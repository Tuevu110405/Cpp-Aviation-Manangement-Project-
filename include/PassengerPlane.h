#pragma once
#include "Plane.h"
class PassengerPlane :
    public Plane
{
private:
    int seatCapacity;
    int Passenger_num;
public:
    // constructor
    PassengerPlane();

    // override function
    int maxPayLoad() const override;
    int passengerCapacity() const override;

    //setter
    void setSeatCapacity(int seatCapacity);
    void setNumOfPassenger(int Passenger_num);

    //getter
    int getSeatCapacity();

    // validate number of passenger 
    bool IsEnoughPassenger(int num_passenger);
   
};

 // operator overloading
    istream& operator>>(istream& in, PassengerPlane& plane);
    ostream& operator<<(ostream& out, const PassengerPlane& plane);
