#ifndef FLIGHT_H
#define FLIGHT_H
#include "Weather.h"
#include "WeatherInspectionResult.h"
#include "PilotInspectionResult.h"
#include "StringManipulator.h"
#include "Pilot.h"
#include "../include/Plane.h"
#include "../include/PassengerPlane.h"
#include "../include/CargoPlane.h"
#include "PlaneInspectionresult.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;


class Flight
{
private:
    // Pilot and flight (Hoang).
    string flightID;                    // The flight ID.
    string flightType;                  // The type of the flight.
    bool flightStatus;                  // The status of the flight: Eligible or Ineligible.
    Pilot pilot;                        // The pilot.
    PilotInspectionResult pilotResult;  // The pilot inspection result.
    
    // Weather (Tue)
    Weather weather;
    WeatherInspectionResult weatherInspectionResult;

    // Plane (Tung)
    Plane *plane;   // The plane.
    PlaneInspectionResult planeInspectionResult;
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
    Flight(const string &id, const string &type, const Pilot &pilotInfor, const Weather &weatherInfo, const Plane *planeInfo);
    //Copy constructor for FlightManagement stage(Tue)
    
    Flight(const Flight &flight);

    // Accessor functions (Hoang).
    string getFlightID() const
        { return flightID; }

    string getFlightType() const
        { return flightType; }
    
    bool getFlightStatus() const
        { return flightStatus; }

    Pilot getPilot() const
        { return pilot; }
    
    const PilotInspectionResult &getPilotInspectionResult() const
        { return pilotResult; }

    Plane *getPlane() const
        { return plane; }

    PlaneInspectionResult getPlaneInspectionResult() const
        { return planeInspectionResult; }

    // Accessor functions (Tue).
    const Weather& getWeather();
    const WeatherInspectionResult& getWeatherInspectionResult();
    
        
    // Mutator functions (Hoang).
    void setFlightID(const string &id);
    void setFlightType(const string &type);
    void setPilot(const Pilot &newPilot);
    void setPilotResult(const PilotInspectionResult &);
    void updateFlightStatus();

    // Mutator functions (Tue).
    void setWeather(const Weather& weather);
    void setWeatherInspectionResult(const WeatherInspectionResult& weatherInspectionResult);

    // Mutator functions (Tung).
    void setPlane(Plane *newPlane)
    {
        // Do not delete the existing plane pointer here to avoid double deletion.
        plane = newPlane;
    }

    void setPlaneInspectionResult(const PlaneInspectionResult &result)
        { planeInspectionResult = result; }
    
    // Other functions (Hoang).
    void displayDetailsPilotResult() const;
};


#endif 
