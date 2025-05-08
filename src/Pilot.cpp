#include "../include/Pilot.h"
#include <cctype>

// Definition of constructor.
Pilot::Pilot(string n, PilotCompetence competence, PilotCertificate certificate)
{
    try
    {
        setName(n);
        setPilotCompetence(competence);
        setPilotCertificate(certificate);
    }
    catch (InvalidName errorName)
    {
        throw errorName;
    }
}


// Function Pilot::setName
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


// Pilot::setPilotCompetence
void Pilot::setPilotCompetence(const PilotCompetence &newCompetence)
{
    pilotCompetence = newCompetence;
}


// Function Pilot::setPilotCertificate
void Pilot::setPilotCertificate(const PilotCertificate &newCertificate)
{
    pilotCertificate = newCertificate;
}


// Overloaded operator >>
istream &operator >> (istream & strm, Pilot &obj)
{
    // Variables declaration.
    string pilotName;

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

    // Prompt user for pilot's competence.
    cout << "Enter the pilot's competence.\n";
    strm >> obj.pilotCompetence;

    // Prompt user for pilot's certificate.
    cout << "Enter the pilot's certificate.\n";
    strm >> obj.pilotCertificate;

    return strm;
}


// Overloaded operator <<
ostream &operator << (ostream & strm, const Pilot &obj)
{
    // Display pilot's information.
    strm << "Name: " << obj.getName() << endl;
    strm << "Pilot competence: " << endl;
    strm << obj.getPilotCompetence() << endl;
    strm << "Pilot certificate: " << endl;
    strm << obj.getPilotCertificate();

    return strm;
}