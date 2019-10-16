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

    void putLexemeBack(int& fromPos,int& prevPos)
    {
        fromPos = prevPos;
    }

    string getNextLexem(int& fromPos,int& prevPos)
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
                if (rawStr[fromPos] == '.') pointsNum++;
                if (pointsNum > 1) throw new WrongNumberFormat(rawStr);
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
        double tmp;
        string lexeme = getNextLexem(fromPos,prevPos);
        if (lexeme == "-") tmp = Number(fromPos,prevPos);
        else if (lexeme == "+") throw new NotALexemeException(rawStr,fromPos - 1); //"-1" because getter will already go to next symbol there
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
                else if (lexeme == "+") throw new NotALexemeException(rawStr,fromPos - 1);//"-1" because getter will already go to next symbol there
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
                else if (lexeme == "+") throw new NotALexemeException(rawStr,fromPos - 1);//"-1" because getter will already go to next symbol there
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

    double Number(int& fromPos,int& prevPos)
    {
        int minusNum = 1;
        string lexeme;
        while(true)
        {
            lexeme = getNextLexem(fromPos,prevPos);
            if ((lexeme == "+") || (lexeme == "/") || (lexeme == "*")) throw new NotALexemeException(rawStr,fromPos - 1); //"-1" because getter will already go to next symbol there
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

public:

    Calc(const char* rawStr)
    {
        this->rawStr = string(rawStr);
        this->rawStrSize = this->rawStr.size();
    }

    double calculate()
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

};