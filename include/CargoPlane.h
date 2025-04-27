#pragma once
#include "Plane.h"
class CargoPlane :
    public Plane
{
private:
    int payloadCapacity;
public:
    //constructor
    CargoPlane();
    CargoPlane(int payloadCapacity_);

    // setter
    void setFuel(int fuel_) const override;
    virtual void setModel(const string& model_) const override ;
    virtual void setCapacity(int payloadCapacity__) const override;

    // getter
    int getPayload();
    
    //operator overloading
    ostream& operator<<(ostream& os, const CargoPlane& plane);
    istream& operator>>(istream& is, const CargoPlane& plane);
};

