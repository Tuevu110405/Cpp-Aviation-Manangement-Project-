#pragma once
#include "PlaneStandard.h"

class PassengerPlaneStandard : public PlaneStandard {
protected:
    double max_seat_capacity;
public:
    void setMaxSeatCapacity(double);
    double getMaxSeatCapacity() const;
    bool loadFromFile(const string& filename) override;
};
