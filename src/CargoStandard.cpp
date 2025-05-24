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


    // Read first data line (you can extend this for multiple models)
    if (getline(file, line)) {
        stringstream ss(line);
        string model, payloadStr;

        if (getline(ss, model, ',') && getline(ss, payloadStr, ',')) {
            try {
                double maxPayload = stod(payloadStr);
                setModel_available(model);
                setMaxPayload(maxPayload);
            } catch (const std::invalid_argument& e) {
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
