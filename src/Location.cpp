#include "../include/Location.h"

double Location::degreeToRadian(double deg) {
    return (deg * M_PI / 180.0);
}

double Location::radianToDegree(double rad) {
    return (rad * 180.0 / M_PI);
}

double Location::calculateDistanceInKM(double lat1, double lon1, double lat2, double lon2) const {
    double theta = lon1 - lon2;
    double distance = sin(degreeToRadian(lat1)) * sin(degreeToRadian(lat2)) +
        cos(degreeToRadian(lat1)) * cos(degreeToRadian(lat2)) * cos(degreeToRadian(theta));
    distance = acos(distance);
    distance = radianToDegree(distance);
    distance = distance * 60 * 1.1515 * 1.609344; // convert miles to km
    return distance;
}

double Location::distanceInNM(double distanceInKM) const {
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

bool Location::isOceanicFlight(double lat1, double lon1, double lat2, double lon2) const{
    // Asia to America
    bool isAsiaDeparture = (lat1 >= 20 && lat1 <= 50 && lon1 >= 70 && lon1 <= 140);
    bool isAmericaArrival = (lat2 >= 24 && lat2 <= 50 && lon2 >= -125 && lon2 <= -66);

    // Europe to America
    bool isEuropeDeparture = (lat1 >= 35 && lat1 <= 70 && lon1 >= -25 && lon1 <= 40);
    bool isAmericaArrival2 = (lat2 >= 24 && lat2 <= 50 && lon2 >= -125 && lon2 <= -66);

    // Africa to South America
    bool isAfricaDeparture = (lat1 >= -35 && lat1 <= 40 && lon1 >= -20 && lon1 <= 50);
    bool isSouthAmericaArrival = (lat2 >= -55 && lat2 <= 15 && lon2 >= -80 && lon2 <= -35);

    // South America to Europe
    bool isSouthAmericaDeparture = (lat1 >= -55 && lat1 <= 15 && lon1 >= -80 && lon1 <= -35);
    bool isEuropeArrival = (lat2 >= 35 && lat2 <= 70 && lon2 >= -25 && lon2 <= 40);

    // Australia to Asia
    bool isAustraliaDeparture = (lat1 >= -45 && lat1 <= -10 && lon1 >= 110 && lon1 <= 155);
    bool isAsiaArrival = (lat2 >= 20 && lat2 <= 50 && lon2 >= 70 && lon2 <= 140);

    // Australia to North America
    bool isAustraliaDeparture2 = (lat1 >= -45 && lat1 <= -10 && lon1 >= 110 && lon1 <= 155);
    bool isNorthAmericaArrival = (lat2 >= 24 && lat2 <= 50 && lon2 >= -125 && lon2 <= -66);

    if ((isAsiaDeparture && isAmericaArrival) ||
        (isEuropeDeparture && isAmericaArrival2) ||
        (isAfricaDeparture && isSouthAmericaArrival) ||
        (isSouthAmericaDeparture && isEuropeArrival) ||
        (isAustraliaDeparture && isAsiaArrival) ||
        (isAustraliaDeparture2 && isNorthAmericaArrival)) {
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
