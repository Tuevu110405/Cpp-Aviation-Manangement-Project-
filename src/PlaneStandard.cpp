#include "../include/PlaneStandard.h"
#include <fstream>
#include <sstream>
#include <iostream>

void PlaneStandard::setMin_Fuel(double minFuel) {
    min_fuel = minFuel;
}

void PlaneStandard::setModel_available(const string& model_avail) {
    model_available = model_avail;
}

double PlaneStandard::getMin_fuel() const {
    return min_fuel;
}

string PlaneStandard::getModel_available() const {
    return model_available;
}

// Base loadFromFile only loads model name; child classes will extend this
bool PlaneStandard::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        string model;
        if (!(ss >> model)) {
            cerr << "Error: Incorrect format in file " << filename << endl;
            file.close();
            return false;
        }

        setModel_available(model);
    } else {
        cerr << "Error: Empty file or read failure in " << filename << endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}
