#include "../include/Location.h"

double Location::degreeToRadian(double deg) {
    return (deg * M_PI / 180.0);
}

double Location::radianToDegree(double rad) {
    return (rad * 180.0 / M_PI);
}

double Location::calculateDistanceInKM(double lat1, double lon1, double lat2, double lon2) {
    double theta = lon1 - lon2;
    double distance = sin(degreeToRadian(lat1)) * sin(degreeToRadian(lat2)) +
        cos(degreeToRadian(lat1)) * cos(degreeToRadian(lat2)) * cos(degreeToRadian(theta));
    distance = acos(distance);
    distance = radianToDegree(distance);
    distance = distance * 60 * 1.1515 * 1.609344; // convert miles to km
    return distance;
}

double Location::distanceInNM(double distanceInKM) {
    return distanceInKM / 1.852; // 1 NM = 1.852 km
}

void Location::loadDestinationFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string city, code, latStr, lonStr;

        if (getline(ss, city, ',') &&
            getline(ss, code, ',') &&
            getline(ss, latStr, ',') &&
            getline(ss, lonStr, ',')) {
            Destination dest;
            dest.city = city;
            dest.airport_code = code;
            dest.latitude = stod(latStr);
            dest.longitude = stod(lonStr);
            destinations.push_back(dest);
        }
    }

    file.close();
}

bool Location::isOceanicFlight(double lat1, double lon1, double lat2, double lon2) {
    bool isAsiaDeparture = (lat1 >= 20 && lat1 <= 50 && lon1 >= 70 && lon1 <= 140);
    bool isAmericaArrival = (lat2 >= 24 && lat2 <= 50 && lon2 >= -125 && lon2 <= -66);

    bool isEuropeDeparture = (lat1 >= 35 && lat1 <= 70 && lon1 >= -25 && lon1 <= 40);
    bool isAfricaArrival = (lat2 >= -35 && lat2 <= 40 && lon2 >= -20 && lon2 <= 50);

    if ((isAsiaDeparture && isAmericaArrival) ||
        (isEuropeDeparture && isAmericaArrival)) {
        return true;
    }

    return false;
}

const vector<Destination>& Location::getDestinations() const {
    return destinations;
}

bool Location::getDestinationByCode(const string& code, Destination& dest) const {
    for (const Destination& d : destinations) {
        if (d.airport_code == code) {
            dest = d;
            return true;
        }
    }
    return false;
}
