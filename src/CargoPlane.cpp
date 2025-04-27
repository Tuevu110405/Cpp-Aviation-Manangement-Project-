#include "CargoPlane.h"



ostream& CargoPlane::operator<<(ostream& os, const CargoPlane& plane)
{
	os << "Plane model: " << plane.getModel();
	os << "\nPlane fuel level: " << plane.getfuel();
	os << "\nPlane engines are ok? :" << (plane.areEnginesOk() ? " OK! " : " NO!");
	return os;

}

istream& CargoPlane::operator>>(istream& is, const CargoPlane& plane)
{
	float fuel;
	string model_name;
	int status_;
	// input model
	cout << "Please enter the model : "; is >> model_name;
	while (!isModelNameTrue(model_name)) {
		cout << "The program consisting two brand [BOEING] AND [AIRBUS]";
		cout << "Please enter the model : ";
		is >> model_name;
	}
	plane.setModel(model_name);

	// input fuel level
	cout << "\nPlease enter the fuel level (in percentage 0 - 100 )  : "; is >> fuel;
	plane.setModel(fuel);

	//input engines condition
	do {
		cout << "\nPlease enter the status of engine (1 for ok and 0 for not ok)  : "; is >> status_;
		plane.setEngineStatus(status_);
	} while (status_ == 1 || status_ == 0);




}



