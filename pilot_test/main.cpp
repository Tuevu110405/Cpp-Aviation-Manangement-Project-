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
    }
    else
    {
        cout << "Eligible.";
    }
    cout << pilotResult.getFlightHoursNote() << endl;


    cout << " - Hours in command: ";
    if (pilotResult.getHoursInCommandResult() == false)
    {
        cout << "Ineligible. ";
    }
    else
    {
        cout << "Eligible.";
    }
    cout << pilotResult.getHoursInCommandNote() << endl;

    cout << " - English level: ";
    if (pilotResult.getEnglishLevelResult() == false)
    {
        cout << "Ineligible. ";
    }
    else
    {
        cout << "Eligible.";
    }
    cout << pilotResult.getEnglishLevelNote() << endl;

    cout << " - Health status: ";
    if (pilotResult.getHealthStatusResult() == false)
    {
        cout << "Ineligible. ";
    }
    else
    {
        cout << "Eligible.";
    }
    cout << pilotResult.getHealthStatusNote() << endl;

    cout << " - License Type: ";
    if (pilotResult.getLicenseTypeResult() == false)
    {
        cout << "Ineligible. ";
    }
    else
    {
        cout << "Eligible.";
    }
    cout << pilotResult.getLicenseTypeNote() << endl;

    cout << " - License expiration: ";
    if (pilotResult.getLicenseExpiryResult() == false)
    {
        cout << "Ineligible. ";
    }
    else
    {
        cout << "Eligible.";
    }
    cout << pilotResult.getLicenseExpiryNote() << endl;

    return 0;
}