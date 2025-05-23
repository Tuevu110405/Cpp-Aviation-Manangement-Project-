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
    
    // Pure virtual clone function
    virtual PlaneInspectionResult* clone() const = 0;
    //setters
    void setEngineStatusResult(bool result);
    void setFuelLevelResult(bool result);
    void setEngineStatusNote(const string& note);
    void setFuelLevelNote(const string& note);

    //getters
    bool getEngineStatusResult() const;
    bool getFuelLevelResult() const;
    string getEngineStatusNote() const;
    string getFuelLevelNote() const;
};

#endif
