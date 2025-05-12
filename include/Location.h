#pragma once
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
struct Destination {
	string city;
	string airport_code;
	float latitude;
	float longitude;
};

class Location
{
private:
	// exchange the degree
	double degreeToRadian(double deg) {
		return (deg * M_PI / 180.0);
	}

	double radianToDegree(double rad) {
		return (rad * 180.0 / M_PI);
	}
	vector<Destination> destinations;
public:
	// The calculate function will take the latitude and longitude to calculate the distance between 2 destination
    vector<string> calculateDistance(float lat1, float lat2, float lon1, float lon2);
	void loadDestinationFromFile(const string& filename);
	bool isOceanicFlight(float lat1, float lon1, float lat2, float lon2);
    

};






