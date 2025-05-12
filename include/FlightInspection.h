#ifndef FLIGHTINSPECTION_H
#define FLIGHTINSPECTION_H
#include "Weather.h"
#include "WeatherStandardVN.h"
#include "Flight.h"


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
    
    // //Check if the weather is sufficient for flight
    // void inspectWeather() ;
    // bool inspectAll();
    static WeatherInspectionResult& inspectWeather(Flight& flight, WeatherStandardVN& weatherStandard) ;
        // Check if the weather is satisfactory each quality
       

};

#endif


