#include "../include/Flight.h"

// Default constructor.
Flight::Flight()
{

}

// Constructor
Flight::Flight(const Pilot &pilotInfo)
{
    pilot = pilotInfo;
}

// Function Flight::setPilot (Hoang)
void Flight::setPilot(const Pilot &newPilot)
{
    pilot = newPilot;
}

// Function Flight::setPilotInspectionResult (Hoang)
void Flight::setPilotResult(const PilotInspectionResult &newResult)
{
    pilotResult = newResult;
}
