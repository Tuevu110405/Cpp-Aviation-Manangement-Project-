#include "../include/Date.h"
#include <cctype>

// Definition of Constructor.
Date::Date(int m, int d, int y)
{
    // Try to assign arguments to the member variables.
    try
    {
        setYear(y);
        setMonth(m);
        setDay(d);
    }
    // Catch an exception thrown if the year is invalid.
    catch (InvalidYear y)
    {
        throw y;
    }
    // Catch an exception thrown if the month is invalid.
    catch (InvalidMonth m)
    {
        throw m;
    }
    // Catch an exception thrown if the day is invalid.
    catch (InvalidDay d)
    {
        throw d;
    }
}

// Definition of functions used to validate the date.
bool Date::isLeapYear() const
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return true;  // Divisible by 400, then leap year.
            }
            else
            {
                return false; // Divisible by 100 but not 400, so not a leap year.
            }
        }
        return true;    // Divisible by 4 and not by 100, so leap year.
    }
    return false; // Not divisible by 4, so not a leap year.
}

// Definition of Mutator functions.
void Date::setMonth(int newMonth)
{
    // If the month is less than 1 or greater than 12,
    // throw an exception.
    if (newMonth < 1 || newMonth > 12)
    {
        throw InvalidMonth(newMonth);
    }
    // Otherwise, store it in the member variable.
    month = newMonth;
}

void Date::setDay(int newDay)
{   
    // Arrays of constant integer for the number 
    // of days in a month.
    const int DAYS_LEAP_YEAR[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int DAYS_REGULAR_YEAR[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // If the day is invalid (or out of range),
    // then thows an exception.
    if (isLeapYear() && (newDay < 0 || newDay > DAYS_LEAP_YEAR[month - 1]))
    {
        throw InvalidDay(newDay);
    }
    if (!isLeapYear() && (newDay < 0 || newDay > DAYS_REGULAR_YEAR[month - 1]))
    {
        throw InvalidDay(newDay);
    }
    // Otherwise, store it in the member variable.
    day = newDay;
}

void Date::setYear(int newYear)
{
    // If the year is negative, throws an exception.
    if (newYear < 0 || newYear > 9999)
    {
        throw InvalidYear(newYear);
    }
    // Otherwise, store it in the member variable.
    year = newYear;
}

// Other functions.
bool Date::operator > (const Date &right)
{
    // If the year of the right-hand date is larger than
    // the year of the left-hand date, return true.
    if (year > right.year)
    {
        return true;
    }
    
    // Else if the year of the right-hand date is equal to
    // the year of the left-hand date.
    if (year == right.year)
    {
        // If the month of the right-hand date is larger than
        // the month of the left-hand date, return true.
        if (month > right.month)
        {
            return true;
        }

        // Else if the month of the right-hand date is equal to
        // the month of the left-hand date.
        if (month == right.month)
        {
            // If the day of the right-hand date is larger than 
            // the day of the left-hand date, return true.
            if (day > right.day)
            {
                return true;
            }
        }
    }

    // Otherwise, returns false.
    return false;
}

bool Date::operator == (const Date &right)
{
    if (year == right.year && month == right.month && day == right.day)
        return true;
    return false;
}

istream &operator >> (istream &strm, Date &obj)
{
    // Variables.
    int month, day, year;

    // Validate the input.
    while (true)
    {
        try
        {
            cout << "Enter the month, day, year (E.g: 09 25 2005): ";
            strm >> month >> day >> year;
            obj.setYear(year);
            obj.setMonth(month);
            obj.setDay(day);
            break;
        }
        // Handle the exception when the year is invalid.
        catch (Date::InvalidYear y)
        {
            cout << "Error: The value " << y.getValue();
            cout << " is invalid for year.\n";
        }
        // Handle the exception when the month is invalid.
        catch (Date::InvalidMonth m)
        {
            cout << "Error: The value " << m.getValue();
            cout << " is invalid the month.\n";
        }
        // Handle the exception when the day is invalid.
        catch (Date::InvalidDay d)
        {
            cout << "Error: The day " << d.getValue();
            cout << " is invalid.\n";
        }
    }

    return strm;
}

ostream &operator << (ostream &strm, const Date &obj)
{
    strm << obj.getMonth() << "/" << obj.getDay() << "/" << obj.getYear();
    return strm;
}