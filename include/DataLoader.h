#ifndef DataLoader_H
#define DataLoader_h
#include<vector>
#include<map>
#include<string>

using namespace std;
class DataLoader{
private:
    map<string, vector<string>> data;
    
public:
    map<string, vector<string>> getData();
    void loadFromFile(const string& filename);
    DataLoader(const string& filename);
    DataLoader();
    string getValue(string key, int index);
    int getValueSize(string key);
};

#endif