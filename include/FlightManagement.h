#ifndef FLIGHT_MANAGEMENT_H
#define FLIGHT_MANAGEMENT_H
#include "PilotStandard.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class FlightManagement
{
protected:
    static vector<PilotStandard> pilotStandardArray;    // Pilot-related variable (Hoang)
public:
    // Pilot-related functions (Hoang)
    static void loadPilotStandard(const string &fileName);
    static PilotStandard findPilotStandard(const string &model);
    static void displayPilotStandards();
};

#endif