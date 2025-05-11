#include "../include/FlightInspection.h"
#include "../include/FlightManagement.h"
#include "../include/PilotInspectionResult.h"
#include "../include/PilotStandard.h"
#include "../include/Pilot.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Load pilot standards.
    FlightManagement::loadPilotStandard("pilot_standards.txt");
    string model = "Boeing 787";
    PilotStandard standard = FlightManagement::findPilotStandard(model);

    Pilot pilot;
    cin >> pilot;

    PilotInspectionResult pilotResult = FlightInspection::inspectPilot(pilot, standard);

    cout << "\n[Pilot Inspection Result]\n";
    cout << "Overall result: ";
    cout << (pilotResult.getInspectionResult() == false? "Ineligible" : "Eligible") << endl;
    cout << " - Flight hours: ";
    if (pilotResult.getFlightHoursResult() == false)
    {
        cout << "Ineligible. ";
        cout << pilotResult.getFlightHoursNote() << endl;
    }
    else
    {
        cout << "Eligible.\n";
    }

    cout << " - Hours in command: ";
    if (pilotResult.getHoursInCommandResult() == false)
    {
        cout << "Ineligible. ";
        cout << pilotResult.getHoursInCommandNote() << endl;
    }
    else
    {
        cout << "Eligible.\n";
    }

    cout << " - English level: ";
    if (pilotResult.getEnglishLevelResult() == false)
    {
        cout << "Ineligible. ";
        cout << pilotResult.getEnglishLevelNote() << endl;
    }
    else
    {
        cout << "Eligible.\n";
    }

    cout << " - Health status: ";
    if (pilotResult.getHealthStatusResult() == false)
    {
        cout << "Ineligible. ";
        cout << pilotResult.getHealthStatusNote() << endl;
    }
    else
    {
        cout << "Eligible.\n";
    }

    cout << " - License Type: ";
    if (pilotResult.getLicenseTypeResult() == false)
    {
        cout << "Ineligible. ";
        cout << pilotResult.getLicenseTypeNote() << endl;
    }
    else
    {
        cout << "Eligible.\n";
    }

    cout << " - License expiration: ";
    if (pilotResult.getLicenseExpiryResult() == false)
    {
        cout << "Ineligible. ";
        cout << pilotResult.getLicenseExpiryNote() << endl;
    }
    else
    {
        cout << "Eligible.\n";
    }

    return 0;
}