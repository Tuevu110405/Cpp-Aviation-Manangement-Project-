#pragma once
#include "Plane.h"
#include <string>
#include <iomanip>
#include <iostream>
class CargoPlane :
    public Plane
{
private:
    double payloadCapacity; // in kg
public:
    //constructor
    CargoPlane();
    CargoPlane(const CargoPlane& other);

    // override function
    double PayLoad() const override;
    double passengerCapacity() const override;
    ostream& output(ostream& os) const override;
    istream& input(istream& is) override;

    Plane* clone() const override;


    // setter
    void setPayload(double payloadCapacity);
    
};

