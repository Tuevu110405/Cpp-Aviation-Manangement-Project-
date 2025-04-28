#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <string>
using namespace std;

class Date
{
private:
    int month;      // The month in a year.
    int day;        // The day in a month.
    int year;       // The year.
public:
    // Class for throwing exceptions.
    class InvalidMonth
    {
    private:
        int value;
    public:
        InvalidMonth(int m)
            { value = m; }
        int getValue() const
            { return value; }
    };

    class InvalidDay
    {
    private:
        int value;
    public:
        InvalidDay(int m)
            { value = m; }
        int getValue() const
            { return value; }
    };

    class InvalidYear
    {
    private:
        int value;
    public:
        InvalidYear(int m)
            { value = m; }
        int getValue() const
            { return value; }
    };

    // Default constructor.
    Date()
        { month = day = year = 0; }
    // Constructors.
    Date(int m, int d, int y);
    
    // Accessor functions.
    int getMonth() const
        { return month; }
    int getDay() const
        { return day; }
    int getYear() const
        { return year; }
    
    // Functions to validate the date.
    bool isLeapYear() const;
    
    // Mutator functions.
    void setMonth(int);
    void setDay(int);
    void setYear(int);

    // Overloaded operators.
    bool operator > (const Date &);
    bool operator == (const Date &);
    friend istream &operator >> (istream &, Date &);
    friend ostream &operator << (ostream &, const Date &);
};
#endif