#include "PilotCompetence.h"

// Definition of Constructor.
PilotCompetence::PilotCompetence(int flightHr, int hrInCommand, int english, int health)
{
    try
    {
        setFlightHours(flightHr);
        setHoursInCommand(hrInCommand);
        setEnglishLevel(english);
        setHealthStatus(health);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
// Definition of Mutator functions.
void PilotCompetence::setFlightHours(int hours)
{
    // If the hours is negetive, then thows an exception.
    if (hours < 0)
    {
        throw InvalidHours(hours);
    }
    // Otherwise, store the argument in the member variable.
    flightHours = hours;
}

void PilotCompetence::setHoursInCommand(int hours)
{
    // If the hours is negetive, then thows an exception.
    if (hours < 0 || hours > flightHours)
    {
        throw InvalidHours(hours);
    }
    // Otherwise, store the argument in the member variable.
    hoursInCommand = hours;
}

void PilotCompetence::setEnglishLevel(int level)
{
    // Constants
    const int MAX_LEVEL = 6;
    const int MIN_LEVEL = 1;

    // If the English leve is not from 1 to 6, then thows an exception.
    if (level < MIN_LEVEL || level > MAX_LEVEL)
    {
        throw InvalidEnglish(level);
    }
    // Otherwise, store the argument in the member variable.
    englishLevel = level;
}

void PilotCompetence::setHealthStatus(int status)
{
    // Constants
    const int MAX_STATUS = 1;
    const int MIN_STATUS = 3;

    // If the English leve is not from 1 to 6, then thows an exception.
    if (status > MIN_STATUS || status < MAX_STATUS)
    {
        throw InvalidHeath(status);
    }
    // Otherwise, store the argument in the member variable.
    healthStatus = status;
}

// Overloaded operators.
istream &operator >> (istream &strm, PilotCompetence &obj)
{
    // Variables.
    int flightHr, hrInCommand, english, health;

    // // Prompt user for the total flight hours.
    while (true)
    {
        try
        {
            cout << "Enter pilot's total flight hours: ";
            strm >> flightHr;
            obj.setFlightHours(flightHr);

            break;
        }
        catch (PilotCompetence::InvalidHours h)
        {
            cout << "Error: The value " << h.getValue();
            cout << " is invalid for flight hours.\n";
        }
    }
    // Prompt user for the hours in command.
    while (true)
    {
        try
        {
            cout << "Enter pilot's total hours in command: ";
            strm >> hrInCommand;
            obj.setHoursInCommand(hrInCommand);

            break;
        }
        catch (PilotCompetence::InvalidHours h)
        {
            cout << "Error: The value " << h.getValue();
            cout << " is invalid for hours in command.\n";
        }
    }
    // Prompt user for the English level.
    while (true)
    {
        try
        {
            cout << "Enter pilot's English level (1 - 6): ";
            strm >> english;
            obj.setEnglishLevel(english);

            break;
        }
        catch (PilotCompetence::InvalidEnglish e)
        {
            cout << "Error: The value " << e.getValue();
            cout << " is invalid for English level.\n";
        }
    }
    while (true)
    {
        // Prompt user for the health status.
        try
        {
            cout << "Enter pilot's heath status (1 - 3): ";
            strm >> health;
            obj.setHealthStatus(health);

            break;
        }
        catch (PilotCompetence::InvalidHeath h)
        {
            cout << "Error: The value " << h.getValue();
            cout << " is invalid for health status.\n";
        }
    }

    return strm;
}
ostream &operator << (ostream &strm, const PilotCompetence &obj)
{
    strm << "Pilot's total flight hours: " << obj.getFlightHours() << endl;
    strm << "Pilot's total hours in command: " << obj.getHoursInCommand() << endl;
    strm << "Pilot's English level: Level " << obj.getEnglishLevel() << endl;
    strm << "Pilot's health status: Class " << obj.getHealthStatus();
    return strm;
}