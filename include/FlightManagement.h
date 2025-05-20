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
    // Vector valid flight (Tue)
    static vector<Flight> validFlight;
    static vector<Flight> invalidFlight;
public:
    //actions of flight management(Tue)
    static void addValidFlight(Flight& flight);
    static void addInvalidFlight(Flight& flight);
    //accessor functions for valid and invalid flights
    static vector<Flight> getValidFlight();
    static vector<Flight> getInvalidFlight();
    //store flight to valid or invalid flight after inspection

    static void storeFlight(Flight &flight);
    //function find invalid flight based on flightID
    // notice: after the flight is picked out , it will be removed from invalidFlight
    static Flight& getInvalidFlight(string flightID);


};
#endif
