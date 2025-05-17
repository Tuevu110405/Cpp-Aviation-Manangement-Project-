#include "../include/Weather.h"
#include <iostream>
using namespace std;

//Default constructor
Weather::Weather() : visibility(0), crosswind(0), temperature(0), thunderstorm(0), tailwind(0), horizontalVisibility(0) , Freezing(false) {
    // Constructor initialization
}
Weather::Weather(float visibility, float crosswind, float temperature, float thunderstorm, float tailwind, float horizontalVisibility): visibility(visibility), crosswind(crosswind), temperature(temperature),thunderstorm(thunderstorm), tailwind(tailwind), horizontalVisibility(horizontalVisibility), Freezing(false){}

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
float Weather::getTailwind() const {
    return tailwind;
}

float Weather::getHorizontalVisibility() const {
    return horizontalVisibility;
}

bool Weather::getFreezing() const {
    return Freezing;
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

void Weather::setTailwind(float tailwind) {
    this->tailwind = tailwind;
}

void Weather::setHorizontalVisibility(float horizontalVisibility) {
    this->horizontalVisibility = horizontalVisibility;
}

void Weather::setFreezing(bool Freezing) {
    this->Freezing = Freezing;
}

//cout << operator overload
ostream& operator<<(ostream& os, const Weather& weather) {
    os << "The current weather is: " << endl;
    os << "Visibility: " << weather.getVisibility() << endl;
    os << "Crosswind: " << weather.getCrosswind() << endl;
    os << "Temperature: " << weather.getTemperature() << endl;
    os << "Distance to Thunderstorm: " << weather.getThunderstorm() << endl;
    os << "Tailwind: " << weather.getTailwind() << endl;
    os << "Horizontal Visibility: " << weather.getHorizontalVisibility() << endl;
    return os;
}

istream& operator>>(istream& is, Weather& weather){
    cout << "Enter visibility: ";
    float visibility;
    is >> visibility;
    is.ignore();
    weather.setVisibility(visibility);
    cout << "Enter crosswind: ";
    float crosswind;
    is >> crosswind;
    is.ignore();
    weather.setCrosswind(crosswind);
    cout << "Enter temperature: ";
    float temperature;
    is >> temperature;
    is.ignore();
    weather.setTemperature(temperature);
    cout << "Enter distance to thunderstorm: ";
    float thunderstorm;
    is >> thunderstorm;
    is.ignore();
    weather.setThunderstorm(thunderstorm);
    cout << "Enter tailwind: ";
    float tailwind;
    is >> tailwind;
    is.ignore();
    weather.setTailwind(tailwind);
    cout << "Enter horizontal visibility: ";
    float horizontalVisibility;
    is >> horizontalVisibility;
    is.ignore();
    weather.setHorizontalVisibility(horizontalVisibility);
    return is;
}

