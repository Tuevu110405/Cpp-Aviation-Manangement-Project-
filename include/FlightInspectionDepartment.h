#ifndef FLIGHT_INSPECTION_DEPARTMENT_H
#define FLIGHT_INSPECITON_DEPARTMENT_H
#include "PilotInspectionResult.h"
#include "PilotStandard.h"
#include "Pilot.h"
#include <string>
using namespace std;

class FlightInspectionDepartment
{
public:
    // Function to inspect the pilot (Hoang).
    static PilotInspectionResult inspectPilot(const Pilot &pilotInfo, const PilotStandard &standard);
};

#endif