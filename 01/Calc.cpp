#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <cstdlib>
#include "Calc.hpp"

using namespace std;


NotALexemeException::NotALexemeException(const string& str,int pos)
{
	printLog(str,pos);
}

void NotALexemeException::printLog(const string& str,int pos) const
{
	cout << "\"" << "Wrong symbol " << "\'" << str[pos] << "\'" << " in " << str << " in pos " << pos << "\"" << endl;
} 

DivideByZero::DivideByZero()
{
	printLog();
}

void DivideByZero::printLog(const string& str,int pos) const
{
	cout << "Divide by zero!" << endl;
} 


WrongNumberFormat::WrongNumberFormat(const string& str)
{
    printLog(str);
}

void WrongNumberFormat::printLog(const string& str,int pos) const
{
    cout << "\"" << "Wrong number format in " <<  "\'" << str << "\'" << endl;
}

void Calc::putLexemeBack(int& fromPos,int& prevPos)
{
    fromPos = prevPos;
}

string Calc::getNextLexem(int& fromPos,int& prevPos)
{
    string tmp = "";
    int rawStrLen = rawStr.size();
    int pointsNum = 0;
    bool prevWasDigit = false;
    prevPos = fromPos;//used to implement putback
    while(fromPos < rawStrLen)
	{
	    if(isspace(rawStr[fromPos]))
		{
		    prevWasDigit = false;
			if (!tmp.empty())
			{
                if ((tmp[0] == '.') || (tmp[tmp.size() - 1] == '.')) throw WrongNumberFormat(rawStr);
                else
                {
                    return tmp;
                }
			}
			fromPos++;
		} 
		else if (isdigit(rawStr[fromPos]) || rawStr[fromPos] == '.')
		{
            if (rawStr[fromPos] == '.') pointsNum++;
            if (pointsNum > 1) throw WrongNumberFormat(rawStr);
            else
            {
			    prevWasDigit = true;    
				tmp += rawStr[fromPos];
				fromPos++;
            }
		}
		else if ((rawStr[fromPos] == '*') || (rawStr[fromPos] == '/') || (rawStr[fromPos] == '+') || (rawStr[fromPos] == '-'))
		{
            if (prevWasDigit)
		    {
                if ((tmp[0] == '.') || (tmp[tmp.size() - 1] == '.')) throw WrongNumberFormat(rawStr);
                else
                {
                    return tmp;
                } 
			}
            else
            {
                tmp+=rawStr[fromPos];
			    prevWasDigit = false;
                fromPos++;
				return tmp;
            }
		}
		else throw NotALexemeException(rawStr,fromPos);
	}
	if (!tmp.empty())
	{
        if ((tmp[0] == '.') || (tmp[tmp.size() - 1] == '.')) throw WrongNumberFormat(rawStr);
        else
        {
            return tmp;
        }
	}
    throw NotALexemeException(rawStr,fromPos);	
}
    
double Calc::term(int& fromPos,int& prevPos)
{
    double tmp;
    string lexeme = getNextLexem(fromPos,prevPos);
    if (lexeme == "-") tmp = Number(fromPos,prevPos);
    else if (lexeme == "+") throw NotALexemeException(rawStr,fromPos - 1); //"-1" because getter will already go to next symbol there
    else
    {
       tmp = atof(lexeme.c_str());
    }
    while(fromPos < rawStrSize)
    {
        string lexeme = getNextLexem(fromPos,prevPos);
        if (lexeme == "*")
        {
            lexeme = getNextLexem(fromPos,prevPos);
            double num;
            if (lexeme == "-") num = Number(fromPos,prevPos);
            else if (lexeme == "+") throw NotALexemeException(rawStr,fromPos - 1);//"-1" because getter will already go to next symbol there
            else
            {
                num = atof(lexeme.c_str());
            }
			tmp*=num;
		}
		else if (lexeme == "/")
		{
            lexeme = getNextLexem(fromPos,prevPos);
            double num;
            if (lexeme == "-")
            {
                num = Number(fromPos,prevPos);
            } 
            else if (lexeme == "+") throw NotALexemeException(rawStr,fromPos - 1);//"-1" because getter will already go to next symbol there
            else
            {
                num = atof(lexeme.c_str());
            }
			if (num == 0) throw DivideByZero();
			else	
			{
			    tmp/=num;
			}
		}
		else
		{
		    putLexemeBack(fromPos,prevPos);
			return tmp;
		}
    }
    return tmp;
}

double Calc::Number(int& fromPos,int& prevPos)
{
    int minusNum = 1;
    string lexeme;
    while(true)
    {
        lexeme = getNextLexem(fromPos,prevPos);
        if ((lexeme == "+") || (lexeme == "/") || (lexeme == "*")) throw NotALexemeException(rawStr,fromPos - 1); //"-1" because getter will already go to next symbol there
        else if (lexeme == "-")
        {
            minusNum++;
        } 
        else break;
    }
    if (((minusNum % 2) != 0) && (lexeme != "0"))
    {
        return (-1)*atof(lexeme.c_str());
    } 
    else return atof(lexeme.c_str());
}

Calc::Calc(const char* rawStr)
{
    this->rawStr = string(rawStr);
    this->rawStrSize = this->rawStr.size();
}

double Calc::calculate()
{
	int fromPos = 0;
    int prevPos = fromPos;
    double result = term(fromPos,prevPos);
    while(fromPos < rawStrSize)
    {
        string lexeme = getNextLexem(fromPos,prevPos);
        if (lexeme == "+")
		{
			result+=term(fromPos,prevPos);
		}   
		else if (lexeme == "-")
		{
			result-=term(fromPos,prevPos);
		}
		else
		{
			putLexemeBack(fromPos,prevPos);
	    	return result;
    	}
    }
    return result;
}
