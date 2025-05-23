#pragma once
#include "Plane.h"
#include <iostream>
#include <string>
using namespace std;

class PassengerPlane :
    public Plane
{
private:
    double Passenger_num;
public:
    // constructor
    PassengerPlane();
    PassengerPlane(const PassengerPlane& other);

    // override function
    double PayLoad() const override;
    double passengerCapacity() const override;
    ostream& output(ostream& os) const override;
    istream& input(istream& is) override;
    Plane* clone() const override;

    //setter
    void setNumOfPassenger(double Passenger_num);

    //getter
    double getNumOfPassenger();
 
};

