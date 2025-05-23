#include "../include/FlightManagement.h"
#include "../include/StringManipulator.h"
#include "../include/Flight.h"
#include <sstream>
#include <fstream>

// Define static member variables
vector<Flight *> FlightManagement::eligibleFlightList;
vector<Flight *> FlightManagement::ineligibleFlightList;
vector<Flight *> FlightManagement::inspectedFlightList;

// Function FlightMangement::addFlight
void FlightManagement::addFlight(Flight *flight)
{
    // Add the flight to inspectedFlightList.
    inspectedFlightList.push_back(flight);

    // Categorize the flight to its relevant vector.
    if (flight->getFlightStatus() == false)
    {
        ineligibleFlightList.push_back(flight);
    }
    else
    {
        eligibleFlightList.push_back(flight);
    }
}

// Function FlightMangement::writeIneligibleFlights
void FlightManagement::writeIneligibleFlights(const string &fileName)
{
    // Open the file.
    ofstream outputFile(fileName);
    if (outputFile.fail())
    {
        cout << "ERROR: Could not open the file to write data to.\n";
        exit(EXIT_FAILURE);
    }

    // Write data to the file.
    outputFile << "There are " << ineligibleFlightList.size() << " ineligible flights.\n";
    for (int count = 0; count < ineligibleFlightList.size(); count++)
    {
        Flight *flight = ineligibleFlightList[count];
        outputFile << "Flight: " << flight->getFlightID() << endl;
        outputFile << "Flight type: " << flight->getFlightType() << endl;
        outputFile << "Status: Ineligible\n";

        // Write details of Pilot Inspection Result.
        outputFile << "\n[Pilot Inspection Result]\n";

        // Take the pilot inspection result.
        PilotInspectionResult pilotResult = flight->getPilotInspectionResult();

        // Write the overall pilot inspection result.
        outputFile << "Overall result: " << 
        (pilotResult.getInspectionResult() ? "Eligible" : "Ineligible") << endl;

        // Write the details of the pilot inspection result for flight hours.
        outputFile << " - Flight hours: ";
        outputFile << (pilotResult.getFlightHoursResult() ? "Eligible" : "Ineligible ");
        outputFile << pilotResult.getFlightHoursNote() << endl;

        // Write the details of the pilot inspection result for hours in command.
        outputFile << " - Hours in command: ";
        outputFile << (pilotResult.getHoursInCommandResult() ? "Eligible" : "Ineligible ");
        outputFile << pilotResult.getHoursInCommandNote() << endl;

        // Write the details of the pilot inspection result for English level.
        outputFile << " - English level: ";
        outputFile << (pilotResult.getEnglishLevelResult() ? "Eligible" : "Ineligible ");
        outputFile << pilotResult.getEnglishLevelNote() << endl;

        // Write the details of the pilot inspection result for health status.
        outputFile << " - Health status: ";
        outputFile << (pilotResult.getHealthStatusResult() ? "Eligible" : "Ineligible ");
        outputFile << pilotResult.getHealthStatusNote() << endl;
        
        // Write the details of the pilot inspection result for license type.
        outputFile << " - License type: ";
        outputFile << (pilotResult.getLicenseTypeResult() ? "Eligible" : "Ineligible ");
        outputFile << pilotResult.getLicenseExpiryNote() << endl;

        // Write the details of the pilot inspection result for license expiry.
        outputFile << " - License date: ";
        outputFile << (pilotResult.getLicenseExpiryResult() ? "Eligible" : "Ineligible ");
        outputFile << pilotResult.getLicenseExpiryNote() << endl;
        outputFile << endl;

        
        // Write the details of Weather Inspection Result.
        WeatherInspectionResult weatherInspectionResult = flight->getWeatherInspectionResult();
        outputFile << "[Weather inspection result]\n";
        outputFile << " - Overall result: " << (weatherInspectionResult.getInspectionResult() ? "Acceptable" : "Not Acceptable") << endl;
        outputFile << " - Visibility: " << (weatherInspectionResult.getIsVisibility() ? "Acceptable" : "Not Acceptable") << endl;
        outputFile << " - Crosswind: " << (weatherInspectionResult.getIsCrosswind() ? "Acceptable" : "Not Acceptable") << endl;
        outputFile << " - Temperature: " << (weatherInspectionResult.getIsTemperature() ? "Acceptable" : "Not Acceptable") << endl;
        outputFile << " - Thunderstorm: " << (weatherInspectionResult.getIsThunderstorm() ? "Acceptable" : "Not Acceptable") << endl;
        outputFile << " - Tailwind: " << (weatherInspectionResult.getIsTailwind() ? "Acceptable" : "Not Acceptable") << endl;
        outputFile << " - Horizontal Visibility: " << (weatherInspectionResult.getIsHorizontalVisibility() ? "Acceptable" : "Not Acceptable") << endl;

        // Write the details of Plane Inspection Result.

        outputFile << "==========" << endl;
    }

    // Close the file.
    outputFile.close();
}

