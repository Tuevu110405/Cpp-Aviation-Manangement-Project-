#include "../include/Plane.h"
// constructor
Plane::Plane()
{
	model = "";
	fuel = 0;
	engine_ok = 0;
}

Plane::Plane(int fuel_, string& model, bool engine_ok)
{
	this->fuel = fuel_;
	this->model = model;
	this->engine_ok = engine_ok;
}

// setter

void Plane::setFuel(int fuel__) 
{
	(fuel__ >= 0) ? fuel = fuel__: fuel = 0; // auto set to zero if input is negative
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

// getter
int Plane::getFuel() const
{
	return this->fuel;
}

string Plane::getModel() const
{
	return model;
}

bool Plane::areEnginesOk() const
{
	return engine_ok;
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







