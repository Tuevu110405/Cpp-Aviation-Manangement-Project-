#include "../include/WeatherStandardVN.h"
#include <iostream>
using namespace std;

// Default constructor
WeatherStandardVN::WeatherStandardVN()
    : WeatherStandard(250.0, 5000.0, 5.0, 10.0, 50.0, -47.0, 5.0) {}

// Parameterized constructor
WeatherStandardVN::WeatherStandardVN(float visibility, float horizontalVisibility, float crosswind, float tailwind, float temperatureUpperBound, float temperatureLowerBound, float thunderstorm)
    : WeatherStandard( visibility,  horizontalVisibility,  crosswind,  tailwind,  temperatureUpperBound,  temperatureLowerBound,  thunderstorm ) {}

// Override isWeatherAcceptable
bool WeatherStandardVN::isWeatherAcceptable(const Weather& weather) const {
    bool result = isVisibility(weather)
        && isHorizontalVisibility(weather)
        && isCrosswind(weather)
        && isTailwind(weather)
        && isTemperature(weather)
        && isThunderstorm(weather);
    return result;
}

// Operator overload for printing
ostream& operator<<(ostream& os, const WeatherStandardVN& weatherStandardVN) {
    os << "Our current program supports weather checking for the Vietnamese region" << endl;
    os << "Minimum Visibility: " << weatherStandardVN.getVisibility() << endl;
    os << "Minimum Horizontal Visibility: " << weatherStandardVN.getHorizontalVisibility()<< endl;
    os << "Maximum Crosswind: " << weatherStandardVN.getCrosswind() << endl;
    os << "Maximum Tailwind: " << weatherStandardVN.getTailwind() << endl;
    os << "Maximum Temperature: " << weatherStandardVN.getTemperatureUpperBound() << endl;
    os << "Minimum Temperature: " << weatherStandardVN.getTemperatureLowerBound() << endl;
    os << "Maximum distance to Thunderstorm: " << weatherStandardVN.getThunderstorm() << endl;
    return os;
}