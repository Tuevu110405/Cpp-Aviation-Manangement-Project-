#ifndef FLIGHT_INSPECTION_H
#define FLIGHT_INSPECTION_H
#include "Weather.h"
#include "WeatherStandardVN.h"
#include "Flight.h"
#include "WeatherInspectionResult.h"
#include "PilotInspectionResult.h"
#include "PilotStandard.h"
#include "Pilot.h"
#include <string>
using namespace std;

class FlightInspection
{
public:
    // Function to inspect the weather (Tue).
    static WeatherInspectionResult inspectWeather(const Weather& weather, const  WeatherStandardVN& weatherStandard);
        
    // Function to inspect the pilot (Hoang).
    static PilotInspectionResult inspectPilot(const Pilot &pilotInfo, const PilotStandard &standard);
};

#endif


