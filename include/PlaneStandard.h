#ifndef PLANE_STANDARD_H
#define PLANE_STANDARD_H
#include <string>
using namespace std;

class PlaneStandard {
protected:
    double min_fuel;
    string model_available;
public:
    void setMin_Fuel(double minFuel);
    void setModel_available(const string& model_avail);
    virtual bool loadFromFile(const string& filename);
    double getMin_fuel() const;
    string getModel_available() const;
    virtual ~PlaneStandard() = default;
};
#endif