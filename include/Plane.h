#pragma once
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
class Plane
{
private:
	int fuel; // in proportion
	string model;
	bool engine_ok;
	Location departure;
	Location arrival;

public:
	// constructor
	Plane();
	Plane(int fuel_, string& model, bool engine_ok);

	// destructor
	virtual ~Plane() = default;

	// setter
	 void setFuel(int fuel__) ;
	 void setModel(const string& model_) ;
	 void setEngineStatus(int status);

	//getter 
	int getFuel() const;
	string getModel() const;
	bool areEnginesOk() const;

	// each type of airplane must report their max possible weight
	virtual int maxPayLoad() const = 0;
	virtual int passengerCapacity() const = 0;

	// validate member function
	bool isModelNameTrue(string& modelName);
	
	
};

