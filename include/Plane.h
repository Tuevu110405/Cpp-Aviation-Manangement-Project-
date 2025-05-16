#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Location.h"
using namespace std;
class Plane
{
private:
	int current_fuel; // in gallons kg
	string model;
	bool engine_ok;
	float fuel_consumption_rate;
	float speed;
	

public:
	// constructor
	Plane();
	Plane(int current_fuel_,const string& model, bool engine_ok);

	// destructor
	virtual ~Plane() = default;

	// setter
	 void setCurrent_Fuel(int current_fuel__) ;
	/* void setModel(const string& model_) ;*/
	 void setEngineStatus(int status);

	 virtual void setBaseInfo(float fuel_consumption_rate_, float speed_, const string& model_ );
	 virtual void setBaseInfo_from_FIle(const string& filename);
	//getter 
	int getCurrent_Fuel() const;
	string getModel() const;
	bool areEnginesOk() const;
	float getFuel_consumption_rate() const;
	float getSpeed() const;
	// each type of airplane must report their max possible weight
	virtual int maxPayLoad() const = 0;
	virtual int passengerCapacity() const = 0;
	

	
	
};

