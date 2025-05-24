#include "../include/PassengerPlaneStandard.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

bool PassengerPlaneStandard::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;

    // Skip header
    getline(file, line);

    // Read first data line (you can extend this for multiple models)
    if (getline(file, line)) {
        stringstream ss(line);
        string model, seatCapacity;

        if (getline(ss, model, ',') && getline(ss, seatCapacity, ',')) {
            try {
                double maxSeatCapacity = stod(seatCapacity);
                setModel_available(model);
                setMaxSeatCapacity(maxSeatCapacity);
            } catch (const invalid_argument& e) {
                cerr << "Error: Payload value is not a number in file " << filename << endl;
                file.close();
                return false;
            }
        } else {
            cerr << "Error: Incorrect CSV format in file " << filename << endl;
            file.close();
            return false;
        }
    } else {
        cerr << "Error: File is empty or read failure in " << filename << endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}


void PassengerPlaneStandard::setMaxSeatCapacity(double max_seat){
    max_seat_capacity = max_seat;
}
double PassengerPlaneStandard::getMaxSeatCapacity() const{
    return max_seat_capacity;
}

