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
    virtual void setInspectionResult() override;
public:
    // Default constructor.
    PilotInspectionResult();

    // Constructor
    PilotInspectionResult(string t);

    // Mutator functions.
    void setFlightHoursResult(bool);
    void setHoursInCommandResult(bool);
    void setEnglishLevelResult(bool);
    void setHealthStatusResult(bool);
    void setLicenseExpiryResult(bool);
    void setLicenseTypeResult(bool);
    
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
    
    // Destructor.
    virtual ~PilotInspectionResult() { };
};

#endif