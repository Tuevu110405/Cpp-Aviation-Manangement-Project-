#include "../include/PassengerPlane.h"
#include <limits>
#include <stdexcept>

PassengerPlane::PassengerPlane()
{
	//seatCapacity = 0;
	Passenger_num = 0;
}
PassengerPlane::PassengerPlane(const PassengerPlane& other): Plane(other), Passenger_num(other.Passenger_num){}
double PassengerPlane::PayLoad() const
{
	return Passenger_num * 100;
}

double PassengerPlane::passengerCapacity() const
{
	return Passenger_num;
}

ostream& PassengerPlane::output(ostream& os) const
{
	os << "Plane model: " << getModel();
	os << "\nPlane fuel level: " << getCurrent_Fuel();
	os << "\nPlane engines status :" << (areEnginesOk() ? " OK! " : " NO!");
	os << "\nPlane have " << passengerCapacity() << " passenger! ";
	return os;
}

istream& PassengerPlane::input(istream& is)
{
    double fuel;
    string model_name;
    double status_;
    double passenger_capacity;

    try {
        cout << "Please enter the model: ";
        is >> model_name;
        if (!isModelNameTrue(model_name))
            throw invalid_argument("Model is not supported. Allowed: [BOEING], [AIRBUS]");
        setModel(model_name);

        cout << "\nPlease enter the fuel in gallons : ";
        is >> fuel;
        if (fuel < 0 || fuel > 100000)
            throw out_of_range("Fuel  must be between 0 and l00000");
            
        setCurrent_Fuel(fuel);

        cout << "\nPlease enter the engine status (1 for OK, 0 for NOT OK): ";
        is >> status_;
        if (status_ != 1 && status_ != 0)
            throw invalid_argument("Engine status must be set by using 1 or 0.");
        setEngineStatus(status_);
        cout << "\nPlease enter the number of passengers: ";
        is >> passenger_capacity;
        if (passenger_capacity < 0)
            throw out_of_range("Number of passengers can not less than 0 .");
        setNumOfPassenger(passenger_capacity);

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        return input(is);  // Use Recursion to ler user retry until true

        return is;
    }
    return is;
}


void PassengerPlane::setNumOfPassenger(double Passenger_num)
{
	this->Passenger_num = Passenger_num;
}

double PassengerPlane::getNumOfPassenger(){
    return Passenger_num;
}

Plane* PassengerPlane::clone() const{
    return new PassengerPlane(*this);

}





