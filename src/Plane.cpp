#include "../include/Plane.h"
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;
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

void Plane::setBaseInfo(const string& model_,double fuel_tank_,double fuel_consumption_rate_, double speed_  )
{
	fuel_consumption_rate = fuel_consumption_rate_;
	speed = speed_;
	fuel_tank = fuel_tank_;
	model = model_;
}

void Plane::setBaseInfo_from_FIle(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        string model, fuelTankStr, fuelRateStr, speedStr;

        if (getline(ss, model, ',') &&
            getline(ss, fuelTankStr, ',') &&
            getline(ss, fuelRateStr, ',') &&
            getline(ss, speedStr, ',')) {
            try {
                double fuelTank = stod(fuelTankStr);
                double fuelRate = stod(fuelRateStr);
                double speedVal = stod(speedStr);
                setBaseInfo(model, fuelTank, fuelRate, speedVal);
            } catch (const invalid_argument& e) {
                cerr << "Error: One of the numeric values is invalid in file " << filename << endl;
            }
        } else {
            cerr << "Error: Incorrect CSV format in file " << filename << endl;
        }
    } else {
        cerr << "Error: Failed to read line from file " << filename << endl;
    }

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

double Plane::getFuel_consumption_rate() const{
	return fuel_consumption_rate;
}
double Plane::getSpeed() const{
	return speed;

}

double Plane::getFuelTank() const
{
    return fuel_tank;
}
bool Plane::isModelNameTrue(std::string& modelName) {
	// Convert model name to uppercase
	transform(modelName.begin(), modelName.end(), modelName.begin(), ::toupper);

	// Valid Boeing and Airbus models (you can expand this list)
	// Remove invalid models for Tung 
	const unordered_set<string> validModels = {
		// "BOEING737", "BOEING747", "BOEING757", "BOEING767", "BOEING777",//
		 "BOEING787",
		// "AIRBUSA220", "AIRBUSA300", "AIRBUSA310", "AIRBUSA318", "AIRBUSA319",
		 "AIRBUSA320NEO","AIRBUSA350", 
		"AIRBUSA321" //"AIRBUSA330"//
		//  "AIRBUSA340",  "AIRBUSA380"
	};

	// Check if modelName is in the valid models list
	return validModels.find(modelName) != validModels.end();
}

istream& operator>>(istream& is, Plane& plane) {
	return plane.input(is);  // Calls the virtual input() method
}

ostream& operator<<(ostream& os, const Plane& plane) {
	return plane.output(os);  // Calls the virtual output() method
}





