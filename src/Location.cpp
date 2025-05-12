#include "Location.h"

vector<string> Location::calculateDistance(float lat1, float lat2, float lon1, float lon2)
{
	{
		float theta = lon1 - lon2;
		float distance = sin(degreeToRadian(lat1)) * sin(degreeToRadian(lat2)) +
			cos(degreeToRadian(lat1)) * cos(degreeToRadian(lat2)) * cos(degreeToRadian(theta));
		distance = acos(distance);
		distance = radianToDegree(distance);
		float distance_NM = distance * 60;
        distance = distance_NM * 60 * 1.1515;
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

int min_fuel = distance * Fuelburn_rate * get_advanced_factor_fuel();
if(getfuel < min_fuel)

bool isOceanicFlight(float lat1, float lon1, float lat2, float lon2) {
    // Rough estimates of continents' latitudes and longitudes for oceanic check
    // For example, checking if the flight crosses the Pacific or Atlantic Ocean

    // Define approximate latitude and longitude bounds for continents
    // Asia (approx. latitudes from 20N to 50N, longitudes from 70E to 140E)
    bool isAsiaDeparture = (lat1 >= 20 && lat1 <= 50 && lon1 >= 70 && lon1 <= 140);
    bool isAmericaArrival = (lat2 >= 24 && lat2 <= 50 && lon2 >= -125 && lon2 <= -66);  // North America bounds (e.g., California to New York)

    bool isEuropeDeparture = (lat1 >= 35 && lat1 <= 70 && lon1 >= -25 && lon1 <= 40);  // Europe bounds
    bool isAfricaArrival = (lat2 >= -35 && lat2 <= 40 && lon2 >= -20 && lon2 <= 50);  // Africa bounds

    // Check if flight crosses ocean (Pacific or Atlantic)
    if (isAsiaDeparture && isAmericaArrival) {
        return true;  // Likely Pacific Ocean crossing
    }
    else if (isEuropeDeparture && isAmericaArrival) {
        return true;  // Likely Atlantic Ocean crossing
    }

    return false;  // Not an oceanic flight
}



