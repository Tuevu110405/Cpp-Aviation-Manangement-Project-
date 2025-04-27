#include "PassengerPlane.h"

PassengerPlane::PassengerPlane()
{
	//seatCapacity = 0;
	Passenger_num = 0;
}

int PassengerPlane::maxPayLoad() const
{
	return Passenger_num * 100;
}

int PassengerPlane::passengerCapacity() const
{
	return Passenger_num;
}

void PassengerPlane::setSeatCapacity(int seatCapacity)
{
	this->seatCapacity = seatCapacity;
}

void PassengerPlane::setNumOfPassenger(int Passenger_num)
{
	this->Passenger_num = Passenger_num;
}

int PassengerPlane::getSeatCapacity()
{
	return seatCapacity;
}

bool PassengerPlane::IsEnoughPassenger(int num_passenger) 
{
	
	return (Passenger_num <= seatCapacity) ? true : false;
}

istream& operator>>(istream& in, PassengerPlane& plane)
{
	float fuel;
	string model_name;
	int status_;
	int passenger_capacity;
	// input model
	cout << "Please enter the model : "; in >> model_name;
	while (!plane.isModelNameTrue(model_name)) {
		cout << "The program support two brands: [BOEING] AND [AIRBUS]";
		cout << "Please enter the model : ";
		in >> model_name;
	}
	plane.setModel(model_name);

	// input fuel level
	cout << "\nPlease enter the fuel level (in percentage 0 - 100 )  : "; in >> fuel;
	plane.setFuel(fuel);

	// Input engines condition
	do {
		cout << "\nPlease enter the status of the engine (1 for OK, 0 for not OK): ";
		in >> status_;
		if (status_ == 1 || status_ == 0)
			plane.setEngineStatus(status_);
		else
			cout << "Invalid input. Please enter 1 or 0." << endl;
	} while (status_ != 1 && status_ != 0);

	// Input payload capacity
	cout << "Please enter the number of passenger on this plane : ";
	in >> passenger_capacity;
	while (!plane.IsEnoughPassenger(passenger_capacity)){
		cout << "The number of passenger can not be more than the seat capacity of the plane ( " << plane.getSeatCapacity() << " ) !!!";
		cout << "Please enter the number of passenger on this plane : ";
		in >> passenger_capacity;
	}
	plane.setNumOfPassenger(passenger_capacity);
}

ostream& operator<<(ostream& out, const PassengerPlane& plane)
{
	out << "Plane model: " << plane.getModel();
	out << "\nPlane fuel level: " << plane.getFuel();
	out << "\nPlane engines status :" << (plane.areEnginesOk() ? " OK! " : " NO!");
	out << "\nPlane have " << plane.passengerCapacity() << " passenger! ";
	out << "\nPlane payload: " << plane.maxPayLoad() << " kg";
	return out;
}
