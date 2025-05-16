#include "Plane.h"
// constructor
Plane::Plane()
{
	model = "";
	current_fuel = 0;
	engine_ok = 0;
}

Plane::Plane(int current_fuel_, const string& model, bool engine_ok)
{
	this->current_fuel = current_fuel_;
	this->model = model;
	this->engine_ok = engine_ok;
}

// setter

void Plane::setCurrent_Fuel(int current_fuel__) 
{
	(current_fuel__ >= 0) ? current_fuel = current_fuel__: current_fuel = 0; // auto set to zero if input is negative
}

void Plane::setModel(const string& model_) 
{
	model = model_;
}

void Plane::setEngineStatus(int status) 
{
	if (status == 0) {
		engine_ok = false;
	}
	else if (status == 1) {
		engine_ok = true;
	}
	else {
		cout << "Invalid input for engine status. Type 0 for NOT OK or 1 for OK.\n";
	}
}

void Plane::setBaseInfo(float fuel_consumption_rate_, float speed_, const string& model_)
{
	fuel_consumption_rate = fuel_consumption_rate_;
	speed = speed_;
	model = model_;
}

void Plane::setBaseInfo_from_FIle(const string& filename)
{
		ifstream file(filename);
		if (!file.is_open()) {
			cerr << "Error: Could not open file " << filename << endl;
			return;
		}

		float fuelRate, speedVal;
		file >> fuelRate >> speedVal;

		if (file.fail()) {
			cerr << "Error: Failed to read base info from file." << endl;
			return;
		}

		setBaseInfo(fuelRate, speedVal);  // Use your existing setter

		file.close();

}

// getter
int Plane::getCurrent_Fuel() const
{

	return this->current_fuel;
}

string Plane::getModel() const
{
	return model;
}

bool Plane::areEnginesOk() const
{
	return engine_ok;
}

float Plane::getFuel_consumption_rate() const{
	return fuel_consumption_rate;
}
float Plane::getSpeed() const{
	return speed;

}
// method

bool Plane::isModelNameTrue(string& modelName)
{
	// convert to model name to uppercase
	transform(modelName.begin(), modelName.end(), modelName.begin(), ::toupper);

	// Due to the program just using two brand boeing and airbus -> have to check if the plane is belongs to those two or not
	if (modelName.substr(0, 6) == "BOEING" || modelName.substr(0, 6) == "AIRBUS") {
		return true;
	}
	return false;
}







