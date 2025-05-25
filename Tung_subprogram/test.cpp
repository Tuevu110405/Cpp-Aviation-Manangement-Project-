// #include <iostream>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <sstream>
// #include <algorithm>
// #include <cctype>
// #include <limits> // Required for numeric_limits

// // Include all your custom headers
// #include "../include/FlightInspection.h"
// #include "../include/FlightManagement.h"
// #include "../include/DataManagement.h"
// #include "../include/Location.h" // For Location and Destination
// #include "../include/PilotInspectionResult.h"
// #include "../include/PilotStandard.h"
// #include "../include/Pilot.h"
// #include "../include/PilotCompetence.h"
// #include "../include/PilotCertificate.h"
// #include "../include/WeatherInspectionResult.h"
// #include "../include/WeatherStandardVN.h"
// #include "../include/Weather.h"
// #include "../include/Plane.h"
// #include "../include/CargoPlane.h"
// #include "../include/PassengerPlane.h"
// #include "../include/CargoPlaneStandard.h"
// #include "../include/PassengerPlaneStandard.h"
// #include "../include/PlaneInspectionResult.h" // Ensure this is correct
// // #include "../include/CargoPlaneInspectionResult.h" // Not used directly in combined logic for *planeResult
// // #include "../include/PassengerPlaneInspectionResult.h" // Not used directly in combined logic for *planeResult
// #include "../include/Flight.h"
// #include "../include/DataLoader.h" // From your second file
// #include "../include/StringManipulator.h" // From your second file
// #include "../include/Date.h" // For PilotCertificate

// using namespace std;

// // Function prototypes
// void displayMenu();
// int validateMenuOption(const string &option);
// void runFlightInspectionSystem(); // Renamed main operational function

// // Main function
// int main() {
//     runFlightInspectionSystem();
//     return 0;
// }

// // The main operational logic for the flight inspection system
// void runFlightInspectionSystem() {
//     // Load shared resources once
//     DataManagement::loadPilotStandard("../data/pilot_standards.txt");
//     Location airportLocations; // Changed variable name for clarity
//     airportLocations.loadDestinationFromFile("../data/destinations.csv");

//     DataLoader flightDetailsLoader; // To load weather/pilot data
//     bool flightDetailsFileLoaded = false;
//     try {
//         // Assuming DataLoader is adapted to load the file and store data internally
//         // For simplicity, let's assume it loads into a structure accessible for searching
//         flightDetailsLoader.loadFile("../data/flight_details.csv"); // You might need to adjust DataLoader
//         flightDetailsFileLoaded = true;
//         cout << "Flight details data (for weather/pilot) loaded successfully." << endl;
//     } catch (const runtime_error& e) {
//         cerr << "Warning: Could not load flight_details.csv: " << e.what() << endl;
//         cerr << "Weather and Pilot data will need to be entered manually for all flights." << endl;
//     }

//     const int PASSENGER_OPTION = 1;
//     const int CARGO_OPTION = 2;
//     const int EXIT_OPTION = 3;

//     string optionString;
//     int optionChoice;

//     do {
//         displayMenu();
//         getline(cin, optionString);
//         optionChoice = validateMenuOption(optionString);

//         if (optionChoice == -1) { // Invalid menu option
//             continue;
//         }

//         if (optionChoice == PASSENGER_OPTION || optionChoice == CARGO_OPTION) {
//             Flight *currentFlight = new Flight();
//             string flightID_input;
//             string departureCode_input, arrivalCode_input;
//             Destination departureDetails, arrivalDetails;

//             bool isFirstTimeDataEntry = true; // For the outer loop of data entry for this flight
//             bool tryDataEntryAgain = false;
//             bool flightSuccessfullyProcessed = false;

//             // This loop handles initial data entry and potential re-entry of Flight ID/Destinations
//             // The inner inspection loop will handle re-entry of Plane/Pilot/Weather
//             do {
//                 tryDataEntryAgain = false; // Reset for this iteration

