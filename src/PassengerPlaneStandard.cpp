#include "../include/PassengerPlaneStandard.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool PassengerPlaneStandard::loadFromFile(const string& filename) {

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        string model;
        int maxSeat;

        if (!(ss >> model >> maxSeat)) {
            cerr << "Error: Incorrect format in file " << filename << endl;
            file.close();
            return false;
        }

        setModel_available(model);
        setMaxSeatCapacity(maxSeat);
    } else {
        cerr << "Error: Empty file or read failure in " << filename << endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}

void PassengerPlaneStandard::setMaxSeatCapacity(int max_seat){
    max_seat_capacity = max_seat;
}
int PassengerPlaneStandard::getMaxSeatCapacity() const{
    return max_seat_capacity;
}

