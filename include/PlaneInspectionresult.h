#ifndef PLANEINSPECTIONRESULT_H
#define PLANEINSPECTIONRESULT_H

#include "InspectionResult.h"
#include <string>
using namespace std;

class PlaneInspectionResult : public InspectionResult {
protected:
    bool engineStatusResult;
    bool fuelLevelResult;
    string engineStatusNote;
    string fuelLevelNote;

    virtual void setInspectionResult() override = 0; // Make this class abstract

public:
    PlaneInspectionResult();
    PlaneInspectionResult(const string& type);
    virtual ~PlaneInspectionResult() = default;

    void setEngineStatusResult(bool result);
    void setFuelLevelResult(bool result);
    void setEngineStatusNote(const string& note);
    void setFuelLevelNote(const string& note);

    bool getEngineStatusResult() const;
    bool getFuelLevelResult() const;
    string getEngineStatusNote() const;
    string getFuelLevelNote() const;
};

#endif
