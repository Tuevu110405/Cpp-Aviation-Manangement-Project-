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
        InvalidDay(int d)
            { value = d; }
        int getValue() const
            { return value; }
    };

    class InvalidYear
    {
    private:
        int value;
    public:
        InvalidYear(int y)
            { value = y; }
        int getValue() const
            { return value; }
    };

    class InvalidDate
    {
    private:
        string date;
    public:
        InvalidDate(string d)
            { date = d; }
        string getDate() const
            { return date; }
    };

    // Default constructor.
    Date()
        { month = day = year = 0; }
    // Constructors.
    Date(int m, int d, int y);
    Date(string date);
    
    // Accessor functions.
    int getMonth() const
        { return month; }
    int getDay() const
        { return day; }
    int getYear() const
        { return year; }
    string getDate() const
        { return (to_string(month) + "/" + to_string(day) + "/" + to_string(year)); }
    
    // Functions to validate the date.
    bool isLeapYear() const;
    
    // Mutator functions.
    void setMonth(int newMonth);
    void setDay(int newDay);
    void setYear(int newYear);
    void setDate(string date);

    // Overloaded operators.
    bool operator > (const Date &date);
    friend istream &operator >> (istream &, Date &);
    friend ostream &operator << (ostream &, const Date &);
};
#endif