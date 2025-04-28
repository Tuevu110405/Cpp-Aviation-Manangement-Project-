#ifndef PILOTCERTIFICATE_H
#define PILOTCERTIFICATE_H
#include <string>
#include <iostream>
#include "Date.h"
using namespace std;

class PilotCertificate
{
private:
    string licenseType;     // The pilot's type of license.
    string licenseNumber;   // The pilot's license number.
    Date expiryDate;        // The expiration date of the pilot's license.
public:
    // Class to throw exception when the license type is invalid.
    class InvalidType
    {
    private:
        string type;
    public:
        InvalidType(string t)
            { type = t; }
        string getType() const
            { return type; }
    };

    // Default constructor.
    PilotCertificate()
        { licenseType = licenseNumber = "blank"; }

    // Constructor.
    PilotCertificate(string, string, Date);

    // Accessor functions.
    string getLicenseType() const
        { return licenseType; }
    string getLicenseNumber() const
        { return licenseNumber; }
    Date getExpiryDate() const
        { return expiryDate; }
    
    // Mutator functions.
    void setLicenseType(string);
    void setLicenseNumber(string);
    void setExpiryDate(Date);

    // Overloaded operators.
    friend istream &operator >> (istream &strm, PilotCertificate &);
    friend ostream &operator << (ostream &strm, const PilotCertificate &);

    // Other functions defined in PilotCertificate.cpp.
    bool isLicenseExpired();;
};
#endif