// The class is designed to hold standards of a pilot,
// and provides methods to retrive the standards and
// to load standards from a file into the program.

#ifndef PILOTSTANDARD_H
#define PILOTSTANDARD_H
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class PilotStandard
{
private:
    string modelName;            // The model for which the standards are applied for.    
    int minRequiredFlightHours;  // The minimum required number of flight hours.
    int minRequiredHoursInCommand;  // The minimum required number of hours in command.
    string requiredLicenseType;     // The required liscense type.
    int minRequiredEnglishLevel;    // The minimum required English level.
    int requiredHealthStatus;       // The minimum required health status.

public:
    // Exception classes.
    class InvalidModel { };
    class InvalidType { };
    class InvalidHours { };
    class InvalidEnglish { };
    class InvalidHealth { };

    // Default constructor.
    PilotStandard();

    // Constructor.
    PilotStandard(string model, int flightHours, int hrsInCommand,
                  string type, int english, int health);

    // Accessor functions.
    string getModelName() const;
    int getMinRequiredFlightHours() const;
    int getMinRequiredHoursInCommand() const;
    string getRequiredLicenseType() const;
    int getMinRequiredEnglishLevel() const;
    int getRequiredHealthStatus() const;

    // Mutator functions.
    void setModelName(string);
    void setMinRequiredFlightHours(int);
    void setMinRequiredHoursInCommand(int);
    void setRequiredLicenseType(string);
    void setMinRequiredEnglishLevel(int);
    void setRequiredHealthStatus(int);

    // Other funtions.
    friend ostream& operator << (ostream &, const PilotStandard&);
}; 
#endif