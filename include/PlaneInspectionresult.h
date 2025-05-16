#pragma once
#include "Plane.h"
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "Location.h"

class PlaneInspectionResult {
public:
    static bool validate(const Plane& plane);



protected:
    static bool validateModel(const Plane& plane);
    static bool validateFuel(const Plane& plane);
    static bool validateEngineStatus(const Plane& plane);
    static bool validateFuelConsumptionRate(const Plane& plane);
    static bool validateSpeed(const Plane& plane);
    static bool isModelNameTrue(string& modelName);
};
