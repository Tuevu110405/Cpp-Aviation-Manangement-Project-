#ifndef FLIGHTMANAGEMENT_H
#define FLIGHTMANAGEMENT_H
#include "Weather.h"
#include "WeatherStandard.h"
#include "Flight.h"
#include "PilotStandard.h"
#include "FlightInspection.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class FlightManagement
{
private:
    static vector<PilotStandard> pilotStandardArray;    // Pilot-related variable (Hoang)
    // Vector valid flight (Tue)
    vector<Flight> validFlight;
    vector<Flight> invalidFlight;
public:
    // Pilot-related functions (Hoang)
    static void loadPilotStandard(const string &fileName);
    static PilotStandard findPilotStandard(const string &model);
    static void displayPilotStandards(const string &model);
    //
    void updateInvalidAndValidFlight(Flight &flight);
    //output file
};
#endif;