#include "../include/CargoPlaneStandard.h"
#include <fstream>
#include <sstream>
#include <iostream>

void CargoPlaneStandard::setMaxPayload(double max_payload){
    max_payload_capacity = max_payload;
}
double CargoPlaneStandard::getMaxPayload() const{
    return max_payload_capacity;

}
bool CargoPlaneStandard::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return false;
    }

    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        string model;
        double maxPayload;

        if (!(ss >> model >> maxPayload)) {
            cerr << "Error: Incorrect format in file " << filename << endl;
            file.close();
            return false;
        }

        setModel_available(model);
        setMaxPayload(maxPayload);
    } else {
        cerr << "Error: Empty file or read failure in " << filename << endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}
