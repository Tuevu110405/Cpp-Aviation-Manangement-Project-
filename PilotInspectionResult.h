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
    PilotInspectionResult(const string &t);

    // Mutator functions.
    void setFlightHoursResult(const bool &result);
    void setHoursInCommandResult(const bool &result);
    void setEnglishLevelResult(const bool &result);
    void setHealthStatusResult(const bool &result);
    void setLicenseExpiryResult(const bool &result);
    void setLicenseTypeResult(const bool &result);
    
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