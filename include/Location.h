#pragma once
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#ifndef M_PI
#define M_PI (acos(-1.0))
#endif
using namespace std;
struct Destination {
	string city;
	string airport_code;
	double latitude;
	double longitude;
};

class Location {
private:
    double degreeToRadian(double deg);
    double radianToDegree(double rad);
    vector<Destination> destinations; // List of all loaded airports

public:
    void loadDestinationFromFile(const string& filename);  // Load airport data
    double calculateDistanceInKM(double lat1, double lon1, double lat2, double lon2);
    double distanceInNM(double distanceInKM);
    bool isOceanicFlight(double lat1, double lon1, double lat2, double lon2);
    const vector<Destination>& getDestinations() const;
    bool getDestinationByCode(const string& code, Destination& dest) const;
};
