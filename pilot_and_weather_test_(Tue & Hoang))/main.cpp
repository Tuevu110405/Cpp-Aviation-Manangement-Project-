#include "../include/Weather.h"
#include "../include/WeatherStandard.h"
#include "../include/Flight.h"
#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/DataManagement.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/Pilot.h"
#include "../include/PilotInspectionResult.h"
#include "../include/PilotStandard.h"
#include <iostream>
using namespace std;

int main()
{   
    // Load the standard into the program.
    DataManagement::loadPilotStandard("pilot_standards.txt");

    // Get data for passenger plane.
    // Plane planeInfo;


    // The actual weather.
    Weather weather;
    weather.setVisibility(300.0);
    weather.setCrosswind(10.0);
    weather.setTemperature(25.0);
    weather.setThunderstorm(1.0);
    weather.setTailwind(9);
    weather.setHorizontalVisibility(6000.0);

    // Using WeatherStandardVN
    WeatherStandardVN weatherStandardVN;
    
    // Get data for the pilot.
    Pilot pilot;
    cout << "\nEnter the data for the pilot.\n";
    cin >> pilot;

    // Create a flight object.
    Flight flight;
    flight.setFlightID("VN001");
    flight.setFlightType("Passenger");
    flight.setPilot(pilot);
    flight.setWeather(weather);

    // Inspect the weather.
    WeatherInspectionResult weatherInspectionResult= FlightInspection::inspectWeather(flight, weatherStandardVN);
    flight.setWeatherInspectionResult(weatherInspectionResult);

    // Print the inspection results
    cout << "\n[Weather Inspection Result]" << endl;
    cout << "Visibility: " << (flight.getWeatherInspectionResult().getIsVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Crosswind: " << (flight.getWeatherInspectionResult().getIsCrosswind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Temperature: " << (flight.getWeatherInspectionResult().getIsTemperature() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Thunderstorm: " << (flight.getWeatherInspectionResult().getIsThunderstorm() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Tailwind: " << (flight.getWeatherInspectionResult().getIsTailwind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Horizontal Visibility: " << (flight.getWeatherInspectionResult().getIsHorizontalVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Overall Inspection Result: " << (flight.getWeatherInspectionResult().getInspectionResult() ? "Acceptable" : "Not Acceptable") << endl;

    // Inspect the pilot for model Boeing 787.
    PilotStandard pilotStandard = DataManagement::findPilotStandard("Boeing 787");
    PilotInspectionResult pilotInspectionResult = FlightInspection::inspectPilot(flight.getPilot(), pilotStandard);

    // Store the pilot inspection result to the flight.
    flight.setPilotResult(pilotInspectionResult);
    
    flight.updateFlightStatus();
    
    // Print the details of the pilot inspection result.
    cout << "\n[Pilot Inspection Result]\n";
    flight.displayDetailsPilotResult();

    return 0;

}