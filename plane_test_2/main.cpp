#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/DataManagement.h"
#include "../include/PilotInspectionResult.h"
#include "../include/PilotStandard.h"
#include "../include/Pilot.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/WeatherStandardVN.h"
#include "../include/Weather.h"
#include "../include/Flight.h"
#include "../include/Plane.h"
#include "../include/PlaneInspectionresult.h"
#include "../include/PlaneStandard.h"
#include "../include/PassengerPlane.h"
#include "../include/PassengerPlaneStandard.h"
#include "../include/CargoPlane.h"
#include "../include/CargoPlaneStandard.h"
#include "../include/Location.h"
#include "../include/CargoPlaneInspectionResult.h"
#include "../include/PassengerPlaneInspectionResult.h"
#include <iostream>
using namespace std;

int main()
{
    // Load pilot standaard.
    DataManagement::loadPilotStandard("pilot_standards.txt");

    // Get location.
    Location location;

    location.loadDestinationFromFile("destinations.csv");

    // destination details.
    Destination departureLocationDetails;
    Destination arrivalLocationDetails;
    string departureCode;
    string arrivalCode;


    // Flight type.
    string flightType = "Cargo";

    // Get flight ID.
    string flightID;
    cout << "Enter flight ID: ";
    getline(cin, flightID);

   // Get and validate departure code.
    bool departureFound = false;
    while (!departureFound) {
        cout << "Enter departure code: ";
        getline(cin, departureCode);
        if (location.getDestinationByCode(departureCode, departureLocationDetails)) {
            cout << "Departure location found: " << departureLocationDetails.city << endl;
            departureFound = true;
        } else {
            cout << "Invalid departure code. Please try again." << endl;
        }
    }

    // Get and validate arrival code.
    bool arrivalFound = false;
    while (!arrivalFound) {
        cout << "\nEnter arrival code: ";
        getline(cin, arrivalCode);
        if (location.getDestinationByCode(arrivalCode, arrivalLocationDetails)) {
            if (arrivalCode == departureCode) {
                cout << "Arrival code cannot be the same as departure code. Please try again." << endl;
            } else {
                cout << "Arrival location found: " << arrivalLocationDetails.city << endl;
                arrivalFound = true;
            }
        } else {
            cout << "Invalid arrival code. Please try again." << endl;
        }
    }

    
    Plane *plane = nullptr;
    PlaneStandard *planeStandard = nullptr;

    if (flightType == "Cargo") {
        plane = new CargoPlane(); // Create a CargoPlane
        cout << "Enter Cargo Plane details \n";
        
        cin >> *plane; 
        plane->setBaseInfo_from_FIle("Aircraft baseinfo.csv");

        CargoPlaneStandard *cargoStandard = new CargoPlaneStandard();
        cargoStandard->loadFromFile("Aircraft payload.csv");
        planeStandard = cargoStandard;

    } else if (flightType == "Passenger") {
        plane = new PassengerPlane(); // Create a PassengerPlane
        cout << "Enter Passenger Plane details \n";
        cin >> *plane; 
        plane->setBaseInfo_from_FIle("Aircraft baseinfo.csv");

        PassengerPlaneStandard *passengerStandard = new PassengerPlaneStandard();
        passengerStandard->loadFromFile("Passenger_Aircraft_payload.csv"); 
        planeStandard = passengerStandard;
    } else {
        cerr << "Error: Invalid flight type entered (" << flightType << "). Exiting." << endl;
        return 1; // Exit if flight type is invalid
    }
    cin.ignore();
    // Create a Pilot.
    Pilot pilot;
    cin >> pilot;

    // Create weather.
    Weather weather;
    cin >> weather;

    // Create a Flight.
    Flight flight(flightID, flightType, pilot, weather, plane);
    flight.setLocation(departureCode, arrivalCode);


    // Taking weather standard.
    WeatherStandardVN weatherStandard;

    // Taking pilot standard.
    PilotStandard pilotStandard;
    pilotStandard = DataManagement::findPilotStandard(plane->getModel());

    // Inspceting pilot
    PilotInspectionResult pilotResult;
    pilotResult = FlightInspection::inspectPilot(pilot, pilotStandard);
    flight.setPilotResult(pilotResult);

    // Inspect weather.
    WeatherInspectionResult weatherResult;
    weatherResult = FlightInspection::inspectWeather(weather, weatherStandard);
    flight.setWeatherInspectionResult(weatherResult);
    
      // Inspecting plane.
    PlaneInspectionResult *planeInspectionResult = nullptr;
    if (plane && planeStandard) { 
        planeInspectionResult = FlightInspection::inspectPlane(flight, planeStandard);
    } else {
         cerr << "Error: Plane or PlaneStandard is null. Skipping plane inspection." << endl;
    }

    if (planeInspectionResult != nullptr) {
        flight.setPlaneInspectionResult(*planeInspectionResult);
    } else {
        cout << "Warning: Plane inspection failed or was skipped (result is nullptr)." << endl;
    }

    flight.updateFlightStatus();

    // Dislay inspection result.
    cout << "\n[Inspection result]\n";
    flight.displayDetailsPilotResult();
    cout << endl;
    flight.displayDetailsWeatherResult();
    cout << endl;
    flight.displayDetailsPlaneResult();

    return 0;
}