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
    vector<string> notes;       // The details of the inspection result.
    virtual void setInspectionResult() = 0;
public:
    // Default constructor.
    InspectionResult()
        { title = "blank";
          inspectionResult = false; }
    
    // Constructor.
    InspectionResult(string t)
        { title = t;
          inspectionResult = false; }

    // Accessor functions.
    string getTitle() const
        { return title; }
    
    bool getInspectionResult() const
        { return inspectionResult; }
    
    vector<string> getNotes() const
        { return notes; }

    void displayNotes() const
        {
            for (int count = 0; count < notes.size(); count++)
            {
                cout << "   " << notes[count] << endl;
            }
        }

    // Mutator functions.
    void setTitle(string newTitle)
        { title = newTitle; }
    
    void addNote(string newNote)
        { notes.push_back(newNote); }

    // Destructor.
    virtual ~InspectionResult() { };
};
#endif