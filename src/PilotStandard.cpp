#include "PilotStandard.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

// Definition of PilotStandard::getModelName
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
void PilotStandard::loadStandardsFromFile(PilotStandard* arrPtr, ifstream &inputFile, const int &numOfRecords)
{
    // Skip the header line.
    string headerLine;
    getline(inputFile, headerLine);

    // Reading the file.
    int index = 0;  // Index of the array.
    string line;

    while(!inputFile.eof() && index < numOfRecords)
    {
        // Read the entire line in the file.
        getline(inputFile, line);

        // Skip empty lines.
        if (line.empty()) 
            continue; 

        // Create a PilotStandard object.
        PilotStandard pilotStandard;
        string token;

        // Convert the line into a stream.
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

    // If the number of records in the file is less than 
    // the number of elements in the array.
    if (index < numOfRecords)
    {
        // Create a PilotStandard with default values.
        PilotStandard pilotStandard;

        // Store default information in the element.
        for (int count = index; index < numOfRecords; index++)
        {
            arrPtr[count] = pilotStandard;
        }
    }
}

// The overloaded cout << operator.
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