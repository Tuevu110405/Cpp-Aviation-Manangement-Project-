#ifndef PILOTINSPECTIONRESULT_H
#define PILOTINSPECTIONRESULT_H
#include "InspectionResult.h"

class PilotInspectionResult : public InspectionResult
{
protected:
    bool flightHoursResult;
    bool hoursInCommandResult;
    bool englishLevelResult;
    bool healthStatusResult;
    bool licenseTypeResult;
    bool licenseExpiryResult;

    string flightHoursNote;
    string hoursInCommandNote;
    string englishLevelNote;
    string healthStatusNote;
    string licenseTypeNote;
    string licenseExpiryNote;

    virtual void setInspectionResult() override;
public:
    // Default constructor.
    PilotInspectionResult();

    // Constructor
    PilotInspectionResult(const string &t);

    // Mutator functions.
    void setFlightHoursResult(const bool &result);
    void setHoursInCommandResult(const bool &result);
    void setEnglishLevelResult(const bool &result);
    void setHealthStatusResult(const bool &result);
    void setLicenseExpiryResult(const bool &result);
    void setLicenseTypeResult(const bool &result);
    
    void setFlightHoursNote(const string &note);
    void setHoursInCommandNote(const string &note);
    void setEnglishLevelNote(const string &note);
    void setHealthStatusNote(const string &note);
    void setLicenseTypeNote(const string &note);
    void setLicenseExipiryNote(const string &note);
    
    
    // Accessor functions.
    bool getFlightHoursResult() const
        { return flightHoursResult; }
    
    bool getHoursInCommandResult() const
        { return hoursInCommandResult; }
    
    bool getEnglishLevelResult() const
        { return englishLevelResult; }
    
    bool getHealthStatusResult() const
        { return healthStatusResult; }
    
    bool getLicenseExpiryResult() const
        { return licenseExpiryResult; }

    bool getLicenseTypeResult() const
        { return licenseTypeResult; }

    string getFlightHoursNote() const
        { return flightHoursNote; }
    
    string getHoursInCommandNote() const
        { return hoursInCommandNote; }
    
    string getEnglishLevelNote() const 
        { return englishLevelNote; }
    
    string getHealthStatusNote() const
        { return healthStatusNote; }

    string getLicenseTypeNote() const
        { return licenseTypeNote; }

    string getLicenseExpiryNote() const
        { return licenseExpiryNote; }
    
    // Destructor.
    virtual ~PilotInspectionResult() { };
};

#endif