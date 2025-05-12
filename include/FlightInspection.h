#ifndef FLIGHTINSPECTION_H
#define FLIGHTINSPECTION_H
#include "Weather.h"
#include "WeatherStandardVN.h"
#include "Flight.h"
#ifndef FLIGHT_INSPECTION_H
#define FLIGHT_INSPECITON_H
#include "PilotInspectionResult.h"
#include "PilotStandard.h"
#include "Pilot.h"
#include <string>
using namespace std;


class FlightInspection{

protected:
    // Flight flight;
    // WeatherStandardVN weatherStandard;
    
    

public:
    // FlightInspection(const Flight& flight, const WeatherStandardVN& weatherStandard);
    // //Getters and setters for flight and weatherStandard
    // Flight& getFlight() ;
    // WeatherStandardVN& getWeatherStandard();
    // void setFlight(const Flight& flight);
    // void setWeatherStandard(const WeatherStandardVN& weatherStandard); 
    
    // //Check if the weather is sufficient for flight(Tue)
    // void inspectWeather() ;
    // bool inspectAll();
    static WeatherInspectionResult& inspectWeather(Flight& flight, WeatherStandardVN& weatherStandard) ;
        
    // Function to inspect the pilot (Hoang).
    static PilotInspectionResult inspectPilot(const Pilot &pilotInfo, const PilotStandard &standard);
       

};

#endif


