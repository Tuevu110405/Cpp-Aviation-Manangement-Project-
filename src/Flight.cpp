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

