#pragma once
#include "Plane.h"
class PassengerPlane :
    public Plane
{
private:
    int seatCapacity;
public:
    // constructor
    PassengerPlane();



    // operator overloading
    istream& operator>>(istream& in, PassengerPlane& plane);
    ostream& operator<<(ostream& out, const PassengerPlane& plane);

};

