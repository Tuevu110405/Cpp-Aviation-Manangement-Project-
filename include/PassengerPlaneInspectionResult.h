#ifndef PASSENGERPLANEINSPECTIONRESULT_H
#define PASSENGERPLANEINSPECTIONRESULT_H

#include "../include/PlaneInspectionResult.h"

class PassengerPlaneInspectionResult : public PlaneInspectionResult {
private:
    bool seatCapacityResult;
    string seatCapacityNote;

    

public:
    PassengerPlaneInspectionResult();
    PassengerPlaneInspectionResult(const string& type);
    // Pure virtual clone function
    PlaneInspectionResult* clone() const override {
        return new PassengerPlaneInspectionResult(*this);
    }
    void setSeatCapacityResult(bool result);
    void setSeatCapacityNote(const string& note);
    void setInspectionResult() override;
    bool getSeatCapacityResult() const;
    string getSeatCapacityNote() const;
};

#endif
