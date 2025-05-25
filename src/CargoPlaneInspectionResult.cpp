#include "../include/CargoPlaneInspectionResult.h"

CargoPlaneInspectionResult::CargoPlaneInspectionResult() 
    : PlaneInspectionResult(), payloadResult(false), payloadNote("") {}

CargoPlaneInspectionResult::CargoPlaneInspectionResult(const string& type)
    : PlaneInspectionResult(type), payloadResult(false), payloadNote("") {}

void CargoPlaneInspectionResult::setPayloadResult(bool result) {
    payloadResult = result;
}

void CargoPlaneInspectionResult::setPayloadNote(const string& note) {
    payloadNote = note;
}

bool CargoPlaneInspectionResult::getPayloadResult() const {
    return payloadResult;
}

string CargoPlaneInspectionResult::getPayloadNote() const {
    return payloadNote;
}

void CargoPlaneInspectionResult::setInspectionResult() {
    
    inspectionResult = (engineStatusResult && fuelLevelResult && payloadResult);
}
