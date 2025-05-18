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
}
void Flight::setWeather(const Weather& weather){
    this->weather = weather;
}

// Default constructor.
Flight::Flight() : weather(0, 0, 0, 0, 0, 0), weatherInspectionResult(false, false, false, false, false, false)
{
    flightID = "";
    flightType = "";
}

// Constructor.
Flight::Flight(const string &id, const string &type, const Pilot &pilotInfo, const Weather &weatherInfo, const Plane *planeInfo)
{
    try
    {
        setFlightID(id);
        setFlightType(type);
        setPilot(pilot);
        setWeather(weatherInfo);
        setPlane(plane);
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
    pilot = flight.pilot;
    pilotResult = flight.pilotResult;
    weather = flight.weather;
    plane = flight.plane;
    /*Tuệệ dùng deep copy như trong sách mà không đc
    if(flight.plane != nullptr)
    {
        plane = new Plane(*flight.plane);
        plane->setBaseInfo(flight.plane->getFuel_consumption_rate(), flight.plane->getSpeed(), flight.plane->getCurrent_Fuel(), flight.plane->getModel());
    }
    else
    {
        plane = nullptr;
    }
        */
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
    if (pilotResult.getInspectionResult() == true &&
        weatherInspectionResult.getInspectionResult() == true)
    {
        flightStatus = true;
    }
    else
    {
        flightStatus = false;
    }
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
}

// Function Flight::displayDetailsPilotResult (Hoang).
void Flight::displayDetailsPilotResult() const
{
    cout << " - Overall inspection result: ";
    cout << (pilotResult.getInspectionResult() == false ? "Not acceptable" : "Acceptable") << endl;

    cout << " - Flight hours: " << (pilotResult.getFlightHoursResult() == false ? "Not acceptable, " : "Acceptable");
    cout << pilotResult.getFlightHoursNote() << endl;

    cout << " - Hours in command: " << (pilotResult.getHoursInCommandResult() == false ? "Not acceptable, " : "Acceptable");
    cout << pilotResult.getHoursInCommandNote() << endl;

    cout << " - English level: " << (pilotResult.getEnglishLevelResult() == false ? "Not acceptable, " : "Acceptable");
    cout << pilotResult.getEnglishLevelNote() << endl;

    cout << " - Health status: " << (pilotResult.getHealthStatusResult() == false ? "Not acceptable, " : "Acceptable");
    cout << pilotResult.getHealthStatusNote() << endl;

    cout << " - License type: " << (pilotResult.getLicenseTypeResult() == false ? "Not acceptable, " : "Acceptable");
    cout << pilotResult.getLicenseTypeNote() << endl;

    cout << " - License expiry: " << (pilotResult.getLicenseExpiryResult() == false ? "Not acceptable, " : "Acceptable");
    cout << pilotResult.getLicenseExpiryNote() << endl;
}


void Flight::displayDetailsWeatherResult() const
{
    cout << "\n[Weather Inspection Result]" << endl;
    cout << "Visibility: " << (weatherInspectionResult.getIsVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Crosswind: " << (weatherInspectionResult.getIsCrosswind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Temperature: " << (weatherInspectionResult.getIsTemperature() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Thunderstorm: " << (weatherInspectionResult.getIsThunderstorm() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Tailwind: " << (weatherInspectionResult.getIsTailwind() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Horizontal Visibility: " << (weatherInspectionResult.getIsHorizontalVisibility() ? "Acceptable" : "Not Acceptable") << endl;
    cout << "Overall Inspection Result: " << (weatherInspectionResult.getInspectionResult() ? "Acceptable" : "Not Acceptable") << endl;
}