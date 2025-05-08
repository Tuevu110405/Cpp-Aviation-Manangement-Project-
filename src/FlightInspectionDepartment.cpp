#include "../include/FlightInspectionDepartment.h"


// Function FlightInspectionDepartment::inspectPilot (Hoang)
PilotInspectionResult FlightInspectionDepartment::inspectPilot(const Pilot &pilotInfo, const PilotStandard &standard)
{
    PilotInspectionResult result("Pilot");

    // Inspect the pilot's flight hours. 
    int pilotHours = pilotInfo.getPilotCompetence().getFlightHours();
    int requiredHours = standard.getMinRequiredFlightHours();
    
    if (pilotHours < requiredHours)
    {
        // Set the flight hours result to false.
        result.setFlightHoursResult(false);
        // Add note to the result.
        result.addNote("Flight hours does not meet. (Actual: " + to_string(pilotHours) + " hours, " +
        "Required: " + to_string(requiredHours) + " hours.)");
    }
    else
    {
        result.setFlightHoursResult(true);
    }

    // Inspect the pilot's hours in command.
    pilotHours = pilotInfo.getPilotCompetence().getHoursInCommand();
    requiredHours = standard.getMinRequiredHoursInCommand();

    if (pilotHours < requiredHours)
    {
        // Set the hours in command result to false.
        result.setHoursInCommandResult(false);
        // Add note to the result.
        result.addNote("Hours in command does not meet. (Actual: " + to_string(pilotHours) + " hours, " +
        "Required: " + to_string(requiredHours) + " hours.)");
    }
    else
    {
        result.setHoursInCommandResult(true);
    }

    // Inspect the pilot's English level.
    int pilotEnglish = pilotInfo.getPilotCompetence().getEnglishLevel();
    int requiredEnglish = standard.getMinRequiredEnglishLevel();

    if (pilotEnglish < requiredEnglish)
    {
        // Set the English result to false.
        result.setEnglishLevelResult(false);
        // Add note to the result.
        result.addNote("English level does not meet. (Actual: Level " + to_string(pilotEnglish) +
        "Required: Level " + to_string(requiredEnglish) + ")");
    }
    else
    {
        result.setEnglishLevelResult(true);
    }

    // Inspect the pilot's Health status.
    int pilotHealth = pilotInfo.getPilotCompetence().getHealthStatus();
    int requiredHealth = standard.getRequiredHealthStatus();

    if (pilotHealth < requiredHealth)
    {
        // Set the health result to false.
        result.setHealthStatusResult(false);
        // Add note to the result.
        result.addNote("Health does not meet. (Actual: Status " + to_string(pilotHealth) +
        "Required: Status " + to_string(requiredHealth) + ")");
    }
    else
    {
        result.setHealthStatusResult(true);
    }

    // Inspect the pilot's license type.
    string pilotLicenseType = pilotInfo.getPilotCertificate().getLicenseType();
    string requiredType = standard.getRequiredLicenseType();

    if (pilotLicenseType != requiredType)
    {
        // Set the license type result to false.
        result.setLicenseTypeResult(false);
        // Add note to the result.
        result.addNote("License type does not meet. (Actual: " + pilotLicenseType +
        "Required: " + requiredType + ")");
    }
    else
    {
        result.setLicenseTypeResult(true);
    }

    // Inspect the license expiry date.
    if (pilotInfo.getPilotCertificate().isLicenseExpired())
    {
        // Set the license expiry result to false.
        result.setLicenseExpiryResult(false);
        // Add note to the result.
        result.addNote("License has expired.");
    }
    else
    {
        result.setLicenseExpiryResult(true);
    }

    return result;
}

