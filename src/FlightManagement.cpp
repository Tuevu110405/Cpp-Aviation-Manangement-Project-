#include "../include/FlightManagement.h"
#include <sstream>

// Define static member variables
vector<PilotStandard> FlightManagement::pilotStandardArray; // Hoang


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
    int index = 0;  // Index of the array.

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
        minFlightHours = stod(token);

        // Read the minRequiredHoursInCommand.
        getline(ss, token, ',');
        minHoursInCommand = stod(token);

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
            // Increment the index.
            index++;
        }
        catch (PilotStandard::InvalidModel)
        {
            cout << "Pilot standards file contain invalid model.\n";
            exit(EXIT_FAILURE);
        }
        catch (PilotStandard::InvalidHours)
        {
            cout << "Pilot standards file contains invalid value for hours.\n";
            exit(EXIT_FAILURE);
        } 
        catch (PilotStandard::InvalidEnglish)
        {
            cout << "Pilot standards file contains invalid value for english level.\n";
            exit(EXIT_FAILURE);
        } 
        catch (PilotStandard::InvalidHealth)
        {
            cout << "Pilot standards file contains invalid value for heath status.\n";
            exit(EXIT_FAILURE);
        } 
        catch (PilotStandard::InvalidType)
        {
            cout << "Pilot standards file contains invalid value for license type.\n";
            exit(EXIT_FAILURE);
        } 
    }

    inputFile.close();
}


// Function FlightManagement::findPilotStandard (Hoang)
PilotStandard FlightManagement::findPilotStandard(const string &model)
{
    PilotStandard pilotStandard;
    for (int count = 0; count < pilotStandardArray.size(); count++)
    {
        if (pilotStandardArray[count].getModelName() == model)
        {
            pilotStandard = pilotStandardArray[count];
            break;
        }
    }
    return pilotStandard;
}


// Function FlightManagement::displayPilotStandards (Hoang)
void FlightManagement::displayPilotStandards()
{
    for (int count = 0; count < pilotStandardArray.size(); count++)
    {
        cout << "Model: ";
        cout << pilotStandardArray[count].getModelName() << endl;
        cout << "Flight hours: ";
        cout << pilotStandardArray[count].getMinRequiredFlightHours() << endl;
        cout << "Hours in command: ";
        cout << pilotStandardArray[count].getMinRequiredHoursInCommand() << endl;
        cout << "English level: ";
        cout << pilotStandardArray[count].getMinRequiredEnglishLevel() << endl;
        cout << "Health status: ";
        cout << pilotStandardArray[count].getRequiredHealthStatus() << endl;
        cout << "License type: ";
        cout << pilotStandardArray[count].getRequiredLicenseType() << endl;
        cout << endl;
    }
}