#include "../include/Plane.h"
#include "../include/PlaneInspectionresult.h"
#include "../include/PlaneStandard.h"
#include "../include/PassengerPlane.h"
#include "../include/PassengerPlaneStandard.h"
#include "../include/CargoPlane.h"
#include "../include/CargoPlaneStandard.h"
#include <iostream>
using namespace std;

int main()
{
    // Create a Plane object.
    Plane *plane = new CargoPlane(); // Create a CargoPlane
    cout << "Enter Cargo Plane details \n";
    cin >> *plane; 
    plane->setBaseInfo_from_FIle("../data/Aircraft baseinfo.csv");

    // Display the Plane information.
    cout << "\nPlane information:" << endl;
    cout << *plane;
    cout << "\nPlane base information:" << endl;
    cout << "Fuel tank: " << plane->getFuelTank() << endl;
    cout << "Speed: " << plane->getSpeed() << endl;
    cout << "Fuel burn rate: " << plane->getFuel_consumption_rate() << endl;

    return 0;
}