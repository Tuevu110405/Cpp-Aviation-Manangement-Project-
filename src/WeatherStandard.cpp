#include "../include/Weather.h"
#include "../include/WeatherStandard.h"
#include <iostream>
using namespace std;

//Getters and constructors
WeatherStandard::WeatherStandard()
    : visibility(0), horizontalVisibility(0), crosswind(0), tailwind(0),
      temperatureUpperBound(0), temperatureLowerBound(0), thunderstorm(0) {}
WeatherStandard::WeatherStandard(float visibility,float horizontalVisibility, float crosswind, float tailwind, float temperatureUpperBound, float temperatureLowerBound, float thunderstorm): visibility(visibility), horizontalVisibility(horizontalVisibility), crosswind(crosswind),tailwind(tailwind), temperatureUpperBound(temperatureUpperBound), temperatureLowerBound(temperatureLowerBound),thunderstorm(thunderstorm){}

float WeatherStandard::getVisibility() const {
    return visibility;
}

float WeatherStandard::getHorizontalVisibility() const {
    return horizontalVisibility;
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

float WeatherStandard::getTailwind() const {
    return tailwind;
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

void WeatherStandard::setTailwind(float tailwind) {
    this->tailwind = tailwind;
}
void WeatherStandard::setHorizontalVisibility(float horizontalVisibility) {
    this->horizontalVisibility = horizontalVisibility;
}

//Update function checking each standard
bool WeatherStandard::isCrosswind(const Weather& weather) const {
    return weather.getCrosswind() <= crosswind;
}
bool WeatherStandard::isTailwind(const Weather& weather) const {
    return weather.getTailwind() <= tailwind;
}
bool WeatherStandard::isVisibility(const Weather& weather) const {
    return weather.getVisibility() >= visibility;
}
bool WeatherStandard::isHorizontalVisibility(const Weather& weather) const {
    return weather.getHorizontalVisibility() >= horizontalVisibility;
}
bool WeatherStandard::isTemperature(const Weather& weather) const {
    return weather.getTemperature() >= temperatureLowerBound && weather.getTemperature() <= temperatureUpperBound;
}
bool WeatherStandard::isThunderstorm(const Weather& weather) const {
    return weather.getThunderstorm() <= thunderstorm;
}
bool WeatherStandard::isFreezing(const Weather& weather) const {
    return weather.getFreezing() == false;
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
    if (weather.getTailwind() > tailwind) {
        return false;
    }
    if (weather.getHorizontalVisibility() < horizontalVisibility) {
        return false;
    }
    if (weather.getFreezing()== true){
        return false;
    }

    return true;
}


