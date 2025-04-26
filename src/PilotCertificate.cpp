#include "../include/PilotCertificate.h"
#include <ctime>
#include <cctype>

// Definition of constructor.
PilotCertificate::PilotCertificate(string type, string number, Date date)
{
    // Try to store argument in the member variables.
    try
    {
        licenseType = type;
        licenseNumber = number;
        expiryDate = date;
    }
    // Handle the exception when the license type is invalid.
    catch (InvalidType e)
    {
        throw e;
    }
}

// Definition of Mutator functions.
void PilotCertificate::setLicenseType(string type)
{
    // An array of valid license types.
    const int NUM_OF_TYPES = 5;
    const string validLicenseType[NUM_OF_TYPES] = {"SPL", "RPL", "PPL", "CPL", "ATPL"};

    // Convert the license type into uppercase.
    string output = "";

    for (int i = 0; i < type.length(); i++)
    {
        // Check if the license type contains invalid characters.
        if (!isalpha(type[i]) && !isspace(type[i]))
        {
            throw InvalidType(type);
        }
        // Convert the license type into uppercase.
        if (isalpha(type[i]))
        {
            output += toupper(type[i]);
        }
    }

    // Validate the license type.
    bool isFound = false;

    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        if (output == validLicenseType[i])
        {
            licenseType = output;
            isFound = true;
        }
    }

    if (!isFound)
    {
        throw InvalidType(output);
    }
    
}

void PilotCertificate::setLicenseNumber(string number)
{
    licenseNumber = number;
}

void PilotCertificate::setExpiryDate(Date date)
{
    expiryDate = date;
}

// Overloaded operators.
istream &operator >> (istream &strm, PilotCertificate &obj)
{   
    // Variables.
    string type;

    while (true)
    {
        try
        {
            cout << "Enter pilot's license type: ";
            cin.ignore();
            getline(strm, type);
            obj.setLicenseType(type);

            cout << "Enter pilot's license number: ";
            getline(strm, obj.licenseNumber);

            cout << "Enter the expiration date of the license.\n";
            strm >> obj.expiryDate;
            break;
        }
        catch (PilotCertificate::InvalidType e)
        {
            cout << "Error: Invalid license type " << e.getType() << endl;
            cout << "Enter again." << endl;
        }
    }

    return strm;
}

ostream &operator << (ostream &strm, const PilotCertificate &obj)
{
    strm << "Pilot's license type: " << obj.getLicenseType() << endl;
    strm << "Pilot's license number: " << obj.getLicenseNumber() << endl;
    strm << "License's expiration date: " << obj.getExpiryDate();

    return strm;
}

// Other functions defined in PilotCertificate.cpp.
bool PilotCertificate::isLicenseExpired()
{
    // Get the curren month, day, and year.
    time_t now = time(0);          // Get current system time as a raw time value.
    tm* ltm = localtime(&now);     // Convert raw time into local time structure (calendar form).
    
    int day = ltm->tm_mday;        // Extract the day of the month (1-31).
    int month = 1 + ltm->tm_mon;   // Extract the month (0-11), add 1 to convert to (1-12).
    int year = 1900 + ltm->tm_year;// Extract the year since 1900, add 1900 to get full year.

    // Create a Date object for the current date.
    Date currentDate(month, day, year);

    // Check the expiration of the license.
    if (currentDate > expiryDate)
        return true;
    return false;
}
