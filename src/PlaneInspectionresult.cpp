#include "../include/PlaneInspectionresult.h"

PlaneInspectionResult::PlaneInspectionResult() 
    : engineStatusResult(false), fuelLevelResult(false), 
      engineStatusNote(""), fuelLevelNote("") {}

PlaneInspectionResult::PlaneInspectionResult(const string& type) 
    : InspectionResult(type), engineStatusResult(false), fuelLevelResult(false),
      engineStatusNote(""), fuelLevelNote("") {}

void PlaneInspectionResult::setEngineStatusResult(bool result) {
    engineStatusResult = result;
}

void PlaneInspectionResult::setFuelLevelResult(bool result) {
    fuelLevelResult = result;
}

void PlaneInspectionResult::setEngineStatusNote(const string& note) {
    engineStatusNote = note;
}

void PlaneInspectionResult::setFuelLevelNote(const string& note) {
    fuelLevelNote = note;
}

bool PlaneInspectionResult::getEngineStatusResult() const {
    return engineStatusResult;
}

bool PlaneInspectionResult::getFuelLevelResult() const {
    return fuelLevelResult;
}

string PlaneInspectionResult::getEngineStatusNote() const {
    return engineStatusNote;
}

string PlaneInspectionResult::getFuelLevelNote() const {
    return fuelLevelNote;
}
