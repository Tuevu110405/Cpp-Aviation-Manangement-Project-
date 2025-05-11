#ifndef FLIGHT_H
#define FLIGHT_H
#include "PilotInspectionResult.h"
#include "StringManipulator.h"
#include "Pilot.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Flight
{
protected:
    Pilot pilot;                        // The pilot.
    PilotInspectionResult pilotResult;  // The pilot inspection result.
public:
    // Default constructor.
    Flight();

    // Constructor.
    Flight(const Pilot &pilotInfor);

    // Accessor functions.
    Pilot getPilot() const
        { return pilot; }
    
    const PilotInspectionResult &getPilotInspectionResult() const
        { return pilotResult; }
        
    // Mutator functions.
    void setPilot(const Pilot &newPilot);
    void setPilotResult(const PilotInspectionResult &);
};
#endif