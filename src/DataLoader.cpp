#include "../include/DataLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
using namespace std;

void DataLoader::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    string line;
    while(getline(file, line)){
        // Skip empty line
        if(line.empty()) continue; 

        stringstream ss(line);
        string key;
        //key is the word of row 
        getline(ss, key, ','); 

        string value;
        vector<string> values;
        while(getline(ss, value, ',')){
            //value is the meaning of the word
            values.push_back(value); 
        }
        //value is the meaning of the word
        data[key] = values; 


    }

    file.close();
}

DataLoader::DataLoader(const string& filename) {
    loadFromFile(filename);
}

string DataLoader::getValue(string key, int index) {
    if (data.find(key) == data.end()) {
        throw runtime_error("Key not found: " + key);
    }
    if (index < 0 || index >= data[key].size()) {
        throw out_of_range("Index out of range for key: " + key);
    }
    return data[key][index];
}

map<string, vector<string>> DataLoader::getData() {
    return data;
}

int DataLoader::getValueSize(string key) {
    if (data.find(key) == data.end()) {
        throw runtime_error("Key not found: " + key);
    }
    int size = data[key].size();
    return size;
}