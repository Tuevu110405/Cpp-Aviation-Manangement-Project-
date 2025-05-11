#include "Location.h"

vector<string> Location::calculateDistance(float lat1, float lat2, float lon1, float lon2)
{
	{
		float theta = lon1 - lon2;
		float distance = sin(degreeToRadian(lat1)) * sin(degreeToRadian(lat2)) +
			cos(degreeToRadian(lat1)) * cos(degreeToRadian(lat2)) * cos(degreeToRadian(theta));
		distance = acos(distance);
		distance = radianToDegree(distance);
		distance = distance * 60 * 1.1515;
	}
}

void Location::loadDestinationFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string city, latStr, lonStr;

        if (getline(ss, city, ',') && getline(ss, latStr, ',') && getline(ss, lonStr, ',')) {
            Destination dest;
            dest.city = city;
            dest.latitude = stod(latStr);
            dest.longitude = stod(lonStr);
            destinations.push_back(dest);
        }
    }

    file.close();
}
