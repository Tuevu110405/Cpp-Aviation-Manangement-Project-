#pragma once
#include "PlaneStandard.h"

class PassengerPlaneStandard : public PlaneStandard {
protected:
    int max_seat_capacity;
public:
    void setMaxSeatCapacity(int);
    int getMaxSeatCapacity() const;
    bool loadFromFile(const string& filename) override;
};
