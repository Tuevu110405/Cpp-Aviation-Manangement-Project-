#include "../include/Flight.h"
#include "../include/Weather.h"
#include "../include/WeatherStandard.h"
using namespace std;

// Getters (Tue).
const WeatherInspectionResult& Flight::getWeatherInspectionResult() {
    return this->weatherInspectionResult;
}

const Weather& Flight::getWeather()  {
    return this->weather;
}
// Setters (Tue).
void Flight::setWeatherInspectionResult(const WeatherInspectionResult& weatherInspectionResult) {
    this->weatherInspectionResult = weatherInspectionResult;
    updateFlightStatus();
}
void Flight::setWeather(const Weather& weather){
    this->weather = weather;
}

// Default constructor.
Flight::Flight() : weather(0, 0, 0, 0, 0, 0), weatherInspectionResult(false, false, false, false, false, false)
{
    flightID = "";
    flightType = "";
    flightStatus = false;
}

// Constructor.
Flight::Flight(const string &id, const string &type,const string& dep, const string& arr, const Pilot &pilotInfo, const Weather &weatherInfo, const Plane *planeInfo)
{
    try
    {
        setFlightID(id);
        setFlightType(type);
        setPilot(pilot);
        setWeather(weatherInfo);
        setPlane(plane);
        setDepartureCode(dep);
        setArrivalCode(arr);
    }
    catch (InvalidID e)
    {
        throw e;
    }
}

// Copy constructor for FlightManagement stage (Tue).
Flight::Flight(const Flight &flight)
{
    flightID = flight.flightID;
    flightType = flight.flightType;
    departureCode = flight.departureCode;
    arrivalCode = flight.arrivalCode;
    pilot = flight.pilot;
    pilotResult = flight.pilotResult;
    weather = flight.weather;
    plane = flight.plane;
    if (flight.plane != nullptr) {
    plane = flight.plane->clone(); // Use the clone method to create a deep copy of the plane object
} else {
    plane = nullptr;
}
    weatherInspectionResult = flight.weatherInspectionResult;
    planeInspectionResult = flight.planeInspectionResult;
}


// Function Flight::setFlightID (Hoang).
void Flight::setFlightID(const string &id)
{
    // Remove spaces and capitalize the id.
    string processedID = StringManipulator::removeSpaces(id);
    processedID = StringManipulator::capitalize(processedID);

    // If the length of the id is invalid.
    if (processedID.length() < 5 || processedID.length() > 6)
    {
        throw InvalidID(id);
    }

    // If the format of the id is invalid.
    if (processedID[0] != 'V' || processedID[1] != 'N')
    {
        throw InvalidID(id);
    }

    for (int index = 2; index < processedID.length(); index++)
    {
        if (!isdigit(processedID[index]))
        {
            throw InvalidID(id);
        }
    }
    // Otherwise.
    flightID = processedID;
}


// Function Flight::updateFlightStatus.
void Flight::updateFlightStatus()
{
    flightStatus = pilotResult.getInspectionResult() && 
                   weatherInspectionResult.getInspectionResult()
                   && planeInspectionResult->getInspectionResult();
}

// Function Flight::setFlightType (Hoang).
void Flight::setFlightType(const string &type)
{
    flightType = type;
}


// Function Flight::setPilot (Hoang)
void Flight::setPilot(const Pilot &newPilot)
{
    pilot = newPilot;
}

// Function Flight::setPilotInspectionResult (Hoang)
void Flight::setPilotResult(const PilotInspectionResult &newResult)
{
    pilotResult = newResult;
    updateFlightStatus();
}

// Function Flight::displayDetailsPilotResult (Hoang).
void Flight::displayDetailsPilotResult() const
{
    cout << " - Overall inspection result: ";
    cout << (pilotResult.getInspectionResult() ? "Eligible" : "Ineligible ") << endl;

    cout << " - Flight hours: " << (pilotResult.getFlightHoursResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getFlightHoursNote() << endl;

    cout << " - Hours in command: " << (pilotResult.getHoursInCommandResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getHoursInCommandNote() << endl;

    cout << " - English level: " << (pilotResult.getEnglishLevelResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getEnglishLevelNote() << endl;

    cout << " - Health status: " << (pilotResult.getHealthStatusResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getHealthStatusNote() << endl;

    cout << " - License type: " << (pilotResult.getLicenseTypeResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getLicenseTypeNote() << endl;

    cout << " - License expiry: " << (pilotResult.getLicenseExpiryResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getLicenseExpiryNote() << endl;
}


void Flight::displayDetailsWeatherResult() const
{
    cout << " - Overall Inspection Result: " << (weatherInspectionResult.getInspectionResult() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Visibility: " << (weatherInspectionResult.getIsVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Crosswind: " << (weatherInspectionResult.getIsCrosswind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Temperature: " << (weatherInspectionResult.getIsTemperature() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Thunderstorm: " << (weatherInspectionResult.getIsThunderstorm() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Tailwind: " << (weatherInspectionResult.getIsTailwind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Horizontal Visibility: " << (weatherInspectionResult.getIsHorizontalVisibility() ? "Acceptable" : "Not Acceptable") << endl;
}

 void Flight::displayDetailsPlaneResult() const {
    cout << "===== Plane Inspection Summary =====" << endl;
    cout << " - Overall Inspection Result: "
         << (planeInspectionResult->getInspectionResult() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Engine Status: "
         << (planeInspectionResult->getEngineStatusResult() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Fuel Level: "
         << (planeInspectionResult->getFuelLevelResult() ? "Acceptable" : "Not Acceptable") << endl;
    cout << " - Engine Status Note: " << planeInspectionResult->getEngineStatusNote() << endl;
    cout << " - Fuel Level Note: " << planeInspectionResult->getFuelLevelNote() << endl;

    // Specific fields for CargoPlaneInspectionResult
    if (auto cargoResult = dynamic_cast<const CargoPlaneInspectionResult*>(planeInspectionResult)) {
        cout << " - Payload Capacity: "
             << (cargoResult->getPayloadResult() ? "Acceptable" : "Not Acceptable") << endl;
        cout << " - Payload Capacity Note: " << cargoResult->getPayloadNote() << endl;
    }

    // Specific fields for PassengerPlaneInspectionResult
    else if (auto passengerResult = dynamic_cast<const PassengerPlaneInspectionResult*>(planeInspectionResult)) {
        cout << " - Seat Capacity: "
             << (passengerResult->getSeatCapacityResult() ? "Acceptable" : "Not Acceptable") << endl;
        cout << " - Seat Capacity Note: " << passengerResult->getSeatCapacityNote() << endl;

        cout << " - Passenger Count: "
             << (passengerResult->getSeatCapacityResult() ? "Acceptable" : "Not Acceptable") << endl;
        cout << " - Passenger Count Note: " << passengerResult->getSeatCapacityResult() << endl;
    }
}



void Flight::setPlaneInspectionResult(const PlaneInspectionResult &result){
    planeInspectionResult = result.clone();
    updateFlightStatus();
}