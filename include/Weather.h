#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
using namespace std;

class Weather{
private:
    float visibility;
    float crosswind;
    float temperature;
    float thunderstorm;

public:
    Weather(float visibility, float crosswind, float temperature, float thunderstorm);
    
    //Getters and setters 
    float getVisibility() const;
    float getCrosswind() const;
    float getTemperature() const;
    float getThunderstorm() const;
    void setVisibility(float visibility);
    void setCrosswind(float crosswind);
    void setTemperature(float temperature);
    void setThunderstorm(float thunderstorm);


};
#endif // WEATHER_H