//                 // --- 1. User Input for Flight Core Details ---
//                 cout << (optionChoice == PASSENGER_OPTION ? "\n--- Inspect Passenger Flight ---" : "\n--- Inspect Cargo Flight ---") << endl;
//                 if (isFirstTimeDataEntry) {
//                      // Get Flight ID
//                     while (true) {
//                         cout << "Enter the Flight ID: ";
//                         getline(cin, flightID_input);
//                         try {
//                             currentFlight->setFlightID(flightID_input); // Assuming setter validates
//                             break;
//                         } catch (const Flight::InvalidID& e) {
//                             cout << "ERROR: Invalid Flight ID format: " << e.getID() << ". Please try again." << endl;
//                         }
//                     }

//                     // Get Departure Code
//                     bool departureFound = false;
//                     while (!departureFound) {
//                         cout << "Enter departure airport code: ";
//                         getline(cin, departureCode_input);
//                         if (airportLocations.getDestinationByCode(departureCode_input, departureDetails)) {
//                             cout << "Departure location: " << departureDetails.city << endl;
//                             departureFound = true;
//                         } else {
//                             cout << "Invalid departure code. Please try again." << endl;
//                         }
//                     }

//                     // Get Arrival Code
//                     bool arrivalFound = false;
//                     while (!arrivalFound) {
//                         cout << "Enter arrival airport code: ";
//                         getline(cin, arrivalCode_input);
//                         if (arrivalCode_input == departureCode_input) {
//                             cout << "Arrival code cannot be the same as departure code. Please try again." << endl;
//                             continue;
//                         }
//                         if (airportLocations.getDestinationByCode(arrivalCode_input, arrivalDetails)) {
//                             cout << "Arrival location: " << arrivalDetails.city << endl;
//                             arrivalFound = true;
//                         } else {
//                             cout << "Invalid arrival code. Please try again." << endl;
//                         }
//                     }
//                     currentFlight->setDepartureCode(departureCode_input);
//                     currentFlight->setArrivalCode(arrivalCode_input);
//                     currentFlight->setFlightType(optionChoice == PASSENGER_OPTION ? "Passenger" : "Cargo");
//                 }


//                 // --- 2. User Input for Plane ---
//                 Plane *planeForFlight = nullptr;
//                 if (currentFlight->getPlane()) { // If re-entering, reuse or re-create plane
//                     planeForFlight = currentFlight->getPlane(); // Potentially re-inputting into existing
//                 }

//                 if (!planeForFlight || !isFirstTimeDataEntry) { // Create new if first time or re-entering plane part
//                     delete planeForFlight; // delete old one if exists from previous failed attempt
//                     if (optionChoice == PASSENGER_OPTION) {
//                         planeForFlight = new PassengerPlane();
//                         cout << "\nEnter data for the Passenger Plane:" << endl;
//                         cin >> *static_cast<PassengerPlane*>(planeForFlight);
//                     } else {
//                         planeForFlight = new CargoPlane();
//                         cout << "\nEnter data for the Cargo Plane:" << endl;
//                         cin >> *static_cast<CargoPlane*>(planeForFlight);
//                     }
//                     cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after cin >>
//                     planeForFlight->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");
//                     currentFlight->setPlane(planeForFlight); // Flight takes ownership
//                 }


//                 // --- 3. Load Weather and Pilot Data from File ---
//                 Weather weatherForFlight;
//                 Pilot pilotForFlight;
//                 bool weatherPilotLoadedFromFile = false;

