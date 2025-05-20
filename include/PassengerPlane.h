#pragma once
#include "Plane.h"
#include <iostream>
#include <string>
using namespace std;

class PassengerPlane :
    public Plane
{
private:
    double seatCapacity;
    double Passenger_num;
public:
    // constructor
    PassengerPlane();
    PassengerPlane(const PassengerPlane& other);

    // override function
    double maxPayLoad() const override;
    double passengerCapacity() const override;
    ostream& output(ostream& os) const override;
    istream& input(istream& is) override;

    //setter
    void setSeatCapacity(double seatCapacity);
    void setNumOfPassenger(double Passenger_num);

    //getter
    double getSeatCapacity();

    // validate number of passenger 
    bool IsEnoughPassenger(double num_passenger);

   
};

