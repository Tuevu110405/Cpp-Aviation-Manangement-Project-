#include "../include/FlightManagement.h"
#include "../include/StringManipulator.h"
#include "../include/Flight.h"
#include <sstream>
#include <fstream>

// Define static member variables
vector<PilotStandard> FlightManagement::pilotStandardArray; // Hoang
vector<Flight *> FlightManagement::eligibleFlightList;
vector<Flight *> FlightManagement::ineligibleFlightList;

// Function FlightManagement::loadPilotStandard (Hoang)
void FlightManagement::loadPilotStandard(const string &fileName)
{
    // Open the file.
    ifstream inputFile(fileName);
    if (inputFile.fail())
    {
        cout << "ERROR: File named " << fileName << " not found.\n";
        exit(EXIT_FAILURE);
    }

    // Variable to hold a line in the file.
    string line;

    // Read the pilot's standards and put it in the vector.
    getline(inputFile, line);       // Skip the header line.

    // Reading the file.
    while(getline(inputFile, line))
    {
        // Skip empty lines.
        if (line.empty()) 
            continue; 

        // Create a PilotStandard object.
        PilotStandard pilotStandard;

        // Convert the line into a stream.
        stringstream ss(line);
        string token;

        // Variable declaration.
        string model;
        string requiredType;
        double minFlightHours;
        double minHoursInCommand;
        int minEnglish;
        int minHealth;

        // Read the model name.
        getline(ss, model, ',');

        // Read the minRequiredFlightHours.
        getline(ss, token, ',');
        minFlightHours = stoi(token);

        // Read the minRequiredHoursInCommand.
        getline(ss, token, ',');
        minHoursInCommand = stoi(token);

        // Read the requiredLicenseType.
        getline(ss, requiredType, ',');

        // Read the minRequiredEnglishLevel.
        getline(ss, token, ',');
        minEnglish = stoi(token);

        // Read the minRequiredHealthStatus.
        getline(ss, token, ',');
        minHealth = stoi(token);

        // Store the data of standards into the array.
        try
        {
            pilotStandard.setModelName(model);
            pilotStandard.setMinRequiredFlightHours(minFlightHours);
            pilotStandard.setMinRequiredHoursInCommand(minHoursInCommand);
            pilotStandard.setRequiredLicenseType(requiredType);
            pilotStandard.setMinRequiredEnglishLevel(minEnglish);
            pilotStandard.setRequiredHealthStatus(minHealth);
            pilotStandardArray.push_back(pilotStandard);
        }
        catch (PilotStandard::InvalidModel)
        {
            cout << "LoadFileError: Pilot standards file contain invalid model.\n";
            exit(EXIT_FAILURE);
        }
        catch (PilotStandard::InvalidHours)
        {
            cout << "LoadFileError: Pilot standards file contains invalid value for hours.\n";
            exit(EXIT_FAILURE);
        } 
        catch (PilotStandard::InvalidEnglish)
        {
            cout << "LoadFileError: Pilot standards file contains invalid value for english level.\n";
            exit(EXIT_FAILURE);
        } 
        catch (PilotStandard::InvalidHealth)
        {
            cout << "LoadFileError: Pilot standards file contains invalid value for heath status.\n";
            exit(EXIT_FAILURE);
        } 
        catch (PilotStandard::InvalidType)
        {
            cout << "LoadFileError: Pilot standards file contains invalid value for license type.\n";
            exit(EXIT_FAILURE);
        } 
    }

    inputFile.close();
}


// Function FlightManagement::findPilotStandard (Hoang)
PilotStandard FlightManagement::findPilotStandard(const string &model)
{
    // Remove spaces and capitalize the argument.
    string processedModel = StringManipulator::removeSpaces(model);
    processedModel = StringManipulator::capitalize(processedModel);

    PilotStandard pilotStandard;

    for (int count = 0; count < pilotStandardArray.size(); count++)
    {
        if (pilotStandardArray[count].getModelName() == processedModel)
        {
            pilotStandard = pilotStandardArray[count];
            break;
        }
    }
    return pilotStandard;
}


// Function FlightManagement::displayPilotStandards (Hoang)
void FlightManagement::displayPilotStandards(const string &model)
{
    // Search for the pilot standard corresponding to the model.
    PilotStandard standard = findPilotStandard(model);
    // Display the pilot standard.
    cout << standard << endl;
}

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
        outputFile << "\n[Inspection Result]\n";
        outputFile << "Pilot result: ";
        outputFile << (flight->getPilotInspectionResult().getInspectionResult() == false ? "Ineligible\n" : "Eligible\n");
        outputFile << "Weather result: ";
        outputFile << (flight->getWeatherInspectionResult().getInspectionResult() == false ? "Ineligible\n" : "Eligible\n");
        outputFile << "======\n\n";
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
        outputFile << "\n[Pilot Inspection Result]\n";
        outputFile << "Pilot result: ";
        outputFile << (flight->getPilotInspectionResult().getInspectionResult() == false ? "Ineligible\n" : "Eligible\n");
        outputFile << "Weather result: ";
        outputFile << (flight->getWeatherInspectionResult().getInspectionResult() == false ? "Ineligible\n" : "Eligible\n");
        outputFile << "======\n\n";
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
/* Function for actions of valid and invalid flight (Tue)
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
    */