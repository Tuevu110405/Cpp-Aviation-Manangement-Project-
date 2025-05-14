#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/PilotInspectionResult.h"
#include "../include/Pilot.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/WeatherStandardVN.h"
#include "../include/Weather.h"
#include "../include/Flight.h"
#include <iostream>
using namespace std;

int main()
{
    // Load pilot standards from the file.
    FlightManagement::loadPilotStandard("pilot_standards.txt");
    cout << "Load the pilot standards sucessfully.\n";

    // Variable declaration.
    bool isFirstTime = true;
    bool isAgain = false;
}