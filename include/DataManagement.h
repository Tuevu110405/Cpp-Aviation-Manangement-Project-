#ifndef DATA_MANAGEMENT_H
#define DATA_MANAGEMENT_H
#include "PilotStandard.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class DataManagement
{
private:
    // Pilot-related variable (Hoang)
    static vector<PilotStandard> pilotStandardArray;  

public:
    // Pilot-related functions (Hoang)
    static void loadPilotStandard(const string &fileName);
    static PilotStandard findPilotStandard(const string &model);
    static void displayPilotStandards(const string &model);
};
#endif
