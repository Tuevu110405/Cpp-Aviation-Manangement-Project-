#include "../include/FlightInspectionDepartment.h"
#include "../include/FlightManagementDepartment.h"
#include "../include/StringManipulator.h"
#include "../include/PilotInspectionResult.h"
#include "../include/InspectionResult.h"
#include "../include/PilotStandard.h"
#include "../include/PilotCertificate.h"
#include "../include/PilotCompetence.h"
#include "../include/Pilot.h"
#include <iostream>
using namespace std;

int main()
{
    // Load the pilot standards to the program.
    FlightManagementDepartment::loadPilotStandard("pilot_standards.txt");
    cout << "Load the pilot standards sucessfully.\n";

    // Display the all pilot standards.
    cout << "\nHere are the pilot standards in the file.\n";
    FlightManagementDepartment::displayPilotStandards();

    return 0;
}


