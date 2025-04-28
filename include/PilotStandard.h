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
    int maxAgeMale;     // The maximum age for a male pilot.
    int maxAgeFemale;   // The maximum age for a female pilot.

public:
    // Accessor functions.
    string getModelName() const;
    int getMinRequiredFlightHours() const;
    int getMinRequiredHoursInCommand() const;
    string getRequiredLicenseType() const;
    int getMinRequiredEnglishLevel() const;
    int getRequiredHealthStatus() const;
    int getMaxAgeMale() const;
    int getMaxAgeFemale() const;

    // Other funtions.
    static void loadStandardsFromFile(PilotStandard*, ifstream&, const int &);
    friend ostream& operator << (ostream &, const PilotStandard&);
}; 
#endif