#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/DataManagement.h"
#include "../include/PilotInspectionResult.h"
#include "../include/PilotStandard.h"
#include "../include/Pilot.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/WeatherStandardVN.h"
#include "../include/Weather.h"
#include "../include/Plane.h"
#include "../include/CargoPlane.h"
#include "../include/PassengerPlane.h"
#include "../include/CargoPlaneStandard.h"
#include "../include/PassengerPlaneStandard.h"
#include "../include/CargoPlaneInspectionResult.h"
#include "../include/PassengerPlaneInspectionResult.h"
#include "../include/Flight.h"
#include <iostream>
using namespace std;

// Function prototypes.
void displayMenu1();
int validateOption1(const string &option);
void subprogram1();
int main()
{
    subprogram1();

    return 0;
}

void subprogram1()
{
    // Load pilot standard from the file named pilot_standards.csv.
    DataManagement::loadPilotStandard("../data/pilot_standards.txt");
    // Load locations of airports from the file named destinations.csv.
    Location location;
    location.loadDestinationFromFile("../data/destinations.csv");

    // Constants for options.
    const int PASSENGER_OPTION = 1;         
    const int CARGO_OPTION = 2;
    const int EXIT = 3;

    // Variable to hold the option.
    string optionString;    // To hold the user's option of menu 1.
    int option;             // To hold the user's option after converting to an int.
    
    // The main loop of the subprogram.
    do
    {
        // Display the menu and get option.
        do
        {
            displayMenu1();
            getline(cin, optionString);
            option = validateOption1(optionString);
        } while (option == -1);

        // FLags
        bool isFirstTime = true;
        bool again = false;
        bool isFlightEligible = false;

        // If option is to inspect a passenger flight.
        if (option == PASSENGER_OPTION)
        {
            Destination departureLocationDetails;   // The depature location.
            Destination arrivalLocationDetails;     // The arrival location.
            string departureCode;                   // The airport code of the departure.
            string arrivalCode;                     // The airport code of the arrival.

            Pilot pilot;                            // A Pilot object with default values.
            Plane *plane = new PassengerPlane();    // A Passenger plane object.
            Weather actualWeather;                  // A Weather object with default values.
            WeatherStandardVN weatherStandardVN;    // A WeatherStandard object with default values.

            Flight *flight = new Flight();          // A pointer to a Flight object.
            string flightID;                        // The string of flight ID.

            // Create inspection result objects.
            PlaneInspectionResult* planeResult = nullptr;
            PilotInspectionResult pilotResult;
            WeatherInspectionResult weatherResult;

            PassengerPlaneStandard *passengerStandard = new PassengerPlaneStandard();
            PlaneStandard *planeStandard = nullptr;

            do
            {
                if (isFirstTime)
                {
                    cout << "\nEnter the data for a passenger flight.\n";
                    // Prompt user for flightID.
                    while (true)
                    {
                        // Try to get flightID from user, then if
                        // the flightID is invalid, prompt again.
                        try
                        {
                            cout << "Enter the flight ID: ";
                            getline(cin, flightID);
                            flight->setFlightID(flightID);
                            break;
                        }
                        catch (Flight::InvalidID id)
                        {
                            cout << "ERROR: The ID " << id.getID()
                                << " is invalid for a Vietnam Airline flight.";
                            cout << "\nEnter again.\n";
                        }
                    }

                    // Get and validate departure code.
                    bool departureFound = false;
                    while (!departureFound)
                    {
                        cout << "\nEnter departure code: ";
                        getline(cin, departureCode);
                        if (location.getDestinationByCode(departureCode, departureLocationDetails))
                        {
                            cout << "Departure location found: " << departureLocationDetails.city << endl;
                            departureFound = true;
                        } 
                        else 
                        {
                            cout << "Invalid departure code. Please try again." << endl;
                        }
                    }

                    // Get and validate arrival code.
                    bool arrivalFound = false;
                    while (!arrivalFound)
                    {
                        cout << "Enter arrival code: ";
                        getline(cin, arrivalCode);
                        if (location.getDestinationByCode(arrivalCode, arrivalLocationDetails))
                        {
                            if (arrivalCode == departureCode) 
                            {
                                cout << "Arrival code cannot be the same as departure code. Please try again." << endl;
                            } 
                            else 
                            {
                                cout << "Arrival location found: " << arrivalLocationDetails.city << endl;
                                arrivalFound = true;
                            }
                        } 
                        else 
                        {
                            cout << "Invalid arrival code. Please try again." << endl;
                        }
                    }

                    // Prompt user for Plane.
                    cout << "\nEnter data for the passenger plane.\n";
                    cin >> *plane;
                    plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");

                    // Prompt user for Pilot.
                    cout << "\nEnter data for pilot.\n";
                    cin >> pilot;

                    // Prompt user for Weather.
                    cout << "\nEnter data for actual weather.\n";
                    cin >> actualWeather;

                    // Set the flag isFirstTime to false.
                    isFirstTime = false;
                }
                else
                {
                    if (planeResult->getInspectionResult() == false)
                    {
                        delete plane;
                        plane = new PassengerPlane();
                        cout << "\nRe-enter the data for plane.\n";
                        cin >> *plane;
                    }
                    if (pilotResult.getInspectionResult() == false)
                    {
                        cout << "\nRe-enter the data for pilot.\n";
                        cin >> pilot;
                    }
                    if (weatherResult.getInspectionResult() == false)
                    {
                        cout << "\nRe-enter the data for the weather.\n";
                        cin >> actualWeather;
                    }
                }
            // Set data into a Flight object.
            flight->setFlightType("Passenger");
            flight->setDepartureCode(departureCode);
            flight->setArrivalCode(arrivalCode);
            flight->setPlane(plane);
            flight->setPilot(pilot);
            flight->setWeather(actualWeather);
            
            // Inspect the plane and get the inspection result.
            passengerStandard->loadFromFile("../data/Aircraft seat capacity.csv"); 
            planeStandard = passengerStandard;
            planeResult = FlightInspection::inspectPlane(*flight, planeStandard);
            flight->setPlaneInspectionResult(*planeResult);

            // Inspect the pilot and get the inspection result.
            PilotStandard pilotStandard = DataManagement::findPilotStandard("Boeing 787");
            pilotResult = FlightInspection::inspectPilot(pilot, pilotStandard);
            flight->setPilotResult(pilotResult);

            // Inspect the weather and get the inspection result.
            weatherResult = FlightInspection::inspectWeather(actualWeather, weatherStandardVN);
            flight->setWeatherInspectionResult(weatherResult);
            
            // Update the flight status.
            flight->updateFlightStatus();

            // Inspect the flight.
            isFlightEligible = (flight->getFlightStatus());
                        
            // If the flight is eligible, store it in the vector.
            if (isFlightEligible)
            {
                cout << "\nThe flight is eligible for takeoff.\n";
                cout << "Storing it in the eligible list...\n";
                FlightManagement::addFlight(flight);
            }
            // Otherwise, prompt user if they want to re-enter the data.
            else
            {
                cout << "\nThe flight is ineligible.\n";
                if (planeResult->getInspectionResult() == false)
                {
                    cout << "\nPlane is ineligible because\n";
                    flight->displayDetailsPlaneResult();
                    cout << endl;
                }
                if (pilotResult.getInspectionResult() == false)
                {
                    cout << "\nPilot is ineligible because";
                    flight->displayDetailsPilotResult();
                    cout << endl;
                }
                if (weatherResult.getInspectionResult() == false)
                {
                    cout << "\nWeather is ineligible because";
                    flight->displayDetailsWeatherResult();
                    cout << endl;
                }

                // Prompt user for re-enter again.
                cout << "\nDo you want to re-enter data for ineligible parts? ";
                cout << "\nEnter Y for Yes and N for No: ";
                char choice;
                cin >> choice;
                cin.ignore();

                if (toupper(choice) == 'Y')
                {
                    again = true;
                }
                // Else put the flight to ineligible list.
                else
                {
                    cout << "\nThe flight is ineligible for takeoff.\n";
                    cout << "Storing it to the ineligible list...\n";
                    FlightManagement::addFlight(flight);
                    break;
                }
            }
        } while (isFlightEligible == false && again == true);

        cout << "\nPress Enter to continue...";
        cin.get();
        }

        // If the option is to inspect a cargo flight.
        if (option == CARGO_OPTION)
        {
            Destination departureLocationDetails;   // The depature location.
            Destination arrivalLocationDetails;     // The arrival location.
            string departureCode;                   // The airport code of the departure.
            string arrivalCode;                     // The airport code of the arrival.

            Pilot pilot;                            // A Pilot object with default values.
            Plane *plane = new CargoPlane();        // A Cargo plane object.
            Weather actualWeather;                  // A Weather object with default values.
            WeatherStandardVN weatherStandardVN;    // A WeatherStandard object with default values.

            Flight *flight = new Flight();          // A pointer to a Flight object.
            string flightID;                        // The string of flight ID.

            PlaneInspectionResult* planeResult = nullptr;
            PilotInspectionResult pilotResult;
            WeatherInspectionResult weatherResult;

            CargoPlaneStandard *cargoStandard = new CargoPlaneStandard();
            PlaneStandard *planeStandard = nullptr;

            do
            {
                if (isFirstTime)
                {
                    cout << "\nEnter the data for a cargo flight.\n";
                    // Prompt user for flightID.
                    while (true)
                    {
                        try
                        {
                            cout << "Enter the flight ID: ";
                            getline(cin, flightID);
                            flight->setFlightID(flightID);
                            break;
                        }
                        catch (Flight::InvalidID id)
                        {
                            cout << "ERROR: The ID " << id.getID()
                                << " is invalid for a Vietnam airline flight.";
                            cout << "\nEnter again.\n";
                        }
                    }

                    // Get and validate departure code.
                    bool departureFound = false;
                    while (!departureFound)
                    {
                        cout << "\nEnter departure code: ";
                        getline(cin, departureCode);
                        if (location.getDestinationByCode(departureCode, departureLocationDetails))
                        {
                            cout << "Departure location found: " << departureLocationDetails.city << endl;
                            departureFound = true;
                        } 
                        else 
                        {
                            cout << "Invalid departure code. Please try again." << endl;
                        }
                    }

                    // Get and validate arrival code.
                    bool arrivalFound = false;
                    while (!arrivalFound)
                    {
                        cout << "Enter arrival code: ";
                        getline(cin, arrivalCode);
                        if (location.getDestinationByCode(arrivalCode, arrivalLocationDetails))
                        {
                            if (arrivalCode == departureCode) 
                            {
                                cout << "Arrival code cannot be the same as departure code. Please try again." << endl;
                            } 
                            else 
                            {
                                cout << "Arrival location found: " << arrivalLocationDetails.city << endl;
                                arrivalFound = true;
                            }
                        } 
                        else 
                        {
                            cout << "Invalid arrival code. Please try again." << endl;
                        }
                    }

                    // Prompt user for Plane.
                    cout << "\nEnter data for the passenger plane.\n";
                    cin >> *plane;
                    plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");

                    // Prompt user for Pilot.
                    cout << "Enter data for pilot.\n";
                    cin >> pilot;

                    // Prompt user for Weather.
                    cout << "\nEnter data for actual weather.\n";
                    cin >> actualWeather;

                    // Set the flag isFirstTime to false.
                    isFirstTime = false;
                }
                else
                {
                    if (planeResult->getInspectionResult() == false)
                    {
                        delete plane;
                        plane = new CargoPlane();
                        cout << "\nRe-enter the data for plane.\n";
                        cin >> *plane;
                    }
                    if (pilotResult.getInspectionResult() == false)
                    {
                        cout << "\nRe-enter the data for pilot.\n";
                        cin >> pilot;
                    }
                    if (weatherResult.getInspectionResult() == false)
                    {
                        cout << "\nRe-enter the data for the weather.\n";
                        cin >> actualWeather;
                    }

                }
            // Set data into a Flight object.
            flight->setFlightType("Cargo");
            flight->setDepartureCode(departureCode);
            flight->setArrivalCode(arrivalCode);
            flight->setPlane(plane);
            flight->setPilot(pilot);
            flight->setWeather(actualWeather);
            
            // Inspect the plane and get the inspection result.
            cargoStandard->loadFromFile("../data/Aircraft payload.csv"); 
            planeStandard = cargoStandard;
            planeResult = FlightInspection::inspectPlane(*flight, planeStandard);
            flight->setPlaneInspectionResult(*planeResult);
            

            // Inspect the pilot.
            PilotStandard pilotStandard = DataManagement::findPilotStandard("Boeing 787");
            pilotResult = FlightInspection::inspectPilot(pilot, pilotStandard);
            flight->setPilotResult(pilotResult);

            // Inspect the weather.
            weatherResult = FlightInspection::inspectWeather(actualWeather, weatherStandardVN);
            flight->setWeatherInspectionResult(weatherResult);
            
            // Update the flight status.
            flight->updateFlightStatus();

            // Inspect the flight.
            isFlightEligible = (flight->getFlightStatus());
                        
            // If the flight is eligible, store it in the vector.
            if (isFlightEligible)
            {
                cout << "\nThe flight is eligible for takeoff.\n";
                cout << "Storing it in the eligible list...\n";
                FlightManagement::addFlight(flight);
            }
            // Otherwise, prompt user if they want to re-enter the data.
            else
            {
                cout << "\nThe flight is ineligible.\n";
                if (planeResult->getInspectionResult() == false)
                {
                    cout << "\nPlane is ineligible because\n";
                    flight->displayDetailsPlaneResult();
                    cout << endl;
                }
                if (pilotResult.getInspectionResult() == false)
                {
                    cout << "Pilot is ineligible because";
                    flight->displayDetailsPilotResult();
                    cout << endl;
                }
                if (weatherResult.getInspectionResult() == false)
                {
                    cout << "\nWeather is ineligible because";
                    flight->displayDetailsWeatherResult();
                    cout << endl;
                }
                // Prompt user to re-enter the data.
                cout << "\nDo you want to re-enter data for ineligible parts? ";
                cout << "\nEnter Y for Yes and N for No: ";
                char choice;
                cin >> choice;
                cin.ignore();

                if (toupper(choice) == 'Y')
                {
                    again = true;
                }
                // Else put the flight to ineligible list.
                else
                {
                    cout << "The flight is ineligible for takeoff.\n";
                    cout << "Storing it to the ineligible list...\n";
                    FlightManagement::addFlight(flight);
                    break;
                }
            }
        } while (isFlightEligible == false && again == true);

        cout << "\nPress Enter to continue...";
        cin.get();
        }
        
        // If the option is to exit the program.
        if (option == EXIT)
        {
            const string ELIGIBLE_FLIGHT_FILE = "eligible_flights.txt";
            const string INELIGIBLE_FLIGHT_FILE = "ineligible_flights.txt";
            const string SUMMARY_FILE = "summary.txt";

            // Write the data of ineligible flights to a file.
            FlightManagement::writeIneligibleFlights(INELIGIBLE_FLIGHT_FILE);
            FlightManagement::writeEligibleFlights(ELIGIBLE_FLIGHT_FILE);

            // Write the summary.
            FlightManagement::writeSummary(SUMMARY_FILE);

            // Delete dynamically allocated memory.
            FlightManagement::deleteFlights();
            
            // Display a message to exit the program.
            cout << "\nComplete writing data to files.\n";
            cout << "Exit the program sucessfully!" << endl;
        }
    } while (option != EXIT);
}


// Function displayMenu.
void displayMenu1()
{
    cout << "\n---MENU---\n";
    cout << "1. Inspect a Passenger flight.\n";
    cout << "2. Inspect a Cargo flight.\n";
    cout << "3. Exit the program.\n";
    cout << "Enter your choice (1 - 3): ";
}


// Function validateOption.
int validateOption1(const string &option)
{
    string output = "";
    // Remove any spaces from the option.
    output = StringManipulator::removeSpaces(option);

    // If the option contains character other than digits,
    // then returns false.
    for (int index = 0; index < output.length(); index++)
    {
        if (!isdigit(output[index]))
        {
            cout << "Error: Option contains invalid characters.\n";
            return -1;
        }
    }

    // Convert the option into numeric type.
    int optionNumber = stoi(output);

    // If the output is out of valid range from 1 to 3,
    // then return false.
    const int MAX_OPTION = 3;
    const int MIN_OPTION = 1;

    if (optionNumber > MAX_OPTION || optionNumber < MIN_OPTION)
    {
        cout << "Error: Out of range option.\n";
        return -1;
    }   
    return optionNumber;
}