#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/DataManagement.h"
#include "../include/PilotInspectionResult.h"
#include "../include/PilotStandard.h"
#include "../include/Pilot.h"
#include "../include/PilotCompetence.h"
#include "../include/PilotCertificate.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/WeatherStandardVN.h"
#include "../include/Weather.h"
#include "../include/Flight.h"
#include "../include/DataLoader.h"
#include "../include/Plane.h"
#include "../include/CargoPlane.h"
#include "../include/PassengerPlane.h"
#include "../include/Date.h"
#include "../include/PlaneInspectionResult.h"
#include "../include/StringManipulator.h"
#include <string>
#include <iostream>
using namespace std;

void loadDataAndHandle() {
    string filepath;
    cout << "Enter the path to the flight data file: ";
    cin >> filepath;
    cout << "--- Loading data from file: " << filepath << " ---" << endl;
    // Load flight data (try-catch for not being able to open file)
    bool loadOK = false;
    while (!loadOK) {
        try {
            DataLoader loader(filepath);
            cout << "Data loaded successfully." << endl;
            // Print the number of flights
            string key = "flightID";
            cout << "This data contains " << loader.getValueSize(key) << " flights." << endl;
            loadOK = true; // Set to true if loading is successful
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please check the file path and format." << endl;
            cout << "Enter the path to the flight data file again: ";
            cin >> filepath; // Prompt for a new file path
        }
    }
}

int main() {
    loadDataAndHandle();
    // Additional code to handle flights can be added here
    // For example, you can call functions to process the loaded data
    // and perform inspections or other operations as needed.
    
    cout << "--- Program finished successfully ---" << endl;
    return 0;
}

