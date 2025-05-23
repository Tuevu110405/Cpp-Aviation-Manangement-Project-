#ifndef FLIGHT_INSPECTION_H
#define FLIGHT_INSPECTION_H
#include "Weather.h"
#include "WeatherStandardVN.h"
#include "Flight.h"
#include "WeatherInspectionResult.h"
#include "PilotInspectionResult.h"
#include "PilotStandard.h"
#include "Pilot.h"
#include "Plane.h"
#include "PlaneInspectionresult.h"
#include "PassengerPlaneInspectionResult.h"
#include "CargoPlaneInspectionResult.h"
#include "PlaneStandard.h"
#include "CargoPlaneStandard.h"
#include "PassengerPlaneStandard.h"
#include <string>
using namespace std;

class FlightInspection
{
public:
    // Function to inspect the weather (Tue).
    static WeatherInspectionResult inspectWeather(Flight& flight, WeatherStandardVN& weatherStandard);
        
    // Function to inspect the pilot (Hoang).
    static PilotInspectionResult inspectPilot(const Pilot &pilotInfo, const PilotStandard &standard);

    // Function to inspect the plane (Tung).
    static PlaneInspectionResult inspectPlane(const Plane *plane, const PlaneStandard &standard);


};

#endif


