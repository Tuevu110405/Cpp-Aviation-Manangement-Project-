#include "../include/Plane.h"
#include "../include/CargoPlane.h"
#include "../include/PassengerPlane.h"
#include "../include/Flight.h"
#include "../include/Weather.h"
#include "../include/WeatherStandard.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/Pilot.h"
#include "../include/PilotInspectionResult.h"
#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/PlaneInspectionresult.h"

#include <iostream>
using namespace std;

int main()
{
    FlightManagement::loadPilotStandard("../pilot_and_weather_test_(Tue & Hoang))/pilot_standards.txt");
    Flight* flight = new Flight();
    Weather weather;

    cout << "Enter forecast weather data:\n";
    
    cin >> weather;
    cout << weather;
    flight->setWeather(weather);
    flight->setFlightID("VN001");
    flight->setFlightType("Passenger");
    Pilot pilot;
    cin >> pilot;
    cout << pilot;
    flight->setPilot(pilot);




    Plane *p = new PassengerPlane;
    p->setBaseInfo(10, 100, 1000, "Boeing737");

    cin >> *p;

    cout << *p;
    flight->setPlane(p);
    WeatherStandardVN weatherStandard;
    PilotStandard pilotStandard = FlightManagement::findPilotStandard(p->getModel());
    PilotInspectionResult pilotInspectionResult = FlightInspection::inspectPilot(pilot, pilotStandard);
    flight->setPilotResult(pilotInspectionResult);
    WeatherInspectionResult weatherInspectionResult = FlightInspection::inspectWeather(*flight, weatherStandard);
    flight->setWeatherInspectionResult(weatherInspectionResult);
    flight->setPlaneInspectionResult(PlaneInspectionResult());

    // Print the inspection results
    cout << "\n[Weather Inspection Result]" << endl;
    cout << "Visibility: " << (flight->getWeatherInspectionResult().getIsVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Crosswind: " << (flight->getWeatherInspectionResult().getIsCrosswind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Temperature: " << (flight->getWeatherInspectionResult().getIsTemperature() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Thunderstorm: " << (flight->getWeatherInspectionResult().getIsThunderstorm() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Tailwind: " << (flight->getWeatherInspectionResult().getIsTailwind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Horizontal Visibility: " << (flight->getWeatherInspectionResult().getIsHorizontalVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Overall Inspection Result: " << (flight->getWeatherInspectionResult().getInspectionResult() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "\n[Plane Inspection Result]" << endl;
    flight->displayDetailsPilotResult();
    delete flight;
    delete p;
    return 0;



    
}
