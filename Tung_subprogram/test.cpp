#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits> // Required for numeric_limits

// Include all your custom headers
#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/DataManagement.h"
#include "../include/Location.h" // For Location and Destination
#include "../include/PilotInspectionResult.h"
#include "../include/PilotStandard.h"
#include "../include/Pilot.h"
#include "../include/PilotCompetence.h"
#include "../include/PilotCertificate.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/WeatherStandardVN.h"
#include "../include/Weather.h"
#include "../include/Plane.h"
#include "../include/CargoPlane.h"
#include "../include/PassengerPlane.h"
#include "../include/CargoPlaneStandard.h"
#include "../include/PassengerPlaneStandard.h"
#include "../include/PlaneInspectionResult.h"
#include "../include/Flight.h"
#include "../include/DataLoader.h"       // Your DataLoader
#include "../include/StringManipulator.h"
#include "../include/Date.h"              // For PilotCertificate

using namespace std;

// Function prototypes
void displayMenu();
int validateMenuOption(const string &option);
void runFlightInspectionSystem();

// Main function
int main() {
    runFlightInspectionSystem();
    return 0;
}

// The main operational logic for the flight inspection system
void runFlightInspectionSystem() {
    // Load shared resources once
    DataManagement::loadPilotStandard("../data/pilot_standards.txt");
    Location airportLocations;
    airportLocations.loadDestinationFromFile("../data/destinations.csv");

    DataLoader* flightDetailsLoaderPtr = nullptr; // Pointer to DataLoader
    bool flightDetailsFileLoaded = false;

    try {
        // Attempt to create and load DataLoader using the constructor that takes a filename
        flightDetailsLoaderPtr = new DataLoader("../data/flight_details.csv");
        flightDetailsFileLoaded = true; // If constructor succeeds, file is loaded
        cout << "Flight details data (for weather/pilot) loaded successfully." << endl;
    } catch (const runtime_error& e) {
        cerr << "Warning: Could not load flight_details.csv: " << e.what() << endl;
        cerr << "Weather and Pilot data will need to be entered manually for all flights." << endl;
        // flightDetailsLoaderPtr remains nullptr, flightDetailsFileLoaded remains false
    }

    const int PASSENGER_OPTION = 1;
    const int CARGO_OPTION = 2;
    const int EXIT_OPTION = 3;

    string optionString;
    int optionChoice;

    // --- Main Menu Loop ---
    do {
        displayMenu();
        getline(cin, optionString);
        optionChoice = validateMenuOption(optionString);

        if (optionChoice == -1) { // Invalid menu option
            cout << "Please try again.\n";
            cin.clear(); // Clear error flags
            // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard leftover input if necessary
            continue;
        }

        if (optionChoice == PASSENGER_OPTION || optionChoice == CARGO_OPTION) {
            Flight *currentFlight = new Flight(); // Create a new flight object for this inspection
            string flightID_input;
            string departureCode_input, arrivalCode_input;
            Destination departureDetails, arrivalDetails; // To store details from airportLocations

            bool flightSuccessfullyProcessed = false;

            // --- 1. User Input for Flight Core Details ---
            cout << (optionChoice == PASSENGER_OPTION ? "\n--- Inspect Passenger Flight ---" : "\n--- Inspect Cargo Flight ---") << endl;
            
            // Get Flight ID
            while (true) {
                cout << "Enter the Flight ID: ";
                getline(cin, flightID_input);
                if (flightID_input.empty()) {
                    cout << "Flight ID cannot be empty. Please try again." << endl;
                    continue;
                }
                try {
                    currentFlight->setFlightID(flightID_input); // Assuming setter validates or is robust
                    break;
                } catch (const Flight::InvalidID& e) { // Assuming Flight class throws this
                    cout << "ERROR: Invalid Flight ID format: " << e.getID() << ". Please try again." << endl;
                } catch (const std::exception& e_gen) { // Generic exception
                     cout << "ERROR setting Flight ID: " << e_gen.what() << ". Please try again." << endl;
                }
            }

            // Get Departure Code
            bool departureFound = false;
            while (!departureFound) {
                cout << "Enter departure airport code: ";
                getline(cin, departureCode_input);
                if (airportLocations.getDestinationByCode(departureCode_input, departureDetails)) {
                    cout << "Departure location: " << departureDetails.city << endl;
                    departureFound = true;
                } else {
                    cout << "Invalid departure code. Please try again." << endl;
                }
            }

            // Get Arrival Code
            bool arrivalFound = false;
            while (!arrivalFound) {
                cout << "Enter arrival airport code: ";
                getline(cin, arrivalCode_input);
                if (arrivalCode_input == departureCode_input) {
                    cout << "Arrival code cannot be the same as departure code. Please try again." << endl;
                } else if (airportLocations.getDestinationByCode(arrivalCode_input, arrivalDetails)) {
                    cout << "Arrival location: " << arrivalDetails.city << endl;
                    arrivalFound = true;
                } else {
                    cout << "Invalid arrival code. Please try again." << endl;
                }
            }
            currentFlight->setDepartureCode(departureCode_input);
            currentFlight->setArrivalCode(arrivalCode_input);
            currentFlight->setFlightType(optionChoice == PASSENGER_OPTION ? "Passenger" : "Cargo");

            // --- 2. User Input for Plane ---
            Plane *planeForFlight = nullptr;
            if (optionChoice == PASSENGER_OPTION) {
                planeForFlight = new PassengerPlane();
                cout << "\nEnter data for the Passenger Plane (ensure all fields are entered as prompted by the specific class input):" << endl;
                cin >> *static_cast<PassengerPlane*>(planeForFlight); // Assumes operator>> handles all necessary inputs
            } else { // CARGO_OPTION
                planeForFlight = new CargoPlane();
                cout << "\nEnter data for the Cargo Plane (ensure all fields are entered as prompted by the specific class input):" << endl;
                cin >> *static_cast<CargoPlane*>(planeForFlight); // Assumes operator>> handles all necessary inputs
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after cin >> Plane
            planeForFlight->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv"); // Path from your first file
            currentFlight->setPlane(planeForFlight); // Flight takes ownership

            // --- 3. Load Weather and Pilot Data from File (or manual input) ---
            Weather weatherForFlight; // Default constructor
            Pilot pilotForFlight;     // Default constructor
            bool weatherPilotLoadedFromFile = false;
            int recordIndex = -1;     // Will store the index of the flight in the CSV data

            if (flightDetailsFileLoaded && flightDetailsLoaderPtr != nullptr) {
                std::string csv_flightID_key = "flightID"; // Key for flight IDs in your flight_details.csv

                try {
                    int numberOfFlightRecords = flightDetailsLoaderPtr->getValueSize(csv_flightID_key);
                    for (int i = 0; i < numberOfFlightRecords; ++i) {
                        if (flightDetailsLoaderPtr->getValue(csv_flightID_key, i) == flightID_input) {
                            recordIndex = i; // Match found
                            break;
                        }
                    }
                } catch (const std::runtime_error& e) {
                    // This means the "flightID" key itself was not found in the CSV.
                    // recordIndex will remain -1.
                }

                if (recordIndex != -1) { // A matching flight ID was found in the CSV
                    try {
                        // Populate Weather
                        weatherForFlight.setVisibility(stof(flightDetailsLoaderPtr->getValue("forward_visibility", recordIndex)));
                        weatherForFlight.setHorizontalVisibility(stof(flightDetailsLoaderPtr->getValue("horizontal_visibility", recordIndex)));
                        weatherForFlight.setCrosswind(stof(flightDetailsLoaderPtr->getValue("crosswind", recordIndex)));
                        weatherForFlight.setTailwind(stof(flightDetailsLoaderPtr->getValue("tailwind", recordIndex)));
                        weatherForFlight.setTemperature(stof(flightDetailsLoaderPtr->getValue("temperature", recordIndex)));
                        weatherForFlight.setThunderstorm(stoi(flightDetailsLoaderPtr->getValue("thunderstorm", recordIndex)));

                        // Populate Pilot
                        pilotForFlight.setName(flightDetailsLoaderPtr->getValue("pilot_name", recordIndex));
                        Date expiryDate(flightDetailsLoaderPtr->getValue("license_expiry_date", recordIndex));
                        pilotForFlight.setPilotCertificate(PilotCertificate(
                            flightDetailsLoaderPtr->getValue("license_type", recordIndex), expiryDate
                        ));
                        pilotForFlight.setPilotCompetence(PilotCompetence(
                            stoi(flightDetailsLoaderPtr->getValue("flight_hours", recordIndex)),
                            stoi(flightDetailsLoaderPtr->getValue("hours_in_command", recordIndex)),
                            stoi(flightDetailsLoaderPtr->getValue("english_level", recordIndex)),
                            stoi(flightDetailsLoaderPtr->getValue("health_status", recordIndex))
                        ));

                        weatherPilotLoadedFromFile = true;
                        cout << "\nWeather and Pilot data successfully loaded from file for Flight ID: " << flightID_input << endl;
                    } catch (const std::exception& e) { // Catches stof/stoi errors, missing detail keys, or out_of_range
                        cerr << "Error parsing detailed weather/pilot data from file for Flight ID " << flightID_input
                             << " (Record Index: " << recordIndex << "). Issue: " << e.what() << endl;
                        cerr << "Please check flight_details.csv for completeness and correct data types for this flight record." << endl;
                        weatherPilotLoadedFromFile = false; // Fallback to manual
                    }
                }
            } // End of if (flightDetailsFileLoaded && flightDetailsLoaderPtr != nullptr)

            if (!weatherPilotLoadedFromFile) {
                cout << (recordIndex == -1 && flightDetailsFileLoaded && flightDetailsLoaderPtr != nullptr ? "\nNo data found in file for Flight ID: " + flightID_input + "." : "");
                cout << (flightDetailsFileLoaded && flightDetailsLoaderPtr != nullptr ? "" : "\nFlight details file was not loaded or is unavailable.");
                cout << "\nPlease enter Weather and Pilot data manually." << endl;
                
                cout << "\nEnter data for Actual Weather (ensure all fields are entered as prompted by the Weather class input):" << endl;
                cin >> weatherForFlight; // Assumes operator>> for Weather
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

                cout << "\nEnter data for Pilot (ensure all fields are entered as prompted by the Pilot class input):" << endl;
                cin >> pilotForFlight;   // Assumes operator>> for Pilot
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            }
            currentFlight->setWeather(weatherForFlight);
            currentFlight->setPilot(pilotForFlight);

            // --- 4. Inspection Loop (Plane, Pilot, Weather) ---
            bool isEligible;
            bool reEnterInspectionData; 
            bool firstInspectionCycle = true;

            PlaneInspectionResult* planeInspResult = nullptr;
            PilotInspectionResult pilotInspResultObj;    // Stored in Flight object
            WeatherInspectionResult weatherInspResultObj;// Stored in Flight object

            do {
                reEnterInspectionData = false; // Reset for this inspection cycle

                if (!firstInspectionCycle) { // If this is a re-entry cycle
                    // Plane Re-entry
                    if (planeInspResult && !planeInspResult->getInspectionResult()) {
                        cout << "\nRe-enter data for the " << (optionChoice == PASSENGER_OPTION ? "Passenger Plane" : "Cargo Plane") << ":" << endl;
                        delete currentFlight->getPlane(); // Delete old plane data
                        Plane* newPlaneForReEntry = nullptr;
                        if (optionChoice == PASSENGER_OPTION) newPlaneForReEntry = new PassengerPlane(); else newPlaneForReEntry = new CargoPlane();
                        cin >> *newPlaneForReEntry;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        newPlaneForReEntry->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");
                        currentFlight->setPlane(newPlaneForReEntry);
                    }
                    // Pilot Re-entry
                    if (!currentFlight->getPilotInspectionResult().getInspectionResult()) {
                        cout << "\nRe-enter data for Pilot:" << endl;
                        Pilot newPilotForReEntry;
                        cin >> newPilotForReEntry;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        currentFlight->setPilot(newPilotForReEntry);
                    }
                    // Weather Re-entry
                    if (!currentFlight->getWeatherInspectionResult().getInspectionResult()) {
                        cout << "\nRe-enter data for Actual Weather:" << endl;
                        Weather newWeatherForReEntry;
                        cin >> newWeatherForReEntry;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        currentFlight->setWeather(newWeatherForReEntry);
                    }
                }

                // Perform Inspections
                PlaneStandard *planeStd = nullptr;
                if (optionChoice == PASSENGER_OPTION) {
                    PassengerPlaneStandard *passStd = new PassengerPlaneStandard();
                    passStd->loadFromFile("../data/Aircraft seat capacity.csv");
                    planeStd = passStd;
                } else { // CARGO_OPTION
                    CargoPlaneStandard *cargoStd = new CargoPlaneStandard();
                    cargoStd->loadFromFile("../data/Aircraft payload.csv");
                    planeStd = cargoStd;
                }
                delete planeInspResult; // Delete previous result before new inspection
                planeInspResult = FlightInspection::inspectPlane(*currentFlight, planeStd);
                currentFlight->setPlaneInspectionResult(*planeInspResult); // Flight class should handle this result
                delete planeStd; // Clean up standard object

                PilotStandard actualPilotStd = DataManagement::findPilotStandard(currentFlight->getPlane()->getModel());
                pilotInspResultObj = FlightInspection::inspectPilot(currentFlight->getPilot(), actualPilotStd);
                currentFlight->setPilotResult(pilotInspResultObj);

                WeatherStandardVN weatherStdVN; // Assuming it loads its standards if necessary in constructor
                weatherInspResultObj = FlightInspection::inspectWeather(currentFlight->getWeather(), weatherStdVN);
                currentFlight->setWeatherInspectionResult(weatherInspResultObj);

                currentFlight->updateFlightStatus();
                isEligible = currentFlight->getFlightStatus();
                firstInspectionCycle = false; // Next iteration is not the first

                if (isEligible) {
                    cout << "\nFlight " << currentFlight->getFlightID() << " is ELIGIBLE for takeoff." << endl;
                    FlightManagement::addFlight(currentFlight);
                    currentFlight = nullptr; // Ownership transferred to FlightManagement
                    flightSuccessfullyProcessed = true;
                } else {
                    cout << "\nFlight " << currentFlight->getFlightID() << " is INELIGIBLE." << endl;
                    if (planeInspResult && !planeInspResult->getInspectionResult()) {
                        cout << "Plane Ineligibility Reasons:" << endl;
                        currentFlight->displayDetailsPlaneResult(); // Implement this in Flight class
                        cout << endl;
                    }
                    if (!pilotInspResultObj.getInspectionResult()) {
                        cout << "Pilot Ineligibility Reasons:" << endl;
                        currentFlight->displayDetailsPilotResult(); // Implement this in Flight class
                        cout << endl;
                    }
                    if (!weatherInspResultObj.getInspectionResult()) {
                        cout << "Weather Ineligibility Reasons:" << endl;
                        currentFlight->displayDetailsWeatherResult(); // Implement this in Flight class
                        cout << endl;
                    }

                    cout << "\nDo you want to re-enter data for ineligible parts? (Y/N): ";
                    char reEnterChoice;
                    cin >> reEnterChoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
                    if (toupper(reEnterChoice) == 'Y') {
                        reEnterInspectionData = true;
                    } else {
                        cout << "Storing flight " << currentFlight->getFlightID() << " as ineligible." << endl;
                        FlightManagement::addFlight(currentFlight);
                        currentFlight = nullptr; // Ownership transferred
                        flightSuccessfullyProcessed = true;
                    }
                }
            } while (reEnterInspectionData && !flightSuccessfullyProcessed); // Loop for re-entering parts if ineligible

            delete planeInspResult; // Clean up the last plane inspection result

            if (currentFlight != nullptr) { // If flight wasn't processed (e.g. loop exited unexpectedly)
                delete currentFlight; // Clean up to prevent memory leak
            }
            
            cout << "\nPress Enter to continue...";
            // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Already did after char choice
            cin.get(); // Wait for user to press Enter

        } else if (optionChoice == EXIT_OPTION) {
            cout << "\nWriting flight data to files..." << endl;
            FlightManagement::writeEligibleFlights("../data/eligible_flights.txt");
            FlightManagement::writeIneligibleFlights("../data/ineligible_flights.txt");
            FlightManagement::writeSummary("../data/summary.txt");
            FlightManagement::deleteFlights(); // Clean up all dynamically allocated Flight objects
            cout << "Data written. Exiting program." << endl;
        }
    } while (optionChoice != EXIT_OPTION);

    // Clean up the dynamically allocated DataLoader object
    delete flightDetailsLoaderPtr;
    flightDetailsLoaderPtr = nullptr;
}

// Function to display the main menu
void displayMenu() {
    cout << "\n--- FLIGHT INSPECTION SYSTEM MENU ---\n";
    cout << "1. Inspect a Passenger flight.\n";
    cout << "2. Inspect a Cargo flight.\n";
    cout << "3. Exit the program.\n";
    cout << "Enter your choice (1-3): ";
}

// Function to validate menu option
int validateMenuOption(const string &optionStr) {
    string processedOption = StringManipulator::removeSpaces(optionStr);

    if (processedOption.empty()) {
        cout << "Error: Option cannot be empty.\n";
        return -1;
    }

    for (char c : processedOption) {
        if (!isdigit(c)) {
            cout << "Error: Option must be a number.\n";
            return -1;
        }
    }

    int optionNum;
    try {
        optionNum = stoi(processedOption);
    } catch (const std::out_of_range&) {
        cout << "Error: Option is too large to be a valid choice.\n";
        return -1;
    } catch (const std::invalid_argument&) {
        cout << "Error: Option is not a valid number.\n";
        return -1;
    }


    if (optionNum >= 1 && optionNum <= 3) {
        return optionNum;
    } else {
        cout << "Error: Invalid option. Please choose between 1 and 3.\n";
        return -1;
    }
}