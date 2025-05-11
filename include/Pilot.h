#ifndef PILOT_H
#define PILOT_H
#include "PilotCompetence.h"
#include "PilotCertificate.h"
#include "PilotStandard.h"
#include <string>
#include <iostream>
using namespace std;

class Pilot
{
private:
    string name;                        // The pilot's name.
    PilotCompetence pilotCompetence;    // The pilot's competence.
    PilotCertificate pilotCertificate;  // The pilot's certificate.
public:
    // Class for throwing exception when the pilot's
    // name is invalid.
    class InvalidName
    {
    private:
        string value;
    public:
        InvalidName(const string &n)
            { value = n; }
        string getValue() const
            { return value; }
    };

    // Default constructor.
    Pilot()
        { name = ""; }
    
    // Constructor.
    Pilot(const string &pilotName, const PilotCompetence &competence, const PilotCertificate &certificate);

    // Accessor functions.
    string getName() const
        { return name; }
    PilotCompetence getPilotCompetence() const
        { return pilotCompetence; }
    PilotCertificate getPilotCertificate() const
        { return pilotCertificate; }
    
    // Mutator functions.
    void setName(const string &newName);
    void setPilotCompetence(const PilotCompetence &newCompetence);
    void setPilotCertificate(const PilotCertificate &newCertificate);

    // Overloaded operators.
    friend istream &operator >> (istream &, Pilot &);
    friend ostream &operator << (ostream &, const Pilot &);
};
#endif