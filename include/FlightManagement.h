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
    // Pilot-related variable (Hoang)
    static vector<PilotStandard> pilotStandardArray; 

    // Vector valid flight (Tue)
    static vector<Flight *> eligibleFlightList;
    static vector<Flight *> ineligibleFlightList;
public:
    // Pilot-related functions (Hoang)
    static void loadPilotStandard(const string &fileName);
    static PilotStandard findPilotStandard(const string &model);
    static void displayPilotStandards(const string &model);

    // Actions of flight management(Tue)
    static void addFlight(Flight *flight);

    // Accessor functions for valid and invalid flights
    static vector<Flight *> getEligibleFlightList();
    static vector<Flight *> getIneligibleFlightList();

    //function find invalid flight based on flightID
    // notice: after the flight is picked out , it will be removed from invalidFlight
    static Flight *getIneligibleFlight(string flightID);

    // Report flight data (Hoang).
    static void writeIneligibleFlights(const string &fileName);
    static void writeEligibleFlights(const string &fileName);
    static void writeSummary(const string &fileName);
    static void deleteFlights();
};
#endif