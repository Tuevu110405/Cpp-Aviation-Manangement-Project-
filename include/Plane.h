#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
class Plane
{
protected:
	double current_fuel; // in gallons kg
	string model;
	bool engine_ok;
	double fuel_consumption_rate;
	double speed;
	double fuel_tank;
	

public:
	// constructor
	Plane();
	Plane(int current_fuel_,const	 string& model, bool engine_ok);
	Plane(const Plane& other) = default; // COPY CONSTRUCTOR

	// destructor
	virtual ~Plane() = default;

	// setter
	 void setCurrent_Fuel(int current_fuel__) ;
	 void setModel(const string& model_) ;
	 void setEngineStatus(int status);

	 virtual void setBaseInfo(double fuel_consumption_rate_, double speed_, double fuel_tank_, const string& model_ );
	 virtual void setBaseInfo_from_FIle(const string& filename);
	//getter 
	int getCurrent_Fuel() const;
	string getModel() const;
	bool areEnginesOk() const;
	double getFuel_consumption_rate() const;
	double getSpeed() const;
	double getFuelTank() const;
	

	//deep copy function
	virtual Plane* clone() const = 0;

	// operator overload
	virtual istream& input(istream& in) = 0;
	virtual ostream& output(ostream& out) const = 0;

	bool isModelNameTrue(string& modelName);
	friend ostream& operator<<(ostream& os, const Plane& plane) ;
	friend istream& operator>>(istream& is, Plane& plane) ;


};
