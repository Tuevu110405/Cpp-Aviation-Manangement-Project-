#include "../include/Date.h"
#include "../include/StringManipulator.h"
#include <cctype>
#include <sstream>

// Constructors.
Date::Date(const string &date)
{
    try
    {
        setDate(date);
    }
    catch(InvalidDate d)
    {
        throw d;
    }
    catch(InvalidYear y)
    {
        throw y;
    }
    catch(InvalidMonth m)
    {
        throw m;
    }
    catch(InvalidDay d)
    {
        throw d;
    }
}


Date::Date(const int &m, const int &d, const int &y)
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


// Function Date::isLeapYear
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


// Function Date::setMonth
void Date::setMonth(const int &newMonth)
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


// Function Date::setDay
void Date::setDay(const int &newDay)
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


// Function Date::setYears
void Date::setYear(const int &newYear)
{
    // If the year is negative, throws an exception.
    if (newYear < 0 || newYear > 9999)
    {
        throw InvalidYear(newYear);
    }
    // Otherwise, store it in the member variable.
    year = newYear;
}


// Function Date::setDate
void Date::setDate(const string &date)
{
    // Remove spaces in the argument.
    string processedDate = StringManipulator::removeSpaces(date);

    // Check if the argument contain invalid characters.
    for (int count = 0; count < processedDate.length(); count++)
    {
        if (!isdigit(processedDate[count]) && 
            processedDate[count] != '/')
        {
            throw InvalidDate(processedDate);
        }
    }

    // Check if the argument is in valid formats (MM/DD/YYYY).
    int numOfSlashes = 0;
    const int MAX_LENGTH = 10;
    const int MIN_LENGTH = 8;

    // If the length is invalid, then throws an exception.
    if (processedDate.length() > MAX_LENGTH || processedDate.length() < MIN_LENGTH)
    {
        throw InvalidDate(processedDate);
    }

    // Count the number of slashes.
    for (int count = 0; count < processedDate.length(); count++)
    {
        if (processedDate[count] == '/')
            numOfSlashes++;
    }

    // If the number slashes is not 2, then throws an exception.
    if (numOfSlashes != 2)
    {
        throw InvalidDate(processedDate);
    }

    // Parse the string into month, day, and year.
    stringstream ss(processedDate);     // Convert into a stream.
    string token;
    int month, day, year;

    // Get the month of the date and convert to int.
    getline(ss, token, '/');
    month = stoi(token);

    // Get the day of the date and convert to an int.
    getline(ss, token, '/');
    day = stoi(token);

    // Get the year of the date and convert to an int.
    getline(ss, token);
    year = stoi(token);
    
    // Assigns the value of month, day, and year to member variables.
    try
    {
        setYear(year);
        setMonth(month);
        setDay(day);
    }
    catch(InvalidYear y)
    {
        throw y;
    }
    catch(InvalidMonth m)
    {
        throw m;
    }
    catch(InvalidDay d)
    {
        throw d;
    }
}


// Overloaded operator: >
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


// Overloaded operator: cin >>
istream &operator >> (istream &strm, Date &obj)
{
    // Variable declaration.
    string date;

    // Validate the input.
    while (true)
    {
        try
        {
            cout << "Enter the month, day, year (MM/DD/YYYY): ";
            getline(strm, date);
            obj.setDate(date);
            break;
        }
        // Handle the exception when the date is invalid.
        catch (Date::InvalidDate d)
        {
            cout << "Error: The date " << d.getDate()
                 << " is invalid format.\n";
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


// Overloaded operator: cout <<
ostream &operator << (ostream &strm, const Date &obj)
{
    strm << obj.getMonth() << "/" << obj.getDay() << "/" << obj.getYear();
    return strm;
}