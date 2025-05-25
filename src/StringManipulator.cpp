#include "../include/StringManipulator.h"

// Function StringManipulator::capitalize (Hoang).
string StringManipulator::capitalize(const string &inputStr)
{
    string output = "";

    for (int index = 0; index < inputStr.length(); index++)
    {
        if (isalpha(inputStr[index]))
            output += toupper(inputStr[index]);
        else
            output += inputStr[index];
    }

    return output;
}

// Function StringManipulator::removespaces (Hoang).
string StringManipulator::removeSpaces(const string &inputStr)
{
    string output = "";

    for (int index = 0; index < inputStr.length(); index++)
    {
        if (!isspace(inputStr[index]))
            output += inputStr[index];
    }
    
    return output;
}

// Function StringManipulator::lowercase (Tue).
string StringManipulator::lowerCase(const string& str)
{
    string result = "";
    for (char c : str)
    {
        result += tolower(c);
    }
    return result;
}