#include "../include/StringManipulator.h"

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