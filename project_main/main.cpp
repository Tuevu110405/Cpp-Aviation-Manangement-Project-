#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/DataManagement.h"
#include "../include/PilotInspectionResult.h"
#include "../include/PilotStandard.h"
#include "../include/Pilot.h"
#include "../include/PilotCompetence.h"
#include "../include/PilotCertificate.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/WeatherStandardVN.h"
#include "../include/Weather.h"
#include "../include/Flight.h"
#include "../include/DataLoader.h"
#include "../include/Plane.h"
#include "../include/CargoPlane.h"
#include "../include/PassengerPlane.h"
#include "../include/Date.h"
#include "../include/PlaneInspectionResult.h"
#include "../include/StringManipulator.h"
#include <string>
#include <iostream>
using namespace std;

// Function prototypes.
void displayMainMenu();
void displayMenu1();
int validateOption(const string &option);
void subprogram1();
void subprogram2();
int main()
{
    // Constants for subprogram.
    const int SUBPROGRAM1 = 1;
    const int SUBPROGRAM2 = 2;
    const int EXIT = 3;

    // Variable to hold the option.
    string optionString;    // To hold the user's option of menu 1.
    int option;             // To hold the user's option after converting to an int.

    do 
    {
        // Display the main menu.
        do
        {
            displayMainMenu();
            getline(cin, optionString);
            option = validateOption(optionString);
            if (option > EXIT || option < SUBPROGRAM1)
            {
                cout << "ERROR: Invalid option. Enter again.\n";
            }
        } while (option > EXIT || option < SUBPROGRAM1);

        // If option to select subprogram1.
        if (option == SUBPROGRAM1)
        {
            subprogram1();
        }
        else if (option == SUBPROGRAM2)
        {
            // Call subprogram2 to load data from file.
            subprogram2();
        }
        else if (option == EXIT)
        {
            cout << "Exit the program sucessfully.\n";
        }
        else
        {
            cout << "ERROR: Invalid option. Enter again.\n";
        }
    } while (option != EXIT);

    return 0;
}

