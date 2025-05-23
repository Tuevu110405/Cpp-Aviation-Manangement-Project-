#include "../include/PassengerPlane.h"
#include <limits>
#include <stdexcept>

PassengerPlane::PassengerPlane()
{
	//seatCapacity = 0;
	Passenger_num = 0;
}
PassengerPlane::PassengerPlane(const PassengerPlane& other): Plane(other), Passenger_num(other.Passenger_num){}


ostream& PassengerPlane::output(ostream& os) const
{
	os << "Plane model: " << getModel();
	os << "\nPlane fuel level: " << getCurrent_Fuel();
	os << "\nPlane engines status :" << (areEnginesOk() ? " OK! " : " NO!");
	os << "\nPlane have " << getNumOfPassenger() << " passenger! ";
	return os;
}

istream& PassengerPlane::input(istream& is)
{
    double fuel;
    string model_name;
    double status_;
    double passenger_capacity;

   while (true) {
        cout << "Please enter the model: ";
        is >> model_name;
        if (is.fail()) { // Check for non-string input if expected
            cerr << "Error: Invalid input type. Please enter a text model name.\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (!isModelNameTrue(model_name)) {
            cerr << "Error: Model is not supported. Allowed: [BOEING], [AIRBUS]\n";
        } else {
            setModel(model_name);
            break; // Exit loop on valid input
        }
    }

    // Input for Fuel
    while (true) {
        cout << "\nPlease enter the fuel in kg : ";
        is >> fuel;
        if (is.fail()) {
            cerr << "Error: Invalid input type. Please enter a number for fuel.\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (fuel < 0 || fuel > 100000) {
            cerr << "Error: Fuel must be between 0 and 100000 kg.\n";
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
            cerr << "Error: Engine status must be set by using 1 or 0.\n";
        } else {
            setEngineStatus(status_);
            break; // Exit loop on valid input
        }
    }

    // Input for Number of Passengers
    while (true) {
        cout << "\nPlease enter the number of passengers: ";
        is >> passenger_capacity;
        if (is.fail()) {
            cerr << "Error: Invalid input type. Please enter a number for passengers.\n";
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (passenger_capacity < 0) {
            cerr << "Error: Number of passengers cannot be less than 0.\n";
        } else {
            setNumOfPassenger(passenger_capacity);
            break; // Exit loop on valid input
        }
    }
    return is;
}


void PassengerPlane::setNumOfPassenger(double Passenger_num)
{
	this->Passenger_num = Passenger_num;
}

double PassengerPlane::getNumOfPassenger() const{
    return Passenger_num;
}

Plane* PassengerPlane::clone() const{
    return new PassengerPlane(*this);

}





