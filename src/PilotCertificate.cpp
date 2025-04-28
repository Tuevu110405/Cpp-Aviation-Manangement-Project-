#include "PilotCertificate.h"
#include <ctime>
#include <cctype>

// Definition of constructor.
PilotCertificate::PilotCertificate(string type, string number, Date date)
{
    // Try to store argument in the member variables.
    try
    {
        setLicenseType(type);
        licenseNumber = number;
        expiryDate = date;
    }
    // Handle the exception when the license type is invalid.
    catch (InvalidType e)
    {
        throw e;
    }
}

// Definition of PilotCertificate::setLicenseType
void PilotCertificate::setLicenseType(string type)
{
    // An array of valid license types.
    const int NUM_OF_TYPES = 5;
    const string validLicenseType[NUM_OF_TYPES] = {"SPL", "RPL", "PPL", "CPL", "ATPL"};

    // Convert the license type into uppercase.
    string output = "";

    // Scanning the input from left to right.
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

    // Search for the license type in the array.
    bool isFound = false;

    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        if (output == validLicenseType[i])
        {
            licenseType = output;
            isFound = true;
            break;
        }
    }

    // If the license type is not found in the array, throws
    // an InvalidType object as an exception.
    if (!isFound)
    {
        throw InvalidType(output);
    }
    
}

// Definition of PilotCertificate::setLicenseNumber
void PilotCertificate::setLicenseNumber(string number)
{
    licenseNumber = number;
}

// Definition of PilotCertificate::setExpiryDate
void PilotCertificate::setExpiryDate(Date date)
{
    expiryDate = date;
}

// Overloaded operator: cin >>
istream &operator >> (istream &strm, PilotCertificate &obj)
{   
    // Variables.
    string type;    // Hold the license type.

    // Prompt user for input.
    while (true)
    {
        try
        {
            cout << "Enter pilot's license type: ";
            getline(strm, type);
            obj.setLicenseType(type);

            cout << "Enter pilot's license number: ";
            getline(strm, obj.licenseNumber);

            cout << "Enter the expiration date of the license.\n";
            strm >> obj.expiryDate;     // Calling cin >> in the Date class.

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

// Overloaded operator: cout <<
ostream &operator << (ostream &strm, const PilotCertificate &obj)
{
    strm << "Pilot's license type: " << obj.getLicenseType() << endl;
    strm << "Pilot's license number: " << obj.getLicenseNumber() << endl;
    strm << "License's expiration date: " << obj.getExpiryDate();

    return strm;
}

// Definition of PilotCertificate::isLicenseExpired
bool PilotCertificate::isLicenseExpired()
{
    // Get the current month, day, and year.
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
