#include "../include/FlightInspection.h"
#include "../include/WeatherStandardVN.h" 
#include "../include/WeatherStandard.h"
#include "../include/Flight.h"
#include "../include/Weather.h"
#include <bits/stdc++.h>
using namespace std;

// Function FlightInspection::inspectWeather (Tue)
WeatherInspectionResult FlightInspection::inspectWeather(Flight& flight, WeatherStandardVN& weatherStandard) {
    WeatherInspectionResult weatherInspectionResult = flight.getWeatherInspectionResult();
    // Check if the weather is satisfactory, if not, check and set status for each quality
    if(weatherStandard.isWeatherAcceptable(flight.getWeather())){
        weatherInspectionResult.setIsCrosswind(true);
        weatherInspectionResult.setIsTemperature(true);
        weatherInspectionResult.setIsThunderstorm(true);
        weatherInspectionResult.setIsTailwind(true);
        weatherInspectionResult.setIsHorizontalVisibility(true);
        weatherInspectionResult.setIsVisibility(true);
        weatherInspectionResult.setInspectionResult(true);
    }
    else{

        if(flight.getWeather().getVisibility() < weatherStandard.getVisibility()){
            weatherInspectionResult.setIsVisibility(false);
        }
        else{
            weatherInspectionResult.setIsVisibility(true);
        }

        if(flight.getWeather().getCrosswind() > weatherStandard.getCrosswind()){
            weatherInspectionResult.setIsCrosswind(false);
        }
        else{
            weatherInspectionResult.setIsCrosswind(true);
        }

        if(flight.getWeather().getTemperature() < weatherStandard.getTemperatureLowerBound() || flight.getWeather().getTemperature() > weatherStandard.getTemperatureUpperBound()){
            weatherInspectionResult.setIsTemperature(false);
        }
        else{
            weatherInspectionResult.setIsTemperature(true);
        }

        if(flight.getWeather().getThunderstorm() > weatherStandard.getThunderstorm()){
            weatherInspectionResult.setIsThunderstorm(false);
        }
        else{
            weatherInspectionResult.setIsThunderstorm(true);
        }

        if(flight.getWeather().getTailwind() > weatherStandard.getTailwind()){
            weatherInspectionResult.setIsTailwind(false);
        }
        else{
            weatherInspectionResult.setIsTailwind(true);
        }

        if(flight.getWeather().getHorizontalVisibility() < weatherStandard.getHorizontalVisibility()){
            weatherInspectionResult.setIsHorizontalVisibility(false);
        }
        else{
            weatherInspectionResult.setIsHorizontalVisibility(true);
        }
    }

    return weatherInspectionResult;
}


// Function FlightInspection::inspectPilot (Hoang)
PilotInspectionResult FlightInspection::inspectPilot(const Pilot &pilotInfo, const PilotStandard &standard)
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
        result.setFlightHoursNote("Flight hours do not meet. (Actual: " + to_string(pilotHours) + " hours, " +
        "Required: " + to_string(requiredHours) + " hours.)");
    }
    else
    {
        // Set the flight hours result to true.
        result.setFlightHoursResult(true);
        // Add a blank note to the result.
        result.setFlightHoursNote("");
    }

    // Inspect the pilot's hours in command.
    pilotHours = pilotInfo.getPilotCompetence().getHoursInCommand();
    requiredHours = standard.getMinRequiredHoursInCommand();

    if (pilotHours < requiredHours)
    {
        // Set the hours in command result to false.
        result.setHoursInCommandResult(false);
        // Add note to the result.
        result.setHoursInCommandNote("Hours in command do not meet. (Actual: " + to_string(pilotHours) + " hours, " +
        "Required: " + to_string(requiredHours) + " hours.)");
    }
    else
    {
        // Set the hours in command result to true.
        result.setHoursInCommandResult(true);
        // Add a blank note to the result.
        result.setHoursInCommandNote("");
    }

    // Inspect the pilot's English level.
    int pilotEnglish = pilotInfo.getPilotCompetence().getEnglishLevel();
    int requiredEnglish = standard.getMinRequiredEnglishLevel();

    if (pilotEnglish < requiredEnglish)
    {
        // Set the English result to false.
        result.setEnglishLevelResult(false);
        // Add note to the result.
        result.setEnglishLevelNote("English level does not meet. (Actual: Level " + to_string(pilotEnglish) +
        ", Required: Level " + to_string(requiredEnglish) + ")");
    }
    else
    {
        // Set the English result to true.
        result.setEnglishLevelResult(true);
        // Add a blank note to the result.
        result.setEnglishLevelNote("");
    }

    // Inspect the pilot's Health status.
    int pilotHealth = pilotInfo.getPilotCompetence().getHealthStatus();
    int requiredHealth = standard.getRequiredHealthStatus();

    if (pilotHealth > requiredHealth)
    {
        // Set the health result to false.
        result.setHealthStatusResult(false);
        // Add note to the result.
        result.setHealthStatusNote("Health does not meet. (Actual: Status " + to_string(pilotHealth) +
        ", Required: Status " + to_string(requiredHealth) + ")");
    }
    else
    {
        // Set the health result to true.
        result.setHealthStatusResult(true);
        // Add a blank note to the result.
        result.setHealthStatusNote("");
    }

    // Inspect the pilot's license type.
    string pilotLicenseType = pilotInfo.getPilotCertificate().getLicenseType();
    string requiredType = standard.getRequiredLicenseType();

    if (pilotLicenseType != requiredType)
    {
        // Set the license type result to false.
        result.setLicenseTypeResult(false);
        // Add note to the result.
        result.setLicenseTypeNote("License type does not meet. (Actual: " + pilotLicenseType +
        ", Required: " + requiredType + ")");
    }
    else
    {
        // Set the license type result to true.
        result.setLicenseTypeResult(true);
        // Add a blank note to the result.
        result.setLicenseTypeNote("");
    }

    // Inspect the license expiry date.
    // Get the current month, day, and year.
    time_t now = time(0);          // Get current system time as a raw time value.
    tm* ltm = localtime(&now);     // Convert raw time into local time structure (calendar form).
    
    int day = ltm->tm_mday;        // Extract the day of the month (1-31).
    int month = 1 + ltm->tm_mon;   // Extract the month (0-11), add 1 to convert to (1-12).
    int year = 1900 + ltm->tm_year;// Extract the year since 1900, add 1900 to get full year.

    // Create a Date object for the current date.
    Date currentDate(month, day, year);

    if (currentDate > pilotInfo.getPilotCertificate().getExpiryDate())
    {
        // Set the license expiry result to false.
        result.setLicenseExpiryResult(false);
        // Add note to the result.
        result.setLicenseExipiryNote("License has expired.");
    }
    else
    {
        // Set the license expiry result to true.
        result.setLicenseExpiryResult(true);
        // Add a blank note to the result.
        result.setLicenseExipiryNote("");
    }

    return result;
}