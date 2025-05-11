#ifndef INSPECTIONRESULT_H
#define INSPECTIONRESULT_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class InspectionResult
{
protected:
    string title;               // The title of the paper.
    bool inspectionResult;      // The inspection result.
    virtual void setInspectionResult() = 0;
public:
    // Default constructor.
    InspectionResult()
        { inspectionResult = false; }
    
    // Constructor.
    InspectionResult(const string &t)
        { inspectionResult = false; }

    // Accessor functions.
    string getTitle() const
        { return title; }
    
    bool getInspectionResult() const
        { return inspectionResult; }

    // Mutator functions.
    void setTitle(const string &newTitle)
        { title = newTitle; }

    // Destructor.
    virtual ~InspectionResult() { };
};
#endif