#ifndef DATA_MANAGEMENT_H
#define DATA_MANAGEMENT_H
#include "PilotStandard.h"
#include "PlaneStandard.h"
#include "PassengerPlaneStandard.h" 
#include "CargoPlaneStandard.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class DataManagement
{
private:
    // Pilot-related variable (Hoang)
    static vector<PilotStandard> pilotStandardArray;
    static vector<CargoPlaneStandard> cargoStandardArray;
    static vector<PassengerPlaneStandard> passengerStandardArray;

public:
    // Pilot-related functions (Hoang)
    static void loadPilotStandard(const string &fileName);
    static PilotStandard findPilotStandard(const string &model);
    static void displayPilotStandards(const string &model);

    static void loadCargoStandard(const string& fileName);
    static CargoPlaneStandard findCargoStandard(const string& model);


    static void loadPassengerStandard(const string& fileName);
    static PassengerPlaneStandard findPassengerStandard(const string& model);
   

};
#endif
