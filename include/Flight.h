#ifndef FLIGHT_H
#define FLIGHT_H
#include "Weather.h"
#include "WeatherInspectionResult.h"
#include "PilotInspectionResult.h"
#include "StringManipulator.h"
#include "Pilot.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;


class Flight
{
private:
    // Pilot and flight (Hoang).
    string flightID;                    // The flight ID (Hoang).
    string flightType;                  // The type of the flight (Hoang).
    Pilot pilot;                        // The pilot (Hoang).
    PilotInspectionResult pilotResult;  // The pilot inspection result.
    
    // Weather (Tue)
    Weather weather;
    WeatherInspectionResult weatherInspectionResult;

    // Plane (Tung)
    
public:
    // Exception classes.
    // Classes for exceptions.
    class InvalidID
    {
    private:
        string id;
    public:
        InvalidID(string v)
            { id = v; }
        string getID() const
            { return id; }
    };

    // Default constructor.
    Flight();

    // Constructor.
    Flight(const string &id, const string &type, const Pilot &pilotInfor, const Weather &weatherInfo);

    // Accessor functions (Hoang).
    string getFlightID() const
        { return flightID; }

    string getFlightType() const
        { return flightType; }

    Pilot getPilot() const
        { return pilot; }
    
    const PilotInspectionResult &getPilotInspectionResult() const
        { return pilotResult; }

    // Accessor functions (Tue).
    const Weather& getWeather();
    const WeatherInspectionResult& getWeatherInspectionResult();
    
    
        
    // Mutator functions (Hoang).
    void setFlightID(const string &id);
    void setFlightType(const string &type);
    void setPilot(const Pilot &newPilot);
    void setPilotResult(const PilotInspectionResult &);

    // Mutator functions (Tue).
    void setWeather(const Weather& weather);
    void setWeatherInspectionResult(const WeatherInspectionResult& weatherInspectionResult);

    // Other functions (Hoang).
    void displayDetailsPilotResult() const;
};


#endif 
