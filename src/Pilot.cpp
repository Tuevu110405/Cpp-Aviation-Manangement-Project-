
#include "../include/Pilot.h"
#include <cctype>

// Definition of constructor
Pilot::Pilot(string n, int a, char g, PilotCompetence competence, PilotCertificate certificate)
{
    name = n;
    age = a;
    gender = g;
    pilotCompetence = competence;
    pilotCertificate = certificate;
}

// Definition of Mutator functions.
void Pilot::setName(string newName)
{   
    // If the name contains invalid character.
    for (int i = 0; i < newName.length(); i++)
    {
        if (!isalpha(newName[i]) && !isspace(newName[i]))
        {
            throw InvalidName(newName);
        }
    }
    // Otherwise
    name = newName;
}

void Pilot::setAge(int newAge)
{
    if (newAge < 0)
    {
        throw InvalidAge(newAge);
    }
    age = newAge;
}

void Pilot::setGender(char newGender)
{
    // Constants.
    const char MALE = 'M';
    const char FEMALE = 'F';

    if (toupper(newGender) != MALE && toupper(newGender) != FEMALE)
    {
        throw InvalidGender(newGender);
    }
    gender = newGender;
}

void Pilot::setPilotCompetence(const PilotCompetence &newCompetence)
{
    pilotCompetence = newCompetence;
}

void Pilot::setPilotCertificate(const PilotCertificate &newCertificate)
{
    pilotCertificate = newCertificate;
}

// Overloaded operators.
istream &operator >> (istream & strm, Pilot &obj)
{
    // Constants.
    const char MALE = 'M';
    const char FEMALE = 'F';

    // Variables.
    string pilotName;
    int pilotAge;
    char pilotGender;

    // Prompt user for the pilot's name.
    while (true)
    {
        try
        {
            cout << "Enter the pilot's name: ";
            getline(strm, pilotName);
            obj.setName(pilotName);

            break;
        }
        catch (Pilot::InvalidName n)
        {
            cout << "Error: The name " << n.getValue();
            cout << " is invalid.\n";
        }
    }

    // Prompt user for the pilot's age.
    while (true)
    {
        try
        {
            cout << "Enter the pilot's age: ";
            strm >> pilotAge;
            obj.setAge(pilotAge);
            
            break;
        }
        catch (Pilot::InvalidAge a)
        {
            cout << "Error: The value " << a.getValue();
            cout << " is invalid for age.\n";
        }
    }

    // Prompt user for pilot's gender.
    while (true)
    {
        try
        {
            cout << "Enter the pilot's gender (M/F): ";
            strm >> pilotGender;
            obj.setGender(pilotGender);

            break;
        }
        catch (Pilot::InvalidGender g)
        {
            cout << "Error: The value " << g.getValue();
            cout << " is invalid for gender.\n";
        }
    }

    // Prompt user for pilot's competence.
    cout << "Enter the pilot's competence.\n";
    strm >> obj.pilotCompetence;

    // Prompt user for pilot's certificate.
    cout << "Enter the pilot's certificate.\n";
    strm >> obj.pilotCertificate;

    return strm;
}

ostream &operator << (ostream & strm, const Pilot &obj)
{
    // Constants.
    const char MALE = 'M';
    const char FEMALE = 'F';

    strm << "Name: " << obj.getName() << endl;
    strm << "Age: " << obj.getAge() << endl;
    strm << "Gender: " << (obj.getGender() == MALE ? "Male" : "Female") << endl;
    strm << "Pilot competence: " << endl;
    strm << obj.getPilotCompetence() << endl;
    strm << "Pilot certificate: " << endl;
    strm << obj.getPilotCertificate();

    return strm;
}

bool Pilot::operator >= (const PilotStandard &standard)
{
    // Constants.
    const char MALE = 'M';
    const char FEMALE = 'F';

    bool isPilotEligible = true;   // A flag to indicate if the pilot exceeds the standards.

    // Check the pilot's age.
    // Get the standard of age.
    int standardAge = (gender == MALE ? standard.getMaxAgeMale() : standard.getMaxAgeFemale());

    if (!isAgeValid(standardAge))
    {
        cout << "The pilot's age is not met" << endl;
        isPilotEligible = false;
    }
    if (pilotCertificate.isLicenseExpired())
    {
        cout << "The pilot's license has expired.\n";
        isPilotEligible = false;
    }
    if (pilotCertificate.getLicenseType() != standard.getRequiredLicenseType())
    {
        cout << "The pilot's license type is not matched. ";
        cout << "Actual: " << pilotCertificate.getLicenseType();
        cout << " Required: " << standard.getRequiredLicenseType() << endl;
        isPilotEligible = false;
    }
    if (pilotCompetence.getFlightHours() < standard.getMinRequiredFlightHours())
    {
        cout << "The pilot's flight hours is not met.";
        cout << " Actual: " << pilotCompetence.getFlightHours();
        cout << " Required: " << standard.getMinRequiredFlightHours() << endl;
        isPilotEligible = false;
    }
    if (pilotCompetence.getHoursInCommand() < standard.getMinRequiredHoursInCommand())
    {
        cout << "The pilot's hours in command is not met.";
        cout << " Actual: " << pilotCompetence.getHoursInCommand();
        cout << " Required: " << standard.getMinRequiredHoursInCommand() << endl;
        isPilotEligible = false;
    }
    if (pilotCompetence.getEnglishLevel() < standard.getMinRequiredEnglishLevel())
    {
        cout << "The pilot's English level is not met.";
        cout << " Actual: Level " << pilotCompetence.getEnglishLevel();
        cout << " Required: Level " << standard.getMinRequiredEnglishLevel() << endl;
        isPilotEligible = false;
    }
    if (pilotCompetence.getHealthStatus() > standard.getRequiredHealthStatus())
    {
        cout << "The pilot's health is not met.";
        cout << " Actual: Class " << pilotCompetence.getHealthStatus();
        cout << " Required: Class " << standard.getRequiredHealthStatus() << endl;
        isPilotEligible = false;
    }

    return isPilotEligible;
}

// Other functions.
bool Pilot::isAgeValid(int pilotAge)
{
    if (age <= pilotAge && pilotAge >= 18)
        return true;
    return false;
}
