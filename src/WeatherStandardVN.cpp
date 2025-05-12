#include "WeatherStandardVN.h"
#include <iostream>
using namespace std;

// Default constructor
WeatherStandardVN::WeatherStandardVN()
    : visibility(250.0), horizontalVisibility(5000.0), crosswind(15.0), tailwind(10.0),
      temperatureUpperBound(50.0), temperatureLowerBound(-47.0), thunderstorm(5.0) {}

// Parameterized constructor
WeatherStandardVN::WeatherStandardVN(float visibility, float horizontalVisibility, float crosswind, float tailwind, float temperatureUpperBound, float temperatureLowerBound, float thunderstorm)
    : visibility(visibility), horizontalVisibility(horizontalVisibility), crosswind(crosswind), tailwind(tailwind),
      temperatureUpperBound(temperatureUpperBound), temperatureLowerBound(temperatureLowerBound), thunderstorm(thunderstorm) {}

// Override isWeatherAcceptable
bool WeatherStandardVN::isWeatherAcceptable(const Weather& weather) const {
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

    return true;
}

// Operator overload for printing
ostream& operator<<(ostream& os, const WeatherStandardVN& weatherStandardVN) {
    os << "Our current program supports weather checking for the Vietnamese region" << endl;
    os << "Minimum Visibility: " << weatherStandardVN.visibility << endl;
    os << "Minimum Horizontal Visibility: " << weatherStandardVN.horizontalVisibility << endl;
    os << "Maximum Crosswind: " << weatherStandardVN.crosswind << endl;
    os << "Maximum Tailwind: " << weatherStandardVN.tailwind << endl;
    os << "Maximum Temperature: " << weatherStandardVN.temperatureUpperBound << endl;
    os << "Minimum Temperature: " << weatherStandardVN.temperatureLowerBound << endl;
    os << "Maximum distance to Thunderstorm: " << weatherStandardVN.thunderstorm << endl;
    return os;
}