// Function FlightMangement::writeEligibleFlights
void FlightManagement::writeEligibleFlights(const string &fileName)
{
    // Open the file.
    ofstream outputFile(fileName);
    if (outputFile.fail())
    {
        cout << "ERROR: Could not open the file to write data to.\n";
        exit(EXIT_FAILURE);
    }

    // Write data to the file.
    outputFile << "There are " << eligibleFlightList.size() << " ineligible flights.\n";
    for (int count = 0; count < eligibleFlightList.size(); count++)
    {
        Flight *flight = eligibleFlightList[count];
        outputFile << "Flight: " << flight->getFlightID() << endl;
        outputFile << "Flight type: " << flight->getFlightType() << endl;
        outputFile << "Status: Eligible\n";

        // Write details of Pilot Inspection Result.
        outputFile << "\n[Inspection Results]\n";
        // Take the pilot inspection result.
        PilotInspectionResult pilotResult = flight->getPilotInspectionResult();
        // Write the overall pilot inspection result.
        outputFile << "Pilot result: Eligible.\n";

        // Write details Weather Inspection Result.
        outputFile << "Weather result: Eligible.\n";

        // Write Plane Inspection Result.

        outputFile << "==========" << endl;
    }

    // Close the file.
    outputFile.close();
}

void FlightManagement::writeSummary(const string &fileName)
{
    // Open the file.
    ofstream outputFile(fileName);
    if (outputFile.fail())
    {
        cout << "ERROR: Could not open file to write summary.\n";
        exit(EXIT_FAILURE);
    }

    int totalFlightsInspected = eligibleFlightList.size() + ineligibleFlightList.size();

    // Write the summary.
    outputFile << "Total flight inspected: " << totalFlightsInspected << " flights, in which" << endl;
    outputFile << "  - " << eligibleFlightList.size() << " eligible flights\n";
    outputFile << "  - " << ineligibleFlightList.size() << " ineligible flights\n";

    // Write details of all inspected flights.
    outputFile << "\nFlights have been inspected are listed below.\n";
    outputFile << "==========\n\n";
    for (int count = 0; count < inspectedFlightList.size(); count++)
    {
        Flight *flight = inspectedFlightList[count];
        
        // Write the flight general information.
        outputFile << "Flight #" << (count + 1) <<  endl;
        outputFile << "Flight ID: " << flight->getFlightID() << endl;
        outputFile << "Flight type: " << flight->getFlightType() << endl;
        outputFile << endl;

        // Write the details of pilot.
        Pilot pilot = flight->getPilot();
        PilotCertificate certificate = pilot.getPilotCertificate();
        PilotCompetence competence = pilot.getPilotCompetence();

        outputFile << "[Pilot]\n";
        outputFile << "Pilot name: " << pilot.getName() << endl;
        outputFile << "Flight hours: " << competence.getFlightHours() << endl;
        outputFile << "Hours in command: " << competence.getHoursInCommand() << endl;
        outputFile << "English level: Level " << competence.getEnglishLevel() << endl;
        outputFile << "Health status: Level " << competence.getHealthStatus() << endl;
        outputFile << "License type: " << certificate.getLicenseType() << endl;
        outputFile << "Expiry date: " << certificate.getExpiryDate().getDate() << endl;
        outputFile << endl;

        // Write the details of weather.
        Weather weather = flight->getWeather();

        outputFile << "[Weather]\n";
        outputFile << "Forward visibility: " << weather.getVisibility() << endl;
        outputFile << "Horizontal visibility: " << weather.getHorizontalVisibility() << endl;
        outputFile << "Crosswind: " << weather.getCrosswind() << endl;
        outputFile << "Tailwind: " << weather.getTailwind() << endl;
        outputFile << "Temperature (Celsius degree): " << weather.getTemperature() << endl;
        outputFile << "Thunderstorm: " << weather.getThunderstorm() << endl;
        outputFile << "==========\n\n";
    }
    // Close the file.
    outputFile.close();
}

void FlightManagement::deleteFlights()
{
    for (int count = 0; count < eligibleFlightList.size(); count++)
    {
        delete eligibleFlightList[count];
    }
    for (int count = 0; count < ineligibleFlightList.size(); count++)
    {
        delete ineligibleFlightList[count];
    }
}

// Function FlightManagement::getEligibleFlightList.
vector<Flight *> FlightManagement::getEligibleFlightList()
{
    return eligibleFlightList;
}

// Function FlightManagement::getIneligibleFlightList.
vector<Flight *> FlightManagement::getIneligibleFlightList()
{
    return ineligibleFlightList;
}

// Function FlightManagement::getEligibleFlight.
Flight *FlightManagement::getIneligibleFlight(string flightID)
{
    for (int i = 0; i < ineligibleFlightList.size(); i++)
    {
        if (ineligibleFlightList[i]->getFlightID() == flightID)
        {
            //get flight that we want to find and remove it from invalidFlight
            Flight *temp = ineligibleFlightList[i];
            ineligibleFlightList.erase(ineligibleFlightList.begin() + i);
            return temp;
        }
    }
    throw runtime_error("Flight not found");
}
