#ifndef Flight_H
#define Flight_H
#include "Weather.h"
#include "WeatherInspectionResult.h"


class Flight{
private:
    Weather weather;
    WeatherInspectionResult weatherInspectionResult;
    

public:
    Flight();
    // Getters
    Weather& getWeather() ;
    WeatherInspectionResult& getWeatherInspectionResult() ;
    // Setters
    void setWeather(const Weather& weather);
    void setWeatherInspectionResult(const WeatherInspectionResult& weatherInspectionResult);
    
    
    
};


#endif 