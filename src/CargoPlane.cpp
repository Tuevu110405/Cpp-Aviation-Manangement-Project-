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
        try {
            cout << "Please enter the model: ";
            is >> model_name;
            if (!isModelNameTrue(model_name))
                throw invalid_argument("Unsupported model. Allowed: [BOEING], [AIRBUS]");
            setModel(model_name);

            cout << "\nPlease enter the fuel level in gallons : ";
            is >> fuel;
            if (fuel < 0 || fuel > 100000)
                throw out_of_range("Fuel level must be between 0 and 100,000.");
            setCurrent_Fuel(fuel);

            cout << "\nPlease enter the engine status (1 for OK, 0 for NOT OK): ";
            is >> status_;
            if (status_ != 1 && status_ != 0)
                throw invalid_argument("Engine status must be 1 or 0.");
            setEngineStatus(status_);

            cout << "\nPlease enter the number of payload: ";
            is >> payload_capacity;
            if (payloadCapacity < 0 )
            
                throw out_of_range("The payload can not less than zero.");
            setPayload(payload_capacity);

        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
            return input(is);  // Use Recursion to ler user retry until true
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