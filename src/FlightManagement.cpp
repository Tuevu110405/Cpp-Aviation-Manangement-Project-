#include "../include/FlightManagement.h"
#include "../include/StringManipulator.h"
#include "../include/Flight.h"
#include <sstream>

//Function for actions of valid and invalid flight (Tue)
void FlightManagement::addValidFlight(Flight& flight)
{
    validFlight.push_back(flight);
}

void FlightManagement::addInvalidFlight(Flight& flight)
{
    invalidFlight.push_back(flight);
}

vector<Flight> FlightManagement::getValidFlight()
{
    return validFlight;
}

vector<Flight> FlightManagement::getInvalidFlight()
{
    return invalidFlight;
}

void FlightManagement::storeFlight(Flight &flight)
{
    // Check if the flight is valid or invalid
    if (flight.getWeatherInspectionResult().getInspectionResult() == true &&
        flight.getPilotInspectionResult().getInspectionResult() == true )
        // &&flight.getPlaneInspectionResult().getInspectionResult() == true)
    {
        addValidFlight(flight);
    }
    else
    {
        addInvalidFlight(flight);
    }
}

Flight& FlightManagement::getInvalidFlight(string flightID)
{
    for (int i = 0; i < invalidFlight.size(); i++)
    {
        if (invalidFlight[i].getFlightID() == flightID)
        {
            //get flight that we want to find and remove it from invalidFlight
            Flight temp = invalidFlight[i];
            invalidFlight.erase(invalidFlight.begin() + i);
            return temp;
        }
    }
    throw runtime_error("Flight not found");
}
