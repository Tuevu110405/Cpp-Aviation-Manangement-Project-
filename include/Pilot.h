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
    string name;    // The pilot's name.
    int age;        // The pilot's age.
    char gender;    // The pilot's gender.
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
        InvalidName(string n)
            { value = n; }
        string getValue() const
            { return value; }
    };

    // Class for throwing exception when the pilot's 
    // age is invalid.
    class InvalidAge
    {
    private:
        int value;
    public:
        InvalidAge(int a)
            { value = a; }
        int getValue() const
            { return value; }
    };

    // Class for throwing exception when the pilot's
    // gender is invalid.
    class InvalidGender
    {
    private:
        char value;
    public:
        InvalidGender(char g)
            { value = g; }
        char getValue() const
            { return value; }
    };

    // Default constructor.
    Pilot()
        { name = "blank"; gender = ' '; age = 0; }
    
    // Constructor.
    Pilot(string, int, char, PilotCompetence, PilotCertificate);

    // Accessor functions.
    string getName() const
        { return name; }
    int getAge() const
        { return age; }
    char getGender() const
        { return gender; }
    PilotCompetence getPilotCompetence() const
        { return pilotCompetence; }
    PilotCertificate getPilotCertificate() const
        { return pilotCertificate; }
    
    // Mutator functions.
    void setName(string);
    void setAge(int);
    void setGender(char);
    void setPilotCompetence(const PilotCompetence &);
    void setPilotCertificate(const PilotCertificate &);

    // Overloaded operators.
    friend istream &operator >> (istream &, Pilot &);
    friend ostream &operator << (ostream &, const Pilot &);
    bool operator >= (const PilotStandard&);

    // Other functions.
    bool isAgeValid(int);
};
#endif