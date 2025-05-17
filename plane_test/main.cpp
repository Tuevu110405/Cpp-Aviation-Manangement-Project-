#include "../include/Plane.h"
#include "../include/CargoPlane.h"
#include "../include/PassengerPlane.h"
#include "../include/PlaneInspectionresult.h"
#include <iostream>
using namespace std;

int main()
{
    Plane *p = new CargoPlane;

    cin >> *p;

    cout << *p;
    
}
