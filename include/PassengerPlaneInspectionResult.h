#ifndef PASSENGERPLANEINSPECTIONRESULT_H
#define PASSENGERPLANEINSPECTIONRESULT_H

#include "../include/PlaneInspectionResult.h"

class PassengerPlaneInspectionResult : public PlaneInspectionResult {
private:
    bool seatCapacityResult;
    string seatCapacityNote;

    void setInspectionResult() override;

public:
    PassengerPlaneInspectionResult();
    PassengerPlaneInspectionResult(const string& type);

    void setSeatCapacityResult(bool result);
    void setSeatCapacityNote(const string& note);

    bool getSeatCapacityResult() const;
    string getSeatCapacityNote() const;
};

#endif
