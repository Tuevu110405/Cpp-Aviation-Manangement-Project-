#ifndef WeatherStandard_H
#define WeatherStandard_H
#include "Weather.h"
#include <iostream>
using namespace std;

class WeatherStandard{
private:
    float visibility;
    float horizontalVisibility;
    float crosswind;
    float tailwind;
    float temperatureUpperBound;
    float temperatureLowerBound;
    float thunderstorm;
    bool Freezing;
public:
    //Constructors
    WeatherStandard();
    WeatherStandard(float visibility, float horizontalVisibility, float crosswind,float tailwind, float temperatureUpperBound, float temperatureLowerBound, float thunderstorm);
    // /Getters and setters
    float getTailwind() const;
    float getVisibility() const;
    float getHorizontalVisibility() const;
    float getCrosswind() const;
    float getTemperatureUpperBound() const;
    float getTemperatureLowerBound() const;
    float getThunderstorm() const;
    bool getFreezing() const;
    void setTailwind(float tailwind);
    void setVisibility(float visibility);
    void setHorizontalVisibility(float horizontalVisibility);
    void setCrosswind(float crosswind);
    void setTemperatureUpperBound(float temperatureUpperBound);
    void setTemperatureLowerBound(float temperatureLowerBound);
    void setThunderstorm(float thunderstorm);
    void setFreezing(bool Freezing);
    //Check whether the weather is qualified
    virtual bool isWeatherAcceptable(const Weather& weather) const ;
};
#endif