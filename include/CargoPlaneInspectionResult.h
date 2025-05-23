#ifndef CARGOPLANEINSPECTIONRESULT_H
#define CARGOPLANEINSPECTIONRESULT_H

#include "PlaneInspectionResult.h"

class CargoPlaneInspectionResult : public PlaneInspectionResult {
private:
    bool payloadResult;
    string payloadNote;

    

public:
    CargoPlaneInspectionResult();
    CargoPlaneInspectionResult(const string& type);
    void setInspectionResult() override;
    void setPayloadResult(bool result);
    void setPayloadNote(const string& note);
    // Pure virtual clone function
    PlaneInspectionResult* clone() const override {
        return new CargoPlaneInspectionResult(*this);
    }
    bool getPayloadResult() const;
    string getPayloadNote() const;
};

#endif