//                 if (flightDetailsFileLoaded) {
//                     int recordIndex = -1;
//                     // Find record by flightID_input in flightDetailsLoader
//                     // This assumes flightDetailsLoader.data is the map<string, vector<string>>
//                     // And getValue(key,index) is a method of DataLoader
//                     try {
//                          if (flightDetailsLoader.getKeyIndex("flightID", flightID_input, recordIndex) ){
//                             // Populate Weather
//                             weatherForFlight.setVisibility(stof(flightDetailsLoader.getValue("forward_visibility", recordIndex)));
//                             weatherForFlight.setHorizontalVisibility(stof(flightDetailsLoader.getValue("horizontal_visibility", recordIndex)));
//                             weatherForFlight.setCrosswind(stof(flightDetailsLoader.getValue("crosswind", recordIndex)));
//                             weatherForFlight.setTailwind(stof(flightDetailsLoader.getValue("tailwind", recordIndex)));
//                             weatherForFlight.setTemperature(stof(flightDetailsLoader.getValue("temperature", recordIndex)));
//                             weatherForFlight.setThunderstorm(stoi(flightDetailsLoader.getValue("thunderstorm", recordIndex)));

//                             // Populate Pilot
//                             pilotForFlight.setName(flightDetailsLoader.getValue("pilot_name", recordIndex));
//                             Date expiryDate(flightDetailsLoader.getValue("license_expiry_date", recordIndex)); // Assuming Date constructor from string
//                             pilotForFlight.setPilotCertificate(PilotCertificate(
//                                 flightDetailsLoader.getValue("license_type", recordIndex), expiryDate
//                             ));
//                             pilotForFlight.setPilotCompetence(PilotCompetence(
//                                 stoi(flightDetailsLoader.getValue("flight_hours", recordIndex)),
//                                 stoi(flightDetailsLoader.getValue("hours_in_command", recordIndex)),
//                                 stoi(flightDetailsLoader.getValue("english_level", recordIndex)),
//                                 stoi(flightDetailsLoader.getValue("health_status", recordIndex))
//                             ));
//                             weatherPilotLoadedFromFile = true;
//                             cout << "\nWeather and Pilot data successfully loaded from file for Flight ID: " << flightID_input << endl;
//                         }
//                     } catch (const std::exception& e) { // Catch stof/stoi errors or missing keys
//                         cerr << "Error parsing weather/pilot data from file for " << flightID_input << ": " << e.what() << endl;
//                         weatherPilotLoadedFromFile = false; // Fallback to manual
//                     }
//                 }

//                 if (!weatherPilotLoadedFromFile) {
//                     cout << (flightDetailsFileLoaded ? "\nCould not find or parse data in file for Flight ID: " + flightID_input : "\nFlight details file not loaded.") << endl;
//                     cout << "Please enter Weather and Pilot data manually." << endl;
//                     cout << "\nEnter data for Actual Weather:" << endl;
//                     cin >> weatherForFlight;
//                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                     cout << "\nEnter data for Pilot:" << endl;
//                     cin >> pilotForFlight;
//                     cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                 }
//                 currentFlight->setWeather(weatherForFlight);
//                 currentFlight->setPilot(pilotForFlight);

//                 // --- 4. Inspection Loop (Plane, Pilot, Weather) ---
//                 bool isEligible;
//                 bool reEnterInspectionData = false;
//                 bool firstInspectionCycle = true;

//                 PlaneInspectionResult* planeInspResult = nullptr; // Must be deleted
//                 PilotInspectionResult pilotInspResultObj;
//                 WeatherInspectionResult weatherInspResultObj;

//                 do {
//                     reEnterInspectionData = false; // Reset for this inspection cycle

