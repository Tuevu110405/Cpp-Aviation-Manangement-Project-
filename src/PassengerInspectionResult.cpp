#include "../include/PassengerPlaneInspectionResult.h"

PassengerPlaneInspectionResult::PassengerPlaneInspectionResult() 
    : PlaneInspectionResult(), seatCapacityResult(false), seatCapacityNote("") {}

PassengerPlaneInspectionResult::PassengerPlaneInspectionResult(const string& type)
    : PlaneInspectionResult(type), seatCapacityResult(false), seatCapacityNote("") {}

void PassengerPlaneInspectionResult::setSeatCapacityResult(bool result) {
    seatCapacityResult = result;
}

void PassengerPlaneInspectionResult::setSeatCapacityNote(const string& note) {
    seatCapacityNote = note;
}

bool PassengerPlaneInspectionResult::getSeatCapacityResult() const {
    return seatCapacityResult;
}

string PassengerPlaneInspectionResult::getSeatCapacityNote() const {
    return seatCapacityNote;
}

void PassengerPlaneInspectionResult::setInspectionResult() {
    inspectionResult = (engineStatusResult && fuelLevelResult && seatCapacityResult);
}
