#include "../include/PilotStandard.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

// Definition of Mutator functions.
void PilotStandard::setModelName(string model)
{ modelName = model; }

void PilotStandard::setMinRequiredFlightHours(int hours)
{ minRequiredFlightHours = hours; }

void PilotStandard::setMinRequiredHoursInCommand(int hours)
{ minRequiredHoursInCommand = hours; }

void PilotStandard::setRequiredLicenseType(string type)
{ requiredLicenseType = type; }

void PilotStandard::setMinRequiredEnglishLevel(int level)
{ minRequiredEnglishLevel = level; }

void PilotStandard::setRequiredHealthStatus(int status)
{ requiredHealthStatus = status; }

void PilotStandard::setMaxAgeMale(int age)
{ maxAgeMale = age; }

void PilotStandard::setMaxAgeFemale(int age)
{ maxAgeFemale = age; }

// Definition of Accessor functions.
string PilotStandard::getModelName() const
{ return modelName; }

int PilotStandard::getMinRequiredFlightHours() const
{ return minRequiredFlightHours; }

int PilotStandard::getMinRequiredHoursInCommand() const
{ return minRequiredHoursInCommand; }

string PilotStandard::getRequiredLicenseType() const
{ return requiredLicenseType; }

int PilotStandard::getMinRequiredEnglishLevel() const
{ return minRequiredEnglishLevel; }

int PilotStandard::getRequiredHealthStatus() const
{ return requiredHealthStatus; }

int PilotStandard::getMaxAgeMale() const
{return maxAgeMale; }

int PilotStandard::getMaxAgeFemale() const
{ return maxAgeFemale; }

// Other functions.
void PilotStandard::loadStandardsFromFile(PilotStandard* arrPtr, ifstream &inputFile)
{
    // Skip the header line.
    string headerLine;
    getline(inputFile, headerLine);

    // Reading the file.
    int index = 0;  // Index of the array.
    string line;

    while(getline(inputFile, line))
    {
        PilotStandard pilotStandard;
        string token;

        stringstream ss(line);

        // Read the model name.
        getline(ss, pilotStandard.modelName, ',');

        // Read the minRequiredFlightHours.
        getline(ss, token, ',');
        pilotStandard.minRequiredFlightHours = stoi(token);

        // Read the minRequiredHoursInCommand.
        getline(ss, token, ',');
        pilotStandard.minRequiredHoursInCommand = stoi(token);

        // Read the requiredLicenseType.
        getline(ss, pilotStandard.requiredLicenseType, ',');

        // Read the minRequiredEnglishLevel.
        getline(ss, token, ',');
        pilotStandard.minRequiredEnglishLevel = stoi(token);

        // Read the requiredHealthStatus.
        getline(ss, token, ',');
        pilotStandard.requiredHealthStatus = stoi(token);

        // Read the maxAgeMale.
        getline(ss, token, ',');
        pilotStandard.maxAgeMale = stoi(token);

        // Read the maxAgeFemale.
        getline(ss, token, ',');
        pilotStandard.maxAgeFemale = stoi(token);

        // Store the data of standards into the array.
        arrPtr[index] = pilotStandard;
        // Increment the index.
        index++;
    }
}

ostream &operator << (ostream &strm, const PilotStandard &obj)
{
    strm << "Model name: " << obj.getModelName() << endl;
    strm << "  Minimum required flight hours: " << obj.getMinRequiredFlightHours() << endl;
    strm << "  Minimum required hours in command: " << obj.getMinRequiredHoursInCommand() << endl;
    strm << "  Required license type: " << obj.getRequiredLicenseType() << endl;
    strm << "  Required health status: " << obj.getRequiredHealthStatus() << endl;
    strm << "  Required English level: " << obj.getMinRequiredEnglishLevel() << endl;
    strm << "  Maximum male age: " << obj.getMaxAgeMale() << endl;
    strm << "  Maximum female age: " << obj.getMaxAgeFemale();
    return strm;
}