#include "../include/PilotCertificate.h"
#include <ctime>
#include <cctype>
#include "../include/StringManipulator.h"

// Definition of constructor.
PilotCertificate::PilotCertificate(string type, Date date)
{
    // Try to store argument in the member variables.
    try
    {
        setLicenseType(type);
        setExpiryDate(date);
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
    string processedType = StringManipulator::removeSpaces(type);
    processedType = StringManipulator::capitalize(processedType); 

    // Search for the license type in the array.
    bool isFound = false;

    for (int i = 0; i < NUM_OF_TYPES; i++)
    {
        if (processedType == validLicenseType[i])
        {
            isFound = true;
            break;
        }
    }

    // If the license type is not found in the array, throws
    // an InvalidType object as an exception.
    if (!isFound)
    {
        throw InvalidType(processedType);
    }
    licenseType = processedType;
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
