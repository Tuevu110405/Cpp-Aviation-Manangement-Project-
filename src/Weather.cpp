#include "../include/Weather.h"
#include <iostream>
using namespace std;

Weather::Weather(float visibility, float crosswind, float temperature, float thunderstorm): visibility(visibility), crosswind(crosswind), temperature(temperature),thunderstorm(thunderstorm){}

//Getters
float Weather::getVisibility() const {
    return visibility;
}

float Weather::getCrosswind() const {
    return crosswind;
}

float Weather::getTemperature() const {
    return temperature;
}

float Weather::getThunderstorm() const {
    return thunderstorm;
}


//Setters
void Weather::setVisibility(float visibility) {
    this->visibility = visibility;
}

void Weather::setCrosswind(float crosswind) {
    this->crosswind = crosswind;
}

void Weather::setTemperature(float temperature) {
    this->temperature = temperature;
}

void Weather::setThunderstorm(float thunderstorm) {
    this->thunderstorm = thunderstorm;
}