//                     // If not the first inspection cycle, it means user chose to re-enter specific parts.
//                     if (!firstInspectionCycle) {
//                         // Check which part was ineligible and prompt for re-entry.
//                         // Plane re-entry (user input part)
//                         if (planeInspResult && !planeInspResult->getInspectionResult()) {
//                             cout << "\nRe-enter data for the " << (optionChoice == PASSENGER_OPTION ? "Passenger Plane" : "Cargo Plane") << ":" << endl;
//                             delete currentFlight->getPlane(); // Delete old plane data
//                             Plane* newPlaneData = nullptr;
//                             if (optionChoice == PASSENGER_OPTION) newPlaneData = new PassengerPlane(); else newPlaneData = new CargoPlane();
//                             cin >> *newPlaneData;
//                             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                             newPlaneData->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");
//                             currentFlight->setPlane(newPlaneData);
//                         }
//                         // Pilot re-entry (overrides file or previous manual)
//                         if (!currentFlight->getPilotResult().getInspectionResult()) { // getPilotResult is from Flight class
//                             cout << "\nRe-enter data for Pilot:" << endl;
//                             Pilot newPilotData;
//                             cin >> newPilotData;
//                             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                             currentFlight->setPilot(newPilotData);
//                         }
//                         // Weather re-entry (overrides file or previous manual)
//                         if (!currentFlight->getWeatherResult().getInspectionResult()) {
//                             cout << "\nRe-enter data for Actual Weather:" << endl;
//                             Weather newWeatherData;
//                             cin >> newWeatherData;
//                             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                             currentFlight->setWeather(newWeatherData);
//                         }
//                     }

//                     // Perform Inspections
//                     // Plane Inspection
//                     PlaneStandard *planeStd = nullptr;
//                     if (optionChoice == PASSENGER_OPTION) {
//                         PassengerPlaneStandard *passStd = new PassengerPlaneStandard();
//                         passStd->loadFromFile("../data/Aircraft seat capacity.csv"); // Path from your first file
//                         planeStd = passStd;
//                     } else {
//                         CargoPlaneStandard *cargoStd = new CargoPlaneStandard();
//                         cargoStd->loadFromFile("../data/Aircraft payload.csv"); // Path from your first file
//                         planeStd = cargoStd;
//                     }
//                     delete planeInspResult; // clear previous result
//                     planeInspResult = FlightInspection::inspectPlane(*currentFlight, planeStd);
//                     currentFlight->setPlaneInspectionResult(*planeInspResult);
//                     delete planeStd;

//                     // Pilot Inspection
//                     PilotStandard actualPilotStd = DataManagement::findPilotStandard(currentFlight->getPlane()->getModel());
//                     pilotInspResultObj = FlightInspection::inspectPilot(currentFlight->getPilot(), actualPilotStd);
//                     currentFlight->setPilotResult(pilotInspResultObj);

//                     // Weather Inspection
//                     WeatherStandardVN weatherStd; // Assuming default constructor loads standards or it's pre-loaded
//                     weatherInspResultObj = FlightInspection::inspectWeather(currentFlight->getWeather(), weatherStd);
//                     currentFlight->setWeatherInspectionResult(weatherInspResultObj);

//                     currentFlight->updateFlightStatus();
//                     isEligible = currentFlight->getFlightStatus();
//                     firstInspectionCycle = false;

//                     if (isEligible) {
//                         cout << "\nFlight " << currentFlight->getFlightID() << " is ELIGIBLE for takeoff." << endl;
//                         FlightManagement::addFlight(currentFlight);
//                         currentFlight = nullptr; // Ownership transferred
//                         flightSuccessfullyProcessed = true;
//                         break; // Exit inspection loop
//                     } else {
//                         cout << "\nFlight " << currentFlight->getFlightID() << " is INELIGIBLE." << endl;
//                         if (planeInspResult && !planeInspResult->getInspectionResult()) {
//                             cout << "Plane Ineligibility Reasons:" << endl;
//                             currentFlight->displayDetailsPlaneResult(); // Assuming this method exists
//                         }
//                         if (!pilotInspResultObj.getInspectionResult()) {
//                             cout << "Pilot Ineligibility Reasons:" << endl;
//                             currentFlight->displayDetailsPilotResult(); // Assuming this method exists
//                         }
//                         if (!weatherInspResultObj.getInspectionResult()) {
//                             cout << "Weather Ineligibility Reasons:" << endl;
//                             currentFlight->displayDetailsWeatherResult(); // Assuming this method exists
//                         }

