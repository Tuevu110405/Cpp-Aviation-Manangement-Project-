#include "../include/StringManipulator.h"
#include "../include/PilotStandard.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

// Default constructor.
PilotStandard::PilotStandard()
{
    modelName = "";
    minRequiredFlightHours = 0;
    minRequiredHoursInCommand = 0;
    requiredLicenseType = "";
    minRequiredEnglishLevel = 0;
    requiredHealthStatus = 0;
}

// Constructor.
PilotStandard::PilotStandard(const string &model, const int &flightHours, const int &hrsInCommand,
                             const string &type, const int &english, const int &health)
{
    try
    {
        setModelName(model);
        setMinRequiredFlightHours(flightHours);
        setMinRequiredHoursInCommand(hrsInCommand);
        setRequiredLicenseType(type);
        setMinRequiredEnglishLevel(english);
        setRequiredHealthStatus(health);
    }
    catch (InvalidModel)
    {
        throw InvalidModel();
    }
    catch (InvalidHours)
    {
        throw InvalidHours();
    }
    catch (InvalidType)
    {
        throw InvalidType();
    }
    catch (InvalidEnglish)
    {
        throw InvalidType();
    }
    catch (InvalidHealth)
    {
        throw InvalidType();
    }
}


// Definition of PilotStandard::getModelName
string PilotStandard::getModelName() const
{ return modelName; }


// Definition of PilotStandard::getMinRequiredFlightHours
int PilotStandard::getMinRequiredFlightHours() const
{ return minRequiredFlightHours; }


// Definition of PilotStandard::getMinRequiredHoursInCommand
int PilotStandard::getMinRequiredHoursInCommand() const
{ return minRequiredHoursInCommand; }


// Definition of PilotStandard::getMinRequiredLicenseType.
string PilotStandard::getRequiredLicenseType() const
{ return requiredLicenseType; }


// Definition of PilotStandard::getMinRequiredEnglishLevel.
int PilotStandard::getMinRequiredEnglishLevel() const
{ return minRequiredEnglishLevel; }


// Definition of PilotStandard::getRequiredHealthStatus
int PilotStandard::getRequiredHealthStatus() const
{ return requiredHealthStatus; }


// Function PilotStandard::setModelName
void PilotStandard::setModelName(const string &model)
{
    // Array of valid model names.
    const int NUM_MODELS = 4;
    const string validModels[NUM_MODELS] = {
        "BOEING787", "AIRBUSA350", "AIRBUSA321", "AIRBUSA320NEO"
    };

    // Remove spaces and capitalize the model name.
    string processedModel = StringManipulator::removeSpaces(model);
    processedModel = StringManipulator::capitalize(processedModel);

    // Search the model in the array.
    bool isFound = false;

    for (int count = 0; count < NUM_MODELS; count++)
    {
        if (processedModel == validModels[count])
        {
            isFound = true;
            break;
        }
    }

    // If the model is not found, then throw an exception.
    if (!isFound)
    {
        throw InvalidModel();
    }
    // Otherwise, store the model in the member variable.
    modelName = processedModel;
}


// Function PilotStandard::setMinRequiredFlightHours
void PilotStandard::setMinRequiredFlightHours(const int &hours)
{
    // If the argument is negative, then throw an InvalidHours
    // object as an exception.
    if (hours < 0)
    {
        throw InvalidHours();
    }
    // Otherwise, store the argument in the member variable.
    minRequiredFlightHours = hours;
}


// Function PilotStandard::setMinRequiredHoursInCommand
void PilotStandard::setMinRequiredHoursInCommand(const int &hours)
{
    // If the argument is negative or larger than the minRequiredFlightHours,
    // then throw an InvalidHours object as an exception.
    if (hours < 0 || hours > minRequiredFlightHours)
    {
        throw InvalidHours();
    }
    // Otherwise, store the argument in the member variable.
    minRequiredHoursInCommand = hours;
}


// Function PilotStandard::setRequiredLicenseType
void PilotStandard::setRequiredLicenseType(const string &type)
{
    // Array of valid license types.
    const int NUM_LICENSES = 5;
    const string validTypes[NUM_LICENSES] = {
        "SPL", "RPL", "PPL", "CPL", "ATPL"
    };

    // Remove spaces and capitalize the model name.
    string processedType = StringManipulator::removeSpaces(type);
    processedType = StringManipulator::capitalize(processedType);

    // Search for the license type in the array.
    bool isFound = false;

    for (int count = 0; count < NUM_LICENSES; count++)
    {
        if (processedType == validTypes[count])
        {
            isFound = true;
            break;
        }
    }

    // If the license type is not found, then throw an exception.
    if (!isFound)
    {
        throw InvalidType();
    }
    // Otherwise, store the argument in the member variable.
    requiredLicenseType = processedType;
}


// Function PilotStandard::setMinRequiredEnglishLevel.
void PilotStandard::setMinRequiredEnglishLevel(const int &level)
{
    const int MAX_LEVEL = 6;
    const int MIN_LEVEL = 1;
    // If the argument is out of valid range,
    // then throw an InvalidEnglish object as an exception.
    if (level > MAX_LEVEL || level < MIN_LEVEL)
    {
        throw InvalidEnglish();
    }
    // Otherwise, store the argument into the member variable.
    minRequiredEnglishLevel = level;
}


// Function PilotStandard::setRequiredHealthStatus
void PilotStandard::setRequiredHealthStatus(const int &health)
{
    const int MAX_STATUS = 1;
    const int MIN_STATUS = 3;

    // If the argument is out of value range, then throw an
    // InvalidHealth object as an exception.
    if (health > MIN_STATUS || health < MAX_STATUS)
    {
        throw InvalidHealth();
    }
    // Otherwise, store the argument in the member variable.
    requiredHealthStatus = health;
}


// The overloaded cout << operator.
ostream &operator << (ostream &strm, const PilotStandard &obj)
{
    strm << "Model name: " << obj.getModelName() << endl;
    strm << "  Minimum required flight hours: " << obj.getMinRequiredFlightHours() << endl;
    strm << "  Minimum required hours in command: " << obj.getMinRequiredHoursInCommand() << endl;
    strm << "  Required license type: " << obj.getRequiredLicenseType() << endl;
    strm << "  Required health status: " << obj.getRequiredHealthStatus() << endl;
    strm << "  Required English level: " << obj.getMinRequiredEnglishLevel();
    return strm;
}