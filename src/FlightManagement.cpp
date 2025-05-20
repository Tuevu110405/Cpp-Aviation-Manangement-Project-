#include "../include/FlightManagement.h"
#include "../include/StringManipulator.h"
#include "../include/Flight.h"
#include <sstream>
#include <fstream>

// Define static member variables
vector<Flight *> FlightManagement::eligibleFlightList;
vector<Flight *> FlightManagement::ineligibleFlightList;

// Function FlightMangement::addFlight
void FlightManagement::addFlight(Flight *flight)
{
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
        if (pilotResult.getFlightHoursResult() == false)
        {
            outputFile << "Ineligible, ";
            outputFile << pilotResult.getFlightHoursNote()<< endl;
        }
        else
        {
            outputFile << "Eligible" << endl;
        }
        // Write the details of the pilot inspection result for hours in command.
        outputFile << " - Hours in command: ";
        if (pilotResult.getHoursInCommandResult() == false)
        {
            outputFile << "Ineligible, ";
            outputFile << pilotResult.getHoursInCommandNote() << endl;
        }
        else
        {
            outputFile << "Eligible" << endl;
        }
        // Write the details of the pilot inspection result for English level.
        outputFile << " - English level: ";
        if (pilotResult.getEnglishLevelResult() == false)
        {
            outputFile << "Ineligible, ";
            outputFile << pilotResult.getEnglishLevelNote() << endl;
        }
        else
        {
            outputFile << "Eligible" << endl;
        }
        // Write the details of the pilot inspection result for health status.
        outputFile << " - Health status: ";
        if (pilotResult.getHealthStatusResult() == false)
        {
            outputFile << "Ineligible, ";
            outputFile << pilotResult.getHealthStatusNote() << endl;
        }
        else
        {
            outputFile << "Eligible" << endl;
        }
        // Write the details of the pilot inspection result for license type.
        outputFile << " - License type: ";
        if (pilotResult.getLicenseTypeResult() == false)
        {
            outputFile << "Ineligible, ";
            outputFile << pilotResult.getLicenseExpiryNote() << endl;
        }
        else
        {
            outputFile << "Eligible" << endl;
        }
        // Write the details of the pilot inspection result for license expiry.
        outputFile << " - License date: ";
        if (pilotResult.getLicenseTypeResult() == false)
        {
            outputFile << "Ineligible, ";
            outputFile << pilotResult.getLicenseExpiryNote() << endl;
        }
        else
        {
            outputFile << "Eligible" << endl;
        }
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
        outputFile << "\nWeather result: Eligible.\n";

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