// Suprogram 1.
void subprogram1()
{
    // Load pilot standard from the file named pilot_standards.csv.
    DataManagement::loadPilotStandard("../data/pilot_standards.txt");
    // Load locations of airports from the file named destinations.csv.
    Location location;
    location.loadDestinationFromFile("../data/destinations.csv");
    // Load plane standards.
    DataManagement::loadCargoStandard("../data/Aircraft payload.csv");
    DataManagement::loadPassengerStandard("../data/Aircraft seat capacity.csv");

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
            option = validateOption(optionString);
            if (option > EXIT || option < PASSENGER_OPTION)
            {
                cout << "ERROR: Invalid option. Enter again.\n";
            }
        } while (option > EXIT || option < PASSENGER_OPTION);

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

            PassengerPlaneStandard passengerStandard;
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
                        flight->setDepartureCode(departureCode);
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
                        flight->setArrivalCode(arrivalCode);
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
                        plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");
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
            flight->setPlane(plane);
            flight->setPilot(pilot);
            flight->setWeather(actualWeather);
            
            // Inspect the plane and get the inspection result.
            passengerStandard = DataManagement::findPassengerStandard(plane->getModel()); 
            planeStandard = &passengerStandard;
            planeResult = FlightInspection::inspectPlane(*flight, planeStandard);
            flight->setPlaneInspectionResult(*planeResult);

            // Inspect the pilot and get the inspection result.
            PilotStandard pilotStandard = DataManagement::findPilotStandard(plane->getModel());
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
                break;
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
            flight->setFlightType("Cargo");
            string flightID;                        // The string of flight ID.

            PlaneInspectionResult* planeResult = nullptr;
            PilotInspectionResult pilotResult;
            WeatherInspectionResult weatherResult;

            CargoPlaneStandard cargoStandard;
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
                        flight->setDepartureCode(departureCode);
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
                        flight->setArrivalCode(arrivalCode);
                    }

                    // Prompt user for Plane.
                    cout << "\nEnter data for the cargo plane.\n";
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
                        plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");
                    }
                    if (pilotResult.getInspectionResult() == false)
                    {
                        cout << "Re-enter the data for pilot.\n";
                        cin >> pilot;
                    }
                    if (weatherResult.getInspectionResult() == false)
                    {
                        cout << "\nRe-enter the data for the weather.\n";
                        cin >> actualWeather;
                    }
                }

            // Set data for the flight.
            flight->setPlane(plane);
            flight->setWeather(actualWeather);
            flight->setWeather(actualWeather);
            // Inspect the plane and get the inspection result.
            cargoStandard = DataManagement::findCargoStandard(plane->getModel()); 
            planeStandard = &cargoStandard;
            planeResult = FlightInspection::inspectPlane(*flight, planeStandard);
            flight->setPlaneInspectionResult(*planeResult);
            
            // Inspect the pilot.
            PilotStandard pilotStandard = DataManagement::findPilotStandard(plane->getModel());
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
                break;
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
        // If the option is to exit the program.
        if (option == EXIT)
        {
            const string ELIGIBLE_FLIGHT_FILE = "output/eligible_flights.txt";
            const string INELIGIBLE_FLIGHT_FILE = "output/ineligible_flights.txt";
            const string SUMMARY_FILE = "output/summary.txt";

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

// Function displayMainMenu.
void displayMainMenu()
{
    cout << "\n--- MAIN MENU ---\n";
    cout << "1. To enter data by hand.\n";
    cout << "2. To enter data from a file.\n";
    cout << "3. To exit the program.\n";
    cout << "Enter your choice (1 - 3): ";
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
int validateOption(const string &option)
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

    return optionNumber;
}

void subprogram2(){
    string filepath;

    cout << "Enter the path to the flight data file: ";
    cin >> filepath;
    cout << "--- Loading data from file: " << filepath << " ---" << endl;

    //test fixed path
    // string filepath = "../data/flight_data.csv";
    bool loadOK = false;
    while(!loadOK){
    // Load flight data(try-catch for not being able to open file)
        try{
            DataLoader loader(filepath);
            cout << "Data loaded successfully." << endl;
            // Print the number of flights
            string key = "flightID";
            cout << "This data constains " << loader.getValueSize(key) << " flights." << endl;
            DataManagement::loadPilotStandard("../data/pilot_standards.txt");
            WeatherStandardVN weatherStandard;
            //Using a loop to handle each flight
            for (int i = 0; i < loader.getValueSize(key); i++) {
                // Flight* flight = new Flight();
                string flightID = loader.getValue(key, i);
                // flight->setFlightID(flightID);
                string flightType = loader.getValue("flight_type", i);
                //processing flight type
                flightType = StringManipulator::lowerCase(flightType); // remove spaces
                flightType = StringManipulator::lowerCase(flightType); // Convert to lowercase 

                // if (flightType != "cargo" && flightType != "passenger") {
                //     cout << "Invalid flight type: " << flightType << endl;
                //     delete flight; // Free memory for the flight object
                //     continue; // Skip to the next iteration
                // }
                // flight->setFlightType(flightType);

                
                Weather* weather = new Weather();
                //Set weather data        
                weather->setVisibility(stof(loader.getValue("forward_visibility", i)));
                weather->setCrosswind(stof(loader.getValue("crosswind", i)));
                weather->setTailwind(stof(loader.getValue("tailwind", i)));            
                weather->setTemperature(stof(loader.getValue("temperature", i)));
                weather->setThunderstorm(stof(loader.getValue("thunderstorm", i)));
                weather->setHorizontalVisibility(stof(loader.getValue("horizontal_visibility", i)));
                // flight->setWeather(*weather);
                // delete weather;


                Pilot *pilot= new Pilot();
                //Set pilot data
                pilot->setName(loader.getValue("pilot_name", i));
                pilot->setPilotCompetence(PilotCompetence(stoi(loader.getValue("flight_hours", i)), stoi(loader.getValue("hours_in_command", i)),
                    stoi(loader.getValue("english_level", i)), stoi(loader.getValue("health_status", i))));
                Date expiryDate(loader.getValue("license_expiry_date", i));
                pilot->setPilotCertificate(PilotCertificate(loader.getValue("license_type", i), expiryDate));
                // flight->setPilot(*pilot);
                // delete pilot;

                
                // if(flightType == "cargo"){
                //     //Set cargoPlane data
                //     CargoPlane *plane = new CargoPlane();
                //     plane->setBaseInfo(stof(loader.getValue("fuel_consumption_rate", i)), stof(loader.getValue("speed_val", i)), 
                //         stof(loader.getValue("fuel_tank", i)), loader.getValue("model", i));
                //     plane->setPayload(stof(loader.getValue("capacity", i)));
                //     flight->setPlane(plane);
                    
                // }
                // else if(flightType == "passenger"){
                //     PassengerPlane *plane = new PassengerPlane();
                //     plane->setBaseInfo(stof(loader.getValue("fuel_consumption_rate", i)), stof(loader.getValue("speed_val", i)), 
                //         stof(loader.getValue("fuel_tank", i)), loader.getValue("model", i));
                //     plane->setSeatCapacity(stoi(loader.getValue("capacity", i)));
                //     plane->setNumOfPassenger(stoi(loader.getValue("passenger_number", i)));
                //     flight->setPlane(plane);
                    
                // }
                // else{
                //     cout << "Invalid flight type: " << flightType << endl;
                //     delete flight;
                //     continue; // Skip to the next iteration
                // }

                //New version of setting plane data
                // Get location.
                Location location;

                location.loadDestinationFromFile("../data/destinations.csv");

                // destination details.
                Destination departureLocationDetails;
                Destination arrivalLocationDetails;
                string departureCode;
                string arrivalCode;

                //Create a plane instance
                Plane *plane = nullptr;
                

                if(flightType == "cargo"){
                    plane = new CargoPlane(); // Create a CargoPlane
                    float current_fuel = stof(loader.getValue("fuel", i));
                    string model = loader.getValue("model", i);
                    int engine_status = stoi(loader.getValue("engine_status", i));
                    float payload = stof(loader.getValue("capacity", i));
                    cout << "Plane information: " << endl;
                    cout << "Current fuel: " << current_fuel << endl;
                    cout << "Model: " << model << endl;
                    cout << "Engine status: " << engine_status << endl;
                    cout << "Payload capacity: " << payload << endl;

                    
            
                    //Getting cargo plane details from laoder
                    plane->setCurrent_Fuel(current_fuel);
                    plane->setModel(model);
                    plane->setEngineStatus(engine_status);
                    plane->setPayload(payload);
                    plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");

                    
                }

                else if(flightType == "passenger"){
                    plane = new PassengerPlane(); // Create a PassengerPlane
                    
                    float current_fuel = stof(loader.getValue("fuel", i));
                    string model = loader.getValue("model", i);
                    int engine_status = stoi(loader.getValue("engine_status", i));
                    int  passengernum = stoi(loader.getValue("passenger_number", i));
                    cout << "Plane information: " << endl;
                    cout << "Current fuel: " << current_fuel << endl;
                    cout << "Model: " << model << endl;
                    cout << "Engine status: " << engine_status << endl;
                    cout << "Number of passengers: " << passengernum << endl;
            
                    plane->setCurrent_Fuel( current_fuel);
                    
                    plane->setModel(model);
                    plane->setEngineStatus(engine_status);
                    plane->setNumOfPassenger(passengernum);

                    plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");



                    
                }
                else{
                    cout << "Invalid flight type: " << flightType << endl;
                    // delete flight; // Free memory for the flight object
                    continue; // Skip to the next iteration
                }
                //load arrival and departure code
                departureCode = loader.getValue("departure_code", i);
                arrivalCode = loader.getValue("arrival_code", i);
                // initialize flight instance with parameters
                Flight *flight = new Flight(flightID, flightType, *pilot, *weather, plane);

                //set location for flight
                flight->setDepartureCode(departureCode);
                flight->setArrivalCode(arrivalCode);
                
                
                
        //         //Inspect pilot
        //         PilotStandard pilotStandard = DataManagement::findPilotStandard(plane->getModel());
        //         PilotInspectionResult pilotInspectionResult = FlightInspection::inspectPilot(flight->getPilot(), pilotStandard);
        //         flight->setPilotResult(pilotInspectionResult);
        //         //Inspect weather
        //         WeatherInspectionResult weatherInspectionResult = FlightInspection::inspectWeather(flight->getWeather(), weatherStandard);
        //         flight->setWeatherInspectionResult(weatherInspectionResult);
        //         //Inspect plane
        //         PlaneInspectionResult* planeInspectionResult = nullptr;
        //         if (plane && planeStandard) { 
        //             planeInspectionResult = FlightInspection::inspectPlane(*flight, planeStandard);
        // }       else {
        //             cerr << "Error: Plane or PlaneStandard is null. Skipping plane inspection." << endl;
        // }

        //         if (planeInspectionResult != nullptr) {
        //             flight->setPlaneInspectionResult(*planeInspectionResult);
        // }       else {
        //             cout << "Warning: Plane inspection failed or was skipped (result is nullptr)." << endl;
        // }
        //         //Store the flight in the relevant vector
        //         flight->updateFlightStatus();
        //         FlightManagement::addFlight(flight);
        //         cout << "Processing flight: " << flightID << " succesfully" << endl;

        
        // Taking pilot standard.
                PilotStandard pilotStandard;
                pilotStandard = DataManagement::findPilotStandard(plane->getModel());

                // Inspceting pilot
                PilotInspectionResult pilotResult;
                pilotResult = FlightInspection::inspectPilot(*pilot, pilotStandard);
                flight->setPilotResult(pilotResult);

                // Inspect weather.
                WeatherInspectionResult weatherResult;
                weatherResult = FlightInspection::inspectWeather(*weather, weatherStandard);
                flight->setWeatherInspectionResult(weatherResult);
                
                // Inspecting plane.
                if(flight->getFlightType() == "passenger"){
                    DataManagement::loadPassengerStandard("../data/Aircraft seat capacity.csv");
                    PlaneInspectionResult* planeResult = nullptr;
                    PassengerPlaneStandard passengerStandard;
                    PlaneStandard *planeStandard = nullptr;
                    passengerStandard = DataManagement::findPassengerStandard(plane->getModel()); 
                    planeStandard = &passengerStandard;
                    planeResult = FlightInspection::inspectPlane(*flight, planeStandard);
                    flight->setPlaneInspectionResult(*planeResult);
                }
                else if(flight->getFlightType() == "cargo"){
                    DataManagement::loadCargoStandard("../data/Aircraft payload.csv");
                    PlaneInspectionResult* planeResult = nullptr;
                    CargoPlaneStandard cargoStandard;
                    PlaneStandard *planeStandard = nullptr;
                    cargoStandard = DataManagement::findCargoStandard(plane->getModel()); 
                    planeStandard = &cargoStandard;
                    planeResult = FlightInspection::inspectPlane(*flight, planeStandard);
                    flight->setPlaneInspectionResult(*planeResult);
                }
                else{
                    cout << "Invalid flight type: " << flightType << endl;
                    delete flight; // Free memory for the flight object
                    continue; // Skip to the next iteration
                }

                flight->updateFlightStatus();
                delete weather; // Free memory for the weather object
                delete pilot; // Free memory for the pilot object
                FlightManagement::addFlight(flight); // Store the flight in the relevant vector
                cout << "Processing flight: " << flightID << " successfully." << endl;

                



            }
            loadOK = true; 
            
            //

        }
        catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please check the file path and format." << endl;
            cout << "Enter the path to the flight data file again: ";
            cin >> filepath; 
            
        }
}
    cout << "---Data loaded and handled successfully---" << endl;
    // catch (const exception& e) {
    //     cout << "An unexpected error occurred: " << e.what() << endl;
        
    // }
   
    // FlightManagement::writeEligibleFlights("eligible_flights.txt");
    // try{
    //     FlightManagement::writeEligibleFlights("eligible_flights.txt");
    //     FlightManagement::writeIneligibleFlights("ineligible_flights.txt");
    // }
    // catch(const exception& e){
    //     cout << "Error writing to file: " << e.what() << endl;
    //     return;
    // }

    // vector <Flight *> ineligibleList = FlightManagement::getIneligibleFlightList();
    // for (int count = 0; count < ineligibleList.size(); count++)
    // {
    //     cout << ineligibleList[count]->getPlaneInspectionResult()->getInspectionResult() << endl;
    // }
    FlightManagement::writeIneligibleFlights("ineligible_flights.txt");
    FlightManagement::writeSummary("summary.txt");

    //Options allowing user to adjust and validate the invalid flights
    
    // Free memory
    FlightManagement::deleteFlights();
    cout << "All data is written to file successfully." << endl;
    cout <<"---Program finished successfully---" << endl;
    




    
}


