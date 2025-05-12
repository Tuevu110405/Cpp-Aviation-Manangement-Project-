#ifndef WEATHER_H
#define WEATHER_H
#include <string>
#include <iostream>
using namespace std;

class Weather{
private:
    float visibility;
    float crosswind;
    float temperature;
    float thunderstorm;
    float tailwind;
    float horizontalVisibility;
    bool Freezing;
    

public:
    //Default constructor
    Weather();
    //Constructor for initializing Vietnamese weather conditions 
    Weather(float visibility, float crosswind, float temperature, float thunderstorm, float tailwind, float horizontalVisibility);
    
    //Getters and setters 
    
    bool getFreezing() const;
    float getVisibility() const;
    float getCrosswind() const;
    float getTemperature() const;
    float getThunderstorm() const;
    float getTailwind() const;
    float getHorizontalVisibility() const;
    void setVisibility(float visibility);
    void setCrosswind(float crosswind);
    void setTemperature(float temperature);
    void setThunderstorm(float thunderstorm);
    void setTailwind(float tailwind);
    void setHorizontalVisibility(float horizontalVisibility);
    void setFreezing(bool Freezing);
    //cout << operator overload
    


};
#endif // WEATHER_H
//operator << to print the Vietnames weather
ostream& operator<<(ostream& os, const Weather& weather);
// operator >> to input Vietnamese weather
istream& operator>>(istream& is, Weather& weather);