#include "../include/Weather.h"
#include "../include/WeatherStandard.h"
#include <iostream>
using namespace std;

//Getters 
WeatherStandard::WeatherStandard(float visibility, float crosswind, float temperatureUpperBound, float temperatureLowerBound, float thunderstorm): visibility(visibility), crosswind(crosswind), temperatureUpperBound(temperatureUpperBound), temperatureLowerBound(temperatureLowerBound),thunderstorm(thunderstorm){}

float WeatherStandard::getVisibility() const {
    return visibility;
}

float WeatherStandard::getCrosswind() const {
    return crosswind;
}

float WeatherStandard::getTemperatureUpperBound() const {
    return temperatureUpperBound;
}

float WeatherStandard::getTemperatureLowerBound() const {
    return temperatureLowerBound;
}

float WeatherStandard::getThunderstorm() const {
    return thunderstorm;
}

//Setters
void WeatherStandard::setVisibility(float visibility) {
    this->visibility = visibility;
}

void WeatherStandard::setCrosswind(float crosswind) {
    this->crosswind = crosswind;
}

void WeatherStandard::setTemperatureUpperBound(float temperatureUpperBound) {
    this->temperatureUpperBound = temperatureUpperBound;
}

void WeatherStandard::setTemperatureLowerBound(float temperatureLowerBound) {
    this->temperatureLowerBound = temperatureLowerBound;
}

void WeatherStandard::setThunderstorm(float thunderstorm) {
    this->thunderstorm = thunderstorm;
}

//Check whether the weather is qualified
bool WeatherStandard::isWeatherAcceptable(const Weather& weather) const {
    if (weather.getVisibility() < visibility) {
        return false;
    }
    if (weather.getCrosswind() > crosswind) {
        return false;
    }
    if (weather.getTemperature() < temperatureLowerBound || weather.getTemperature() > temperatureUpperBound) {
        return false;
    }
    if (weather.getThunderstorm() > thunderstorm) {
        return false;
    }
    return true;
}