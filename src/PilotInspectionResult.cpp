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
PilotInspectionResult::PilotInspectionResult(const string &t) : InspectionResult(t)
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
void PilotInspectionResult::setFlightHoursResult(const bool &result)
{
    // Set the result.
    flightHoursResult = result;
    // Update the overall result.
    setInspectionResult();
}

// Function PilotInspectionResult::setHoursInCommandResult
void PilotInspectionResult::setHoursInCommandResult(const bool &result)
{
    // Set the result.
    hoursInCommandResult = result;
    // Update the overall result.
    setInspectionResult();
}

// Function PilotInspectionResult::setEnglishLevelResult
void PilotInspectionResult::setEnglishLevelResult(const bool &result)
{
    // Set the result.
    englishLevelResult = result;
    // Update the overall result.
    setInspectionResult();
}

// Function PilotInspectionResult::setHealthStatusResult
void PilotInspectionResult::setHealthStatusResult(const bool &result)
{
    // Set the result.
    healthStatusResult = result;
    // Update the overall result.
    setInspectionResult();
}

// Function PilotInspectionResult::setLicenseExpiryResult
void PilotInspectionResult::setLicenseExpiryResult(const bool &result)
{
    // Set the result.
    licenseExpiryResult = result;
    // Update the overall result.
    setInspectionResult();
}

// Function PilotInspectionResult::setLicenseTypeResult
void PilotInspectionResult::setLicenseTypeResult(const bool &result)
{
    // Set the result.
    licenseTypeResult = result;
    // Update the overall result.
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