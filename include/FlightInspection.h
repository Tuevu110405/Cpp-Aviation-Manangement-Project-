#ifndef FLIGHT_INSPECTION_H
#define FLIGHT_INSPECITON_H
#include "PilotInspectionResult.h"
#include "PilotStandard.h"
#include "Pilot.h"
#include <string>
using namespace std;

class FlightInspection
{
public:
    // Function to inspect the pilot (Hoang).
    static PilotInspectionResult inspectPilot(const Pilot &pilotInfo, const PilotStandard &standard);
};

#endif