//                         cout << "\nDo you want to re-enter data for ineligible parts? (Y/N): ";
//                         char reEnterChoice;
//                         cin >> reEnterChoice;
//                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//                         if (toupper(reEnterChoice) == 'Y') {
//                             reEnterInspectionData = true;
//                         } else {
//                             cout << "Storing flight " << currentFlight->getFlightID() << " as ineligible." << endl;
//                             FlightManagement::addFlight(currentFlight);
//                              currentFlight = nullptr; // Ownership transferred
//                             flightSuccessfullyProcessed = true;
//                             break; // Exit inspection loop
//                         }
//                     }
//                 } while (reEnterInspectionData); // Loop for re-entering inspection data

//                 delete planeInspResult; // Clean up last plane inspection result
//                 isFirstTimeDataEntry = false; // Subsequent outer loops are not first time for ID/Dest

//                 if(flightSuccessfullyProcessed) break; // Exit outer data entry loop if flight processed

//                 // If inspection loop finished without flight being processed (e.g. user quit early)
//                 // This part might need adjustment based on how loops are exited.
//                 // For now, assume if flightSuccessfullyProcessed is false, user might want to restart flight entry.
//                 // However, current logic always adds to FlightManagement.

//             } while (tryDataEntryAgain); // Loop for re-entering Flight ID / Destinations (currently not triggered)

//             if (currentFlight) { // If flight object still exists (wasn't added to FlightManagement)
//                 delete currentFlight; // This should also delete its owned Plane object
//             }
//             cout << "\nPress Enter to continue...";
//             cin.get();

//         } else if (optionChoice == EXIT_OPTION) {
//             cout << "\nWriting flight data to files..." << endl;
//             FlightManagement::writeEligibleFlights("../data/eligible_flights.txt");
//             FlightManagement::writeIneligibleFlights("../data/ineligible_flights.txt");
//             FlightManagement::writeSummary("../data/summary.txt");
//             FlightManagement::deleteFlights(); // Clean up all dynamically allocated Flight objects
//             cout << "Data written. Exiting program." << endl;
//         }
//     } while (optionChoice != EXIT_OPTION);
// }

// // Function to display the main menu
// void displayMenu() {
//     cout << "\n--- FLIGHT INSPECTION SYSTEM MENU ---\n";
//     cout << "1. Inspect a Passenger flight.\n";
//     cout << "2. Inspect a Cargo flight.\n";
//     cout << "3. Exit the program.\n";
//     cout << "Enter your choice (1-3): ";
// }

// // Function to validate menu option
// int validateMenuOption(const string &optionStr) {
//     string processedOption = StringManipulator::removeSpaces(optionStr); // Assuming StringManipulator is available

//     if (processedOption.empty()) {
//         cout << "Error: Option cannot be empty.\n";
//         return -1;
//     }

//     for (char c : processedOption) {
//         if (!isdigit(c)) {
//             cout << "Error: Option must be a number.\n";
//             return -1;
//         }
//     }

//     int optionNum;
//     try {
//         optionNum = stoi(processedOption);
//     } catch (const std::out_of_range&) {
//         cout << "Error: Option is too large.\n";
//         return -1;
//     }

//     if (optionNum >= 1 && optionNum <= 3) {
//         return optionNum;
//     } else {
//         cout << "Error: Invalid option. Please choose between 1 and 3.\n";
//         return -1;
//     }
// }

// // Ensure your DataLoader class has a method like:
// // bool DataLoader::getKeyIndex(const std::string& keyNameToSearch, const std::string& valueToFind, int& foundIndex) const {
// //    auto it = data.find(keyNameToSearch);
// //    if (it != data.end()) {
// //        const auto& values = it->second;
// //        for (size_t i = 0; i < values.size(); ++i) {
// //            if (values[i] == valueToFind) {
// //                foundIndex = static_cast<int>(i);
// //                return true;
// //            }
// //        }
// //    }
// //    foundIndex = -1;
// //    return false;
// //}
// // And ensure `getValue(key, index)` is robust.