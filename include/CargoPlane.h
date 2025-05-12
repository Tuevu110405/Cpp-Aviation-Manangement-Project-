#pragma once
#include "Plane.h"
class CargoPlane :
    public Plane
{
private:
    int payloadCapacity; // in kg
public:
    //constructor
    CargoPlane();

    // override function
    int maxPayLoad() const override;
    int passenger_Capacity() const override;

    // setter
    void setPayload(int payloadCapacity);
    
    
};

//operator overloading
    ostream& operator<<(ostream& os, const CargoPlane& plane);
    istream& operator>>(istream& is, CargoPlane& plane);