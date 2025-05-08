#ifndef FLIGHT_MANAGEMENT_DEPARTMENT_H
#define FLIGHT_MANAGEMENT_DEPARTMENT_H
#include "PilotStandard.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class FlightManagementDepartment
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