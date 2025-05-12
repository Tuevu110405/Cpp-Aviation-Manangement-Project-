#ifndef WEATHERSTANDARDVN_H
#define WEATHERSTANDARDVN_H
#include "WeatherStandard.h"
using namespace std;

class WeatherStandardVN : public WeatherStandard {
private:
    float visibility;
    float crosswind;
    float tailwind;
    float temperatureUpperBound;
    float temperatureLowerBound;
    float thunderstorm;
    float horizontalVisibility;

public:
    WeatherStandardVN();
    WeatherStandardVN(float visibility, float horizontalVisibility, float crosswind, float tailwind, float temperatureUpperBound, float temperatureLowerBound, float thunderstorm);

    // Override isWeatherAcceptable to use the attributes of WeatherStandardVN
    bool isWeatherAcceptable(const Weather& weather) const override;

    // Operator overload to print Vietnamese weather standard
    friend ostream& operator<<(ostream& os, const WeatherStandardVN& weatherStandardVN);
};

#endif