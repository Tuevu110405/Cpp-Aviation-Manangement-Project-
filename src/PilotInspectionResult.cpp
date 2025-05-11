#include "../include/PilotInspectionResult.h"

// Default constructor.
PilotInspectionResult::PilotInspectionResult() : InspectionResult()
{
    flightHoursResult = false;
    flightHoursNote = "Not checked yet";

    hoursInCommandResult = false;
    hoursInCommandNote = "Not checked yet";

    englishLevelResult = false;
    englishLevelNote = "Not checked yet";

    healthStatusResult = false;
    healthStatusNote = "Not checked yet";

    licenseTypeResult = false;
    licenseTypeNote = "Not checked yet";

    licenseExpiryResult = false;
    licenseExpiryNote = "Not checked yet";

    setInspectionResult();
}

// Constructor.
PilotInspectionResult::PilotInspectionResult(const string &t) : InspectionResult(t)
{
flightHoursResult = false;
    flightHoursNote = "Not checked yet";

    hoursInCommandResult = false;
    hoursInCommandNote = "Not checked yet";

    englishLevelResult = false;
    englishLevelNote = "Not checked yet";

    healthStatusResult = false;
    healthStatusNote = "Not checked yet";

    licenseTypeResult = false;
    licenseTypeNote = "Not checked yet";

    licenseExpiryResult = false;
    licenseExpiryNote = "Not checked yet";

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

// Function PilotInspectionResult::setFlighHoursNote
void PilotInspectionResult::setFlightHoursNote(const string &note)
{
    flightHoursNote = note;
}

// Function PilotInspectionResult::setHoursInCommand
void PilotInspectionResult::setHoursInCommandNote(const string &note)
{
    hoursInCommandNote = note;
}

// Function PilotInspectionResult::setEnglishLevelNote
void PilotInspectionResult::setEnglishLevelNote(const string &note)
{
    englishLevelNote = note;
}

// Function PilotInspectionResult::setHealthStatusNote
void PilotInspectionResult::setHealthStatusNote(const string &note)
{
    healthStatusNote = note;
}

// Function PilotInspectionResult::setLicenseTypeNote
void PilotInspectionResult::setLicenseTypeNote(const string &note)
{
    licenseTypeNote = note;
}

// Function PilotInspectionResult::setLicenseExpiryNote
void PilotInspectionResult::setLicenseExipiryNote(const string &note)
{
    licenseExpiryNote = note;
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
