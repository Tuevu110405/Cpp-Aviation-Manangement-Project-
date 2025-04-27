#pragma once
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
class Plane
{
private:
	float fuel;
	string model;
	int capacity;
	bool engine_ok;
public:
	// constructor
	Plane();
	Plane(int fuel, string& model, int capacity, bool engine_ok);

	// destructor
	virtual ~Plane() = default;

	// setter
	 void setFuel(int fuel__) ;
	 void setModel(const string& model_) ;
	 void setCapacity(int capacity__) ;
	 void setEngineStatus(int status);

	//getter 
	float getCurrent_fuel();
	string getModel();
	bool areEnginesOk(int );

	// each type of airplane must report their own detail
	virtual int maxPayLoad() const = 0;
	virtual int passengerCapacity() const;

	// method
	bool isModelNameTrue(string& modelName);

	//operator overloading

	ostream& operator<<(ostream& os, const Plane& plane);
	istream& operator>>(istream& is, const Plane& plane);
	

};

