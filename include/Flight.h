#ifndef Flight_H
#define Flight_H
#include "Weather.h"
#include "WeatherInspectionResult.h"
#include "PilotInspectionResult.h"
#include "StringManipulator.h"
#include "Pilot.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;


class Flight{
private:
    //Weather(Tue)
    Weather weather;
    WeatherInspectionResult weatherInspectionResult;
protected:
    string flightID;                    // The flight ID (Hoang).
    string flightType;                  // The type of the flight (Hoang).
    Pilot pilot;                        // The pilot (Hoang).
    PilotInspectionResult pilotResult; 
    

public:
    Flight();
    // Weather(Tue)
    // Getters
    Weather& getWeather() ;
    WeatherInspectionResult& getWeatherInspectionResult() ;
    // Setters
    void setWeather(const Weather& weather);
    void setWeatherInspectionResult(const WeatherInspectionResult& weatherInspectionResult);
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
    Flight(const string &id, const string &type, const Pilot &pilotInfor);

    // Accessor functions.
    string getFlightID() const
        { return flightID; }

    string getFlightType() const
        { return flightType; }

    Pilot getPilot() const
        { return pilot; }
    
    const PilotInspectionResult &getPilotInspectionResult() const
        { return pilotResult; }
        
    // Mutator functions.
    void setFlightID(const string &id);
    void setFlightType(const string &type);
    void setPilot(const Pilot &newPilot);
    void setPilotResult(const PilotInspectionResult &);
    
    
    
};


#endif 
