#pragma once
#include "PlaneStandard.h"

class CargoPlaneStandard : public PlaneStandard {
protected:
    double max_payload_capacity;
public:
    void setMaxPayload(double max_payload);
    double getMaxPayload() const;
    bool loadFromFile(const string& filename) override;
};
