#ifndef WeatherStandard_H
#define WeatherStandard_H
#include "Weather.h"
#include <iostream>
using namespace std;

class WeatherStandard{
private:
    float visibility;
    float crosswind;
    float temperatureUpperBound;
    float temperatureLowerBound;
    float thunderstorm;
public:
    //Constructors
    WeatherStandard(float visibility, float crosswind, float temperatureUpperBound, float temperatureLowerBound, float thunderstorm);
    // /Getters and setters
    float getVisibility() const;
    float getCrosswind() const;
    float getTemperatureUpperBound() const;
    float getTemperatureLowerBound() const;
    float getThunderstorm() const;
    void setVisibility(float visibility);
    void setCrosswind(float crosswind);
    void setTemperatureUpperBound(float temperatureUpperBound);
    void setTemperatureLowerBound(float temperatureLowerBound);
    void setThunderstorm(float thunderstorm);
    //Check whether the weather is qualified
    bool isWeatherAcceptable(const Weather& weather) const;
};
#endif