#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <cstdlib>

#ifndef _CALC
#define _CALC

using namespace std;

// class Exception{
// 	virtual void printLog(const string& str,int pos) const = 0;
// };

// class NotALexemeException: public Exception
// {
// public:
// 	NotALexemeException(const string& str,int pos);

// 	void printLog(const string& str,int pos) const;

// };

// class DivideByZero: public Exception
// {
// public:
// 	DivideByZero();

// 	void printLog(const string& str = "",int pos = 0) const;

// };

// class WrongNumberFormat: public Exception
// {
// public:
//     WrongNumberFormat(const string& str);

//     void printLog(const string& str,int pos = 0) const;
// };


class Calc
{
    string rawStr;
    int rawStrSize;

    void putLexemeBack(int& fromPos,int& prevPos);

    string getNextLexem(int& fromPos,int& prevPos);
    
    double term(int& fromPos,int& prevPos);

    double Number(int& fromPos,int& prevPos);

public:

    Calc(const char* rawStr);

    double calculate();
};

#endif