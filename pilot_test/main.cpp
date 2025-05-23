#include "../include/FlightInspection.h"
#include "../include/DataManagement.h"
#include "../include/PilotStandard.h"
#include "../include/PilotCertificate.h"
#include "../include/PilotCompetence.h"
#include "../include/PilotInspectionResult.h"
#include "../include/Pilot.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Load pilot standards from the file.
    DataManagement::loadPilotStandard("pilot_standards.txt");

    // Demonstrate inspecting pilot for Boeing 787 model.
    PilotStandard pilotStandard = DataManagement::findPilotStandard("Boeing 787");

    // Create a Pilot object and get data.
    Pilot pilotInfo;
    cin >> pilotInfo;

    // Inspecting the pilot and get inspection result.
    PilotInspectionResult pilotResult;
    pilotResult = FlightInspection::inspectPilot(pilotInfo, pilotStandard);

    // Display the inspection result.
    cout << "\n[Pilot inspection result]" << endl;
    cout << " - Overall inspection result: ";
    cout << (pilotResult.getInspectionResult() ? "Eligible" : "Ineligible ") << endl;

    cout << " - Flight hours: " << (pilotResult.getFlightHoursResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getFlightHoursNote() << endl;

    cout << " - Hours in command: " << (pilotResult.getHoursInCommandResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getHoursInCommandNote() << endl;

    cout << " - English level: " << (pilotResult.getEnglishLevelResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getEnglishLevelNote() << endl;

    cout << " - Health status: " << (pilotResult.getHealthStatusResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getHealthStatusNote() << endl;

    cout << " - License type: " << (pilotResult.getLicenseTypeResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getLicenseTypeNote() << endl;

    cout << " - License expiry: " << (pilotResult.getLicenseExpiryResult() ? "Eligible" : "Ineligible ");
    cout << pilotResult.getLicenseExpiryNote() << endl;
    return 0;
}