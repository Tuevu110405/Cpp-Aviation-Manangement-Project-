#ifndef CARGOPLANEINSPECTIONRESULT_H
#define CARGOPLANEINSPECTIONRESULT_H

#include "PlaneInspectionResult.h"

class CargoPlaneInspectionResult : public PlaneInspectionResult {
private:
    bool payloadResult;
    string payloadNote;

    void setInspectionResult() override;

public:
    CargoPlaneInspectionResult();
    CargoPlaneInspectionResult(const string& type);

    void setPayloadResult(bool result);
    void setPayloadNote(const string& note);

    bool getPayloadResult() const;
    string getPayloadNote() const;
};

#endif
