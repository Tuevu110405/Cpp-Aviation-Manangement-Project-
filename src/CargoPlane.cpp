#include "../include/CargoPlane.h"


// Overload operator<<
ostream& operator<<(ostream& os, const CargoPlane& plane)
{
    os << "Plane model: " << plane.getModel();
    os << "\nPlane fuel level: " << plane.getFuel();
    os << "\nPlane engines status: " << (plane.areEnginesOk() ? " OK! " : " NO!");
    os << "\nPlane payload capacity: " << plane.maxPayLoad() << " kg";
    return os;
}

// Overload operator>>
istream& operator>>(istream& is, CargoPlane& plane)
{
    int fuel;
    string model_name;
    int status_;
    int payload_;

    // Input model name
    cout << "Please enter the model: ";
    is >> model_name;
    while (!plane.isModelNameTrue(model_name)) {
        cout << "The program supports two brands: [BOEING] AND [AIRBUS]\n";
        cout << "Please enter the model: ";
        is >> model_name;
    }
    plane.setModel(model_name);
    cin.ignore();

    // Input fuel level
    cout << "\nPlease enter the fuel level (in percentage 0 - 100): ";
    is >> fuel;
    plane.setFuel(fuel);

    // Input engines condition
    do {
        cout << "Please enter the status of the engine (1 for OK, 0 for NOT OK): ";
        is >> status_;
        if (status_ == 1 || status_ == 0)
            plane.setEngineStatus(status_);
        else
            cout << "Invalid input. Please enter 1 or 0.\n";
    } while (status_ != 1 && status_ != 0);

    // Input payload capacity
    cout << "Please enter the payload capacity (in kg): ";
    is >> payload_;
    plane.setPayload(payload_);

    return is;
}

CargoPlane::CargoPlane()
{
    payloadCapacity = 0;
}

int CargoPlane::maxPayLoad() const
{
    return payloadCapacity ;
}

int CargoPlane::passengerCapacity() const
{
    return 0;
}

void CargoPlane::setPayload(int payloadCapacity)
{
    this->payloadCapacity = payloadCapacity;
}
