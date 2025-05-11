#ifndef PILOTCOMPETENCE_H
#define PILOTCOMPETENCE_H
#include <iostream>
using namespace std;

class PilotCompetence
{
private:
    int flightHours;    // The pilot's total flight hours.
    int hoursInCommand; // The pilot's hours in command.
    int englishLevel;   // The pilot's English level.
    int healthStatus;   // The pilot's health status.
public:
    // Class for throwing exception when hours is invalid.
    class InvalidHours
    {
    private:
        int value;
    public:
        InvalidHours(const int &h)
            { value = h; }
        int getValue() const
            { return value; }
    };

    // Class for throwing exception when English level is invalid.
    class InvalidEnglish
    {
    private:
        int value;
    public:
        InvalidEnglish(const int &l)
            { value = l; }
        int getValue() const
            { return value; }
    };

    // Class for throwing exception when health status is invalid.
    class InvalidHealth
    {
    private:
        int value;
    public:
        InvalidHealth(const int &h)
            { value = h; }
        int getValue() const
            { return value; }
    };
    
    // Default constructor.
    PilotCompetence()
        {flightHours = 0; hoursInCommand = 0; englishLevel = 0; healthStatus = 0; }
    
    // Constructor.
    PilotCompetence(const int &flightHr, const int &hrInCommand, const int &english, const int &health);

    // Accessor functions.
    int getFlightHours() const
        { return flightHours; }
    int getHoursInCommand() const
        { return hoursInCommand; }
    int getEnglishLevel() const
        { return englishLevel; }
    int getHealthStatus() const
        { return healthStatus; }
    
    // Mutator functions.
    void setFlightHours(const int &hours);
    void setHoursInCommand(const int &hours);
    void setEnglishLevel(const int &level);
    void setHealthStatus(const int &status);

    // Overloaded operators.
    friend istream &operator >> (istream &, PilotCompetence &);
    friend ostream &operator << (ostream &, const PilotCompetence &);
};
#endif