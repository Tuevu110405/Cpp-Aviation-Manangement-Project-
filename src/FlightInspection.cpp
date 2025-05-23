#include "../include/FlightInspection.h"
#include "../include/WeatherStandardVN.h" 
#include "../include/WeatherStandard.h"
#include "../include/Flight.h"
#include "../include/Weather.h"
#include <bits/stdc++.h>

using namespace std;

// Function FlightInspection::inspectWeather (Tue)
WeatherInspectionResult FlightInspection::inspectWeather(const Weather& weather, const WeatherStandardVN& weatherStandard) {
    WeatherInspectionResult weatherInspectionResult ;
    // Check if the weather is satisfactory, if not, check and set status for each quality
    if(weatherStandard.isWeatherAcceptable(weather)){
        weatherInspectionResult.setIsCrosswind(true);
        weatherInspectionResult.setIsTemperature(true);
        weatherInspectionResult.setIsThunderstorm(true);
        weatherInspectionResult.setIsTailwind(true);
        weatherInspectionResult.setIsHorizontalVisibility(true);
        weatherInspectionResult.setIsVisibility(true);
        weatherInspectionResult.setInspectionResult(true);
    }
    else if(!weatherStandard.isWeatherAcceptable(weather)){

        if(!weatherStandard.isVisibility(weather)){
            weatherInspectionResult.setIsVisibility(false);
        }
        // else{
        //     weatherInspectionResult.setIsVisibility(true);
        // }

        if(!weatherStandard.isCrosswind(weather)){
            weatherInspectionResult.setIsCrosswind(false);
        }
        // else{
        //     weatherInspectionResult.setIsCrosswind(true);
        // }

        if(!weatherStandard.isTemperature(weather)){
            weatherInspectionResult.setIsTemperature(false);
        }
        // else{
        //     weatherInspectionResult.setIsTemperature(true);
        // }

        if(!weatherStandard.isThunderstorm(weather)){
            weatherInspectionResult.setIsThunderstorm(false);
        }
        // else{
        //     weatherInspectionResult.setIsThunderstorm(true);
        // }

        if(!weatherStandard.isTailwind(weather)){
            weatherInspectionResult.setIsTailwind(false);
        }
        // else{
        //     weatherInspectionResult.setIsTailwind(true);
        // }

        if(!weatherStandard.isHorizontalVisibility(weather)){
            weatherInspectionResult.setIsHorizontalVisibility(false);
        }
        // else{
        //     weatherInspectionResult.setIsHorizontalVisibility(true);
        // }
        weatherInspectionResult.setInspectionResult(false);
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
        result.setFlightHoursNote("(Actual: " + to_string(pilotHours) + " hours, " +
        "Required: " + to_string(requiredHours) + " hours).");
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
        result.setHoursInCommandNote("(Actual: " + to_string(pilotHours) + " hours, " +
        "Required: " + to_string(requiredHours) + " hours).");
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
        result.setEnglishLevelNote("(Actual: Level " + to_string(pilotEnglish) +
        ", Required: Level " + to_string(requiredEnglish) + ").");
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
        result.setHealthStatusNote("(Actual: Status " + to_string(pilotHealth) +
        ", Required: Status " + to_string(requiredHealth) + ").");
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
        result.setLicenseTypeNote("(Actual: " + pilotLicenseType +
        ", Required: " + requiredType + ").");
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
double FlightInspection::calculateMinFuelNeed(const Flight &flight)
{
    Destination dep, arr;
    if (!flight.getLocation().getDestinationByCode(flight.getDepartureCode(), dep) ||
        !flight.getLocation().getDestinationByCode(flight.getArrivalCode(), arr)) {
        cerr << "Invalid airport codes" << endl;
        return -1;
    }

    double distance = flight.getLocation().calculateDistanceInKM(dep.latitude, dep.longitude, arr.latitude, arr.longitude);
    double speed = flight.getPlane()->getSpeed();
    double time = distance / speed;
    double minFuel = time * flight.getPlane()->getFuel_consumption_rate();
    if(flight.getLocation().isOceanicFlight(dep.latitude, dep.longitude, arr.latitude, arr.longitude))
    {
        minFuel += 0.1 * minFuel; // Add 10% extra fuel for oceanic flights
    }
    return minFuel;
}
PlaneInspectionResult* FlightInspection::inspectPlane(const Flight& flight, const PlaneStandard* standard) {
    Plane* plane = flight.getPlane();
    string type = flight.getFlightType();

    if (type == "Cargo") {
    const CargoPlane* cargoPlane = dynamic_cast<const CargoPlane*>(plane);
    const CargoPlaneStandard* cargoStandard = dynamic_cast<const CargoPlaneStandard*>(standard);
    return inspectCargoPlane(cargoPlane, cargoStandard);
}
else if (type == "Passenger") {
    const PassengerPlane* passengerPlane = dynamic_cast<const PassengerPlane*>(plane);
    const PassengerPlaneStandard* passengerStandard = dynamic_cast<const PassengerPlaneStandard*>(standard);
    return inspectPassengerPlane(passengerPlane, passengerStandard);
}
else {
        cerr << "Unknown flight type: " << type << endl;
        return nullptr;
    }
}

CargoPlaneInspectionResult* FlightInspection::inspectCargoPlane(const CargoPlane* plane, const CargoPlaneStandard* standard) {
    if (!plane || !standard) return nullptr;

    CargoPlaneInspectionResult* result = new CargoPlaneInspectionResult();

    // 1. Engine
    bool engineOk = plane->areEnginesOk();
    result->setEngineStatusResult(engineOk);
    result->setEngineStatusNote(engineOk ? "Engines operational." : "Engine check failed.");

    // 2. Fuel
      double currentFuel = plane->getCurrent_Fuel();
double requiredFuel = standard->getMin_fuel();
double maxFuel = plane->getFuelTank();

bool fuelAboveMin = currentFuel >= requiredFuel;
bool fuelBelowMax = currentFuel <= maxFuel;
bool fuelOk = fuelAboveMin && fuelBelowMax;

result->setFuelLevelResult(fuelOk);

string note;
 if (!fuelAboveMin) {
    note = "Fuel level too low. Current: " + 
           to_string(currentFuel) + 
           ", Required: " + to_string(requiredFuel) + ".";
} else if (!fuelBelowMax) {
    note = "Fuel level exceeds tank capacity. Current: " + 
           to_string(currentFuel) + 
           ", Max Tank: " + to_string(maxFuel) + ".";
} else {
    note = "Fuel level sufficient.";
}
result->setFuelLevelNote(note);
    // 3. Payload
    bool payloadOk = plane->getPayload() <= standard->getMaxPayload();
    result->setPayloadResult(payloadOk);
    result->setPayloadNote(payloadOk
        ? "Payload within limit."
        : "Payload (" + to_string(plane->getPayload()) + ") exceeds limit (" +
          to_string(standard->getMaxPayload()) + ").");

    // 4. Model match 
    if (!standard->getModel_available().empty()) {
        if (plane->getModel() != standard->getModel_available()) {
            result->setEngineStatusNote(result->getEngineStatusNote() + " Model mismatch.");
        }
    }

    result->setInspectionResult();
    return result;
}

PassengerPlaneInspectionResult* FlightInspection::inspectPassengerPlane(const PassengerPlane* plane, const PassengerPlaneStandard* standard) {
    if (!plane || !standard) return nullptr;

    PassengerPlaneInspectionResult* result = new PassengerPlaneInspectionResult();

    // 1. Engine
    bool engineOk = plane->areEnginesOk();
    result->setEngineStatusResult(engineOk);
    result->setEngineStatusNote(engineOk ? "Engines operational." : "Engine check failed.");

    // 2. Fuel
    double currentFuel = plane->getCurrent_Fuel();
double requiredFuel = standard->getMin_fuel();
double maxFuel = plane->getFuelTank();

bool fuelAboveMin = currentFuel >= requiredFuel;
bool fuelBelowMax = currentFuel <= maxFuel;
bool fuelOk = fuelAboveMin && fuelBelowMax;

result->setFuelLevelResult(fuelOk);

string note;
 if (!fuelAboveMin) {
    note = "Fuel level too low. Current: " + 
           to_string(currentFuel) + 
           ", Required: " + to_string(requiredFuel) + ".";
} else if (!fuelBelowMax) {
    note = "Fuel level exceeds tank capacity. Current: " + 
           to_string(currentFuel) + 
           ", Max Tank: " + to_string(maxFuel) + ".";
} else {
    note = "Fuel level sufficient.";
}

result->setFuelLevelNote(note);

    // 3. Seat capacity
    bool seatOk = plane->getNumOfPassenger() <= standard->getMaxSeatCapacity();
    result->setSeatCapacityResult(seatOk);
    result->setSeatCapacityNote(seatOk
        ? "Passenger count within limit."
        : "Passenger count (" + to_string(plane->getNumOfPassenger()) +
          ") exceeds limit (" + to_string(standard->getMaxSeatCapacity()) + ").");

    // 4. Model match 
    if (!standard->getModel_available().empty()) {
        if (plane->getModel() != standard->getModel_available()) {
            result->setEngineStatusNote(result->getEngineStatusNote() + " Model mismatch.");
        }
    }

    result->setInspectionResult();
    return result;
}

