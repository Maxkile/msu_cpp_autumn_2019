#include <iostream>
#include <cstring>
#include <string>
#include <list>
#include <cstdlib>

using namespace std;

class Exception{
	virtual void printLog(const string& str,int pos) const = 0;
};

class NotALexemeException: public Exception
{
public:
	NotALexemeException(const string& str,int pos)
	{
		printLog(str,pos);
	}

	void printLog(const string& str,int pos) const override
	{
		cout << "\"" << "Wrong symbol " << "\'" << str[pos] << "\'" << " in " << str << " in pos " << pos << "\"" << endl;
	} 

};

class DivideByZero: public Exception
{
public:
	DivideByZero()
	{
		printLog();
	}

	void printLog(const string& str = "",int pos = 0) const override
	{
		cout << "Divide by zero!" << endl;
	} 

};

class WrongNumberFormat: public Exception
{
public:
    WrongNumberFormat(const string& str)
    {
        printLog(str);
    }

    void printLog(const string& str,int pos = 0) const override
    {
        cout << "\"" << "Wrong number format in " <<  "\'" << str << "\'" << endl;
    }
};

class Calc
{

    string rawStr;
    int rawStrSize;

    int countMinus(int& fromPos)
    {
        int num = 0;
        while(true)
        {
            if (rawStr[fromPos] == '+') throw new NotALexemeException(rawStr,fromPos); 
            else if (rawStr[fromPos] == '-')
            {
                num++;
                fromPos++;
            } 
            else break;
        }
        return num;
    }

    void putLexemeBack(int& fromPos,int& prevPos)
    {
        fromPos = prevPos;
    }

    string getNextLexem(int& fromPos,int& prevPos)
    {
        string tmp = "";
		int rawStrLen = rawStr.size();
        int points = 0;
        bool prevWasDigit = false;
        prevPos = fromPos;
        while(fromPos < rawStrLen)
		{
			if(isspace(rawStr[fromPos]))
			{
				prevWasDigit = false;
				if (!tmp.empty())
				{
                    if ((tmp[0] == '.') || (tmp[tmp.size() - 1] == '.')) throw new WrongNumberFormat(rawStr);
                    else
                    {
                        return tmp;
                    }
				}
				fromPos++;
			} 
			else if (isdigit(rawStr[fromPos]) || rawStr[fromPos] == '.')
			{
                if (rawStr[fromPos] == '.') points++;
                if (points > 1) throw new WrongNumberFormat(rawStr);
                else
                {
				    prevWasDigit = true;    
				    tmp += rawStr[fromPos];
				    fromPos++;
                }
			}
			else if ((rawStr[fromPos] == '*') || (rawStr[fromPos] == '/'))
			{
                if ((rawStr[fromPos+1] == '*') || (rawStr[fromPos+1] == '/') || (fromPos == 0)) throw new NotALexemeException(rawStr,fromPos);
                else if (prevWasDigit)
				{
                    if ((tmp[0] == '.') || (tmp[tmp.size() - 1] == '.')) throw new WrongNumberFormat(rawStr);
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
            else if ((rawStr[fromPos] == '+') || (rawStr[fromPos] == '-'))
            {
                if (prevWasDigit)
				{
                    if ((tmp[0] == '.') || (tmp[tmp.size() - 1] == '.')) throw new WrongNumberFormat(rawStr);
                    else
                    {
                        return tmp;
                    }
				}
                int mincnt = 0;
                if (rawStr[fromPos] == '-') mincnt++;
                fromPos++;
                mincnt += countMinus(fromPos);
                if ((mincnt % 2) != 0) tmp+='-';
                else tmp+='+';
                prevWasDigit = false;
                return tmp;
            }
			else throw new NotALexemeException(rawStr,fromPos);
		}
		if (!tmp.empty())
		{
           if ((tmp[0] == '.') || (tmp[tmp.size() - 1] == '.')) throw new WrongNumberFormat(rawStr);
           else
           {
               return tmp;
           }
		}
        throw new NotALexemeException(rawStr,fromPos);	
    }
    
    double term(int& fromPos,int& prevPos)
	{
        string lexeme = getNextLexem(fromPos,prevPos);
        // double tmp;
        // if (lexeme == "-") tmp = (-1)*atof(getNextLexem(fromPos,prevPos).c_str());
        // else if (lexeme == "+")
        // {
        //     tmp = atof(getNextLexem(fromPos,prevPos).c_str());
        // }
        double tmp = atof(lexeme.c_str());
        while(fromPos < rawStrSize)
        {
            string lexeme = getNextLexem(fromPos,prevPos);
            if (lexeme == "*")
            {
                lexeme = getNextLexem(fromPos,prevPos);
                double num;
                if (lexeme == "-") num = signNumber(fromPos,prevPos);
                else if (lexeme == "+") throw new NotALexemeException(rawStr,fromPos - 1);//"-1" because getter will go to next symbol there
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
                    cout << "HERE" << endl;
                    num = signNumber(fromPos,prevPos);
                } 
                else if (lexeme == "+") throw new NotALexemeException(rawStr,fromPos - 1);//"-1" because getter will go to next symbol there
                else
                {
                    num = atof(lexeme.c_str());
                }
			    if (num == 0) throw new DivideByZero();
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

    double signNumber(int& fromPos,int& prevPos)
    {
        int minusNum = 1;
        string lexem;
        while(true)
        {
            lexem = getNextLexem(fromPos,prevPos);
            if (lexem == "+") throw new NotALexemeException(rawStr,fromPos); 
            else if (lexem == "-")
            {
                minusNum++;
                fromPos++;
            } 
            else break;
        }
        if ((minusNum % 2) != 0)
        {
            return (-1)*atof(lexem.c_str());
        } 
        else return atof(lexem.c_str());
    }

public:

    Calc(const char* rawStr)
    {
        this->rawStr = string(rawStr);
        this->rawStrSize = this->rawStr.size();
    }

    double calculate()
	{
        cout << "CALCULATE" << endl;
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

};