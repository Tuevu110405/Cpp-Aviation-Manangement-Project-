#include "../include/PilotInspectionResult.h"

// Default constructor.
PilotInspectionResult::PilotInspectionResult() : InspectionResult()
{
    flightHoursResult = false;
    hoursInCommandResult = false;
    englishLevelResult = false;
    healthStatusResult = false;
    licenseTypeResult = false;
    licenseExpiryResult = false;
    setInspectionResult();
}

// Constructor.
PilotInspectionResult::PilotInspectionResult(string t) : InspectionResult(t)
{
    flightHoursResult = false;
    hoursInCommandResult = false;
    englishLevelResult = false;
    healthStatusResult = false;
    licenseTypeResult = false;
    licenseExpiryResult = false;
    setInspectionResult();
}

// Function PilotInspectionResult::setFlightHoursResult
void PilotInspectionResult::setFlightHoursResult(bool result)
{
    flightHoursResult = result;
    setInspectionResult();
}

// Function PilotInspectionResult::setHoursInCommandResult
void PilotInspectionResult::setHoursInCommandResult(bool result)
{
    hoursInCommandResult = result;
    setInspectionResult();
}

// Function PilotInspectionResult::setEnglishLevelResult
void PilotInspectionResult::setEnglishLevelResult(bool result)
{
    englishLevelResult = result;
    setInspectionResult();
}

// Function PilotInspectionResult::setHealthStatusResult
void PilotInspectionResult::setHealthStatusResult(bool result)
{
    healthStatusResult = result;
    setInspectionResult();
}

// Function PilotInspectionResult::setLicenseExpiryResult
void PilotInspectionResult::setLicenseExpiryResult(bool result)
{
    licenseExpiryResult = result;
    setInspectionResult();
}

// Function PilotInspectionResult::setLicenseTypeResult
void PilotInspectionResult::setLicenseTypeResult(bool result)
{
    licenseTypeResult = result;
    setInspectionResult();
}

// Virtual funciton PilotInspectionResult::setInspectionResult
void PilotInspectionResult::setInspectionResult()
{
    inspectionResult = (flightHoursResult &&
                        hoursInCommandResult &&
                        englishLevelResult &&
                        healthStatusResult &&
                        licenseExpiryResult &&
                        licenseTypeResult);
}