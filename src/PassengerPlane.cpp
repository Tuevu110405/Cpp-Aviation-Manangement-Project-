#include "../include/PassengerPlane.h"
#include <limits>
#include <stdexcept>

PassengerPlane::PassengerPlane()
{
	//seatCapacity = 0;
	Passenger_num = 0;
}

double PassengerPlane::maxPayLoad() const
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
	os << "\nPlane payload: " << maxPayLoad() << " kg";
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
        if (fuel < 0 || fuel > fuel_tank)
            throw out_of_range("Fuel  must be between 0 and less than the fuel capacity of model " + model + " is " + to_string(fuel_tank));
        setCurrent_Fuel(fuel);

        cout << "\nPlease enter the engine status (1 for OK, 0 for NOT OK): ";
        is >> status_;
        if (status_ != 1 && status_ != 0)
            throw invalid_argument("Engine status must be set by using 1 or 0.");
        setEngineStatus(status_);

        cout << "\nPlease enter the number of passengers: ";
        is >> passenger_capacity;
        if (!IsEnoughPassenger(passenger_capacity))
            throw out_of_range("Number of passengers exceeds seat capacity.");
        setNumOfPassenger(passenger_capacity);

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        return input(is);  // Use Recursion to ler user retry until true

        return is;
    }
}

void PassengerPlane::setSeatCapacity(double seatCapacity)
{
	this->seatCapacity = seatCapacity;
}

void PassengerPlane::setNumOfPassenger(double Passenger_num)
{
	this->Passenger_num = Passenger_num;
}

double PassengerPlane::getSeatCapacity()
{
	return seatCapacity;
}

bool PassengerPlane::IsEnoughPassenger(double num_passenger) 
{
	
	return (Passenger_num <= seatCapacity) ? true : false;
}



