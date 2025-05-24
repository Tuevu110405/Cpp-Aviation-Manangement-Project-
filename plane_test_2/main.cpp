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

    // location.loadDestinationFromFile("destinations.csv"); Need to fix
    Destination departure;
    departure.city = "Tokyo";
    departure.airport_code = "HND";
    departure.latitude = 35.5494;
    departure.longitude = 139.7798;
    Destination arrival;
    arrival.city = "Los Angeles";
    arrival.airport_code = "LAX";
    arrival.latitude = 33.9425;
    arrival.longitude = -118.4081;
    const vector<Destination>& destinations = location.getDestinations();

    // Flight type.
    string flightType = "Cargo";

    // Get flight ID.
    string flightID;
    cout << "Enter flight ID: ";
    getline(cin, flightID);

    // Departure code.
    string departureCode;
    cout << "Enter departure code: ";
    getline(cin, departureCode);

    string arrivalCode;
    cout << "\nEnter arrival code: ";
    getline(cin, arrivalCode);

    
    // Create a Plane.
    Plane *plane = new CargoPlane;
    plane = dynamic_cast<CargoPlane *>(plane);
    cin >> *plane;
    plane->setBaseInfo_from_FIle("Aircraft baseinfo.csv");

    
    // Plane standard.
    PlaneStandard *planeStandard = new CargoPlaneStandard;
    planeStandard->loadFromFile("Aircraft payload.csv");

    cin.ignore();
    // Create a Pilot.
    Pilot pilot;
    cin >> pilot;

    // Create weather.
    Weather weather;
    cin >> weather;

    // Create a Flight.
    Flight flight(flightID, flightType, pilot, weather, plane);
    flight.setLocation(location);
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
    
    // Inspecting plane (Need to fix).
    FlightInspection inspector;
    PlaneInspectionResult *planeInspectionResult = inspector.inspectPlane(flight, planeStandard);

    flight.setPlaneInspectionResult(*planeInspectionResult);

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