#include "../include/CargoPlane.h"
#include <limits>
#include <stdexcept>





CargoPlane::CargoPlane()
{
    payloadCapacity = 0;
}

CargoPlane::CargoPlane(const CargoPlane &other):Plane(other), payloadCapacity(other.payloadCapacity)
{
}


// Corrected output() method
ostream& CargoPlane::output(ostream& os) const
{
    os << "Plane model: " << getModel();
    os << "\nPlane fuel level: " << getCurrent_Fuel();
    os << "\nPlane engines status: " << (areEnginesOk() ? " OK! " : " NO!");
    os << "\nPlane payload capacity: " << getPayload() << " kg";
    return os;
}

// Corrected input() method
istream& CargoPlane::input(istream& is)
{
    double fuel;
    string model_name;
    double status_;
    double payload_capacity;
        // Input for Model Name
    while (true) {
        cout << "Please enter the model: ";
        is >> model_name;
        if (is.fail()) { // Check for non-string input if expected
            cerr << "Error: Invalid input type. Please enter a text model name.\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (!isModelNameTrue(model_name)) {
            cerr << "Error: Unsupported model. Allowed: [BOEING], [AIRBUS]\n";
        } else {
            setModel(model_name);
            break; // Exit loop on valid input
        }
    }

    // Input for Fuel
    while (true) {
        cout << "\nPlease enter the fuel level in kg : "; // Updated prompt
        is >> fuel;
        if (is.fail()) {
            cerr << "Error: Invalid input type. Please enter a number for fuel.\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (fuel < 0 || fuel > 100000) {
            cerr << "Error: Fuel level must be between 0 and 100,000.\n"; // Updated error message
        } else {
            setCurrent_Fuel(fuel);
            break; // Exit loop on valid input
        }
    }

    // Input for Engine Status
    while (true) {
        cout << "\nPlease enter the engine status (1 for OK, 0 for NOT OK): ";
        is >> status_;
        if (is.fail()) {
            cerr << "Error: Invalid input type. Please enter 1 or 0.\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (status_ != 1 && status_ != 0) {
            cerr << "Error: Engine status must be 1 or 0.\n"; // Updated error message
        } else {
            setEngineStatus(status_);
            break; // Exit loop on valid input
        }
    }

    // Input for Number of Payload
    while (true) {
        cout << "\nPlease enter the number of payload: "; // Updated prompt
        is >> payload_capacity; // Changed variable name
        if (is.fail()) {
            cerr << "Error: Invalid input type. Please enter a number for payload.\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (payload_capacity < 0) { // Changed variable name
            cerr << "Error: The payload can not be less than zero.\n"; // Updated error message
        } else {
            setPayload(payload_capacity); // Changed function call
            break; // Exit loop on valid input
        }
    }


    return is;
}

void CargoPlane::setPayload(double payloadCapacity)
{
    this->payloadCapacity = payloadCapacity;
}
double CargoPlane::getPayload() const
{
    return payloadCapacity;
}

Plane* CargoPlane::clone() const{

    return new CargoPlane(*this);
}