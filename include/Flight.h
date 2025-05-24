
#ifndef FLIGHT_H
#define FLIGHT_H
#include "Weather.h"
#include "WeatherInspectionResult.h"
#include "PilotInspectionResult.h"
#include "StringManipulator.h"
#include "Pilot.h"
#include "Plane.h"
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PlaneInspectionresult.h"
#include "cargoPlaneInspectionResult.h"
#include "PassengerPlaneInspectionResult.h"
#include "Location.h"
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
    PlaneInspectionResult* planeInspectionResult;
    
    // Location (Tung)
    Location location; // The location of the flight.
    string departureCode; // Departure airport code.
    string arrivalCode; // Arrival airport code.


    

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
    Flight(const string &id, const string &type, const string& dep, const string& arr, const Pilot &pilotInfor, const Weather &weatherInfo, const Plane *planeInfo);
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

    const PlaneInspectionResult* getPlaneInspectionResult() const
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
        if (plane != nullptr)
            delete plane;
        plane = newPlane;
    }

    void setPlaneInspectionResult(const PlaneInspectionResult &result);

    // Mutator functions for location (Tung).
    void setDepartureCode(const string &code)
        { departureCode = code; }
    void setArrivalCode(const string &code)
        { arrivalCode = code; }
    void setLocation(const Location &loc)    // Set the location of the flight from file
        { location = loc; }
    void setLocation(const string &depCode, const string &arrCode)  // Set the location of the flight from text
        { departureCode = depCode; arrivalCode = arrCode; }
    
    // Function to get the location of the flight (Tung).
    const Location& getLocation() const
        { return location; }
    const string& getDepartureCode() const
        { return departureCode; }
    const string& getArrivalCode() const
        { return arrivalCode; }
    
    // Other functions (Hoang).
    void displayDetailsPilotResult() const;
    void displayDetailsWeatherResult() const;
    void displayDetailsPlaneResult() const;
};


#endif 