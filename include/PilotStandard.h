#ifndef PILOTSTANDARD_H
#define PILOTSTANDARD_H
#include <string>
#include <iostream>
using namespace std;

class PilotStandard
{
private:
    string modelName;               // The model for which the standards are applied for.    
    int minRequiredFlightHours;     // The minimum required number of flight hours.
    int minRequiredHoursInCommand;  // The minimum required number of hours in command.
    string requiredLicenseType;     // The required license type.
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
    PilotStandard(const string &model, const int &flightHours, const int &hrsInCommand,
                  const string &type, const int &english, const int &health);

    // Accessor functions.
    string getModelName() const;
    int getMinRequiredFlightHours() const;
    int getMinRequiredHoursInCommand() const;
    string getRequiredLicenseType() const;
    int getMinRequiredEnglishLevel() const;
    int getRequiredHealthStatus() const;

    // Mutator functions.
    void setModelName(const string &model);
    void setMinRequiredFlightHours(const int &hours);
    void setMinRequiredHoursInCommand(const int &hours);
    void setRequiredLicenseType(const string &type);
    void setMinRequiredEnglishLevel(const int &level);
    void setRequiredHealthStatus(const int &health);

    // Other funtions.
    friend ostream& operator << (ostream &, const PilotStandard&);
}; 
#endif