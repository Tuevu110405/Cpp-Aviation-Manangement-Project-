#include "../include/PlaneInspectionResult.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool PlaneInspectionResult::validate(const Plane& plane) {
    bool valid = true;

    if (!validateModel(plane)) valid = false;
    if (!validateFuel(plane)) valid = false;
    if (!validateEngineStatus(plane)) valid = false;
    if (!validateFuelConsumptionRate(plane)) valid = false;
    if (!validateSpeed(plane)) valid = false;

    return valid;
}

bool PlaneInspectionResult::validateModel(const Plane& plane) {
    string model = plane.getModel();
    if (model.empty()) {
        cout << "Error: Model name is empty." << endl;
        return false;
    }
    if (!isModelNameTrue(model)) {
        return false;
    }
    return true;
}

bool PlaneInspectionResult::validateFuel(const Plane& plane) {
    if (plane.getCurrent_Fuel() < 0) {
        cout << "Error: Fuel cannot be negative." << endl;
        return false;
    }
    return true;
}

bool PlaneInspectionResult::validateEngineStatus(const Plane& plane) {
    if (!plane.areEnginesOk()) {
        cout << "Error: Engine status is NOT OK." << endl;
        return false;
    }
    return true;
}

bool PlaneInspectionResult::validateFuelConsumptionRate(const Plane& plane) {
    if (plane.getFuel_consumption_rate() <= 0) {
        cout << "Error: Fuel consumption rate must be greater than 0." << endl;
        return false;
    }
    return true;
}

bool PlaneInspectionResult::validateSpeed(const Plane& plane) {
    if (plane.getSpeed() <= 0) {
        cout << "Error: Speed must be greater than 0." << endl;
        return false;
    }
    return true;
}

bool PlaneInspectionResult::isModelNameTrue(string& modelName)
{
    // convert to model name to uppercase
    transform(modelName.begin(), modelName.end(), modelName.begin(), ::toupper);

    // Due to the program just using two brand boeing and airbus -> have to check if the plane is belongs to those two or not
    if (modelName.substr(0, 6) == "BOEING" || modelName.substr(0, 6) == "AIRBUS") {
        return true;
    }
    return false;
}