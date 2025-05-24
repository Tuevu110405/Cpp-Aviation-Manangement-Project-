#include "../include/FLight.h"
#include "../include/Pilot.h"
#include "../include/PilotStandard.h"
#include "../include/PilotInspectionResult.h"
#include "../include/Weather.h"
#include "../include/WeatherStandardVN.h"
#include "../include/WeatherInspectionResult.h"
#include "../include/Plane.h"
#include "../include/PlaneInspectionresult.h"
#include "../include/PlaneStandard.h"
#include "../include/PassengerPlane.h"
#include "../include/PassengerPlaneStandard.h"
#include "../include/CargoPlane.h"
#include "../include/CargoPlaneStandard.h"
#include "../include/FlightInspection.h"
#include "../include/Location.h"
#include "../include/CargoPlaneInspectionResult.h"
#include "../include/PassengerPlaneInspectionResult.h"
#include <iostream>

using namespace std;

int main() {
    // Create and load locations
    Location loc;
    loc.loadDestinationFromFile("destinations.csv"); // Make sure this file exists

    // Setup test flight data
    string flightType = "Cargo"; // or "Passenger"
    string depCode = "HND";      // Haneda, Japan
    string arrCode = "LAX";      // Los Angeles, USA

    // Create a sample plane (CargoPlane example)
   Plane* plane = new CargoPlane();
   CargoPlane* cargo = dynamic_cast<CargoPlane*>(plane);
if (cargo) {
    cargo->setEngineStatus(1);
    cargo->setBaseInfo("Boeing 747", 20000, 0.5, 900); // model, fuel tank, consumption rate, speed
    cargo->setCurrent_Fuel(8000);      // current level
    cargo->setPayload(25000);  // some payload// OK
} else {
    cout << "Dynamic cast failed: not a CargoPlane.\n";
}
 

    // Create standard
    CargoPlaneStandard cargoStd;
    cargoStd.setMin_Fuel(7000); // min required based on calculation
    cargoStd.setMaxPayload(30000);

    // Setup flight
  
Pilot pilot;
cin >> pilot; // Assuming you have a way to input pilot data
 // You may need to initialize this properly
Flight flight("VN123", "Cargo", depCode, arrCode, pilot, Weather(), cargo);

    flight.setLocation(loc);
    flight.setLocation(depCode, arrCode);

    // Run inspection
    FlightInspection inspector;
    PlaneInspectionResult* result = inspector.inspectPlane(flight, &cargoStd);
    flight.setPlaneInspectionResult(*result);

    // Show results
    cout << "Flight ID: " << flight.getFlightID() << std::endl;
    cout << "Flight Type: " << flight.getFlightType() << std::endl;
    flight.displayDetailsPlaneResult();

    delete cargo;
    delete result;

    return 0;
}
