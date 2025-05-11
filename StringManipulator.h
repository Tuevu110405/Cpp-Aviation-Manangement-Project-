#ifndef STRINGMANIPULATOR_H
#define STRINGMANIPULATOR_H
#include <string>
#include <cctype>
using namespace std;

class StringManipulator
{
public:
    static string capitalize(const string &);
    static string removeSpaces(const string &);
};
#endif