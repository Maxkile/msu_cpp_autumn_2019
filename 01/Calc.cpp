#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <string>

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

class EmptyString: public Exception
{
public:
	EmptyString()
	{
		printLog();
	}

	void printLog(const string& str = "",int pos = 0) const override
	{
		cout << "Empty string!" << endl;
	} 

};

class DoubleSign: public Exception
{
public:
	DoubleSign(const string& str)
	{
		printLog(str);
	}

	void printLog(const string& str,int pos = 0) const override
	{
		cout << "Double sign " << "\'" << str << "\'" << endl;
	} 

};

class Calc
{
	double result;
	vector<string> lexemes;

	void parseStr(const char* rawStr)
	{
		lexemes.clear();
		string tmp = "";
		int rawStrLen = strlen(rawStr);
		bool prevWasDigit = false;
		int i = 0;
		while(i<rawStrLen)
		{
			if(isspace(rawStr[i]))
			{
				prevWasDigit = false;
				if (!tmp.empty())
				{
					lexemes.push_back(tmp);
					tmp.clear();
				}
				i++;
			} 
			else if (isdigit(rawStr[i]) || rawStr[i] == '.')
			{
				prevWasDigit = true;
				tmp += rawStr[i];
				i++;
			}
			else if ((rawStr[i] == '+') || (rawStr[i] == '-') || (rawStr[i] == '*') || (rawStr[i] == '/'))
			{
				if (prevWasDigit)
				{
					lexemes.push_back(tmp);
					tmp.clear();
				}
				tmp += rawStr[i];
				lexemes.push_back(tmp);
				i++;
				tmp.clear();
			}
			else throw new NotALexemeException(rawStr,i);
		}
		if (!tmp.empty())
		{
			lexemes.push_back(tmp);
			tmp.clear();
		}
		if (lexemes.empty()) throw new EmptyString();
		else if ((lexemes[lexemes.size() - 1] == "+") || (lexemes[lexemes.size() - 1] == "-") || (lexemes[lexemes.size() - 1] == "*") || (lexemes[lexemes.size() - 1] == "/")) throw new NotALexemeException(rawStr,strlen(rawStr) - 1);

		
	}

	void detectUnary()
	{	
		// if (lexemes[])
		string prevLexeme = lexemes[0];//indicator that previous lexeme was "+" or "-"
		for(unsigned long  i = 1;i < lexemes.size();++i)
		{
			if (((lexemes[i] == "+") || (lexemes[i] == "-")) && ((prevLexeme == "+") || (prevLexeme == "-")))
			{
				
			}
			else if (((lexemes[i] == "*") || (lexemes[i] == "/")) && (prevLexeme == lexemes[i])) throw new DoubleSign(prevLexeme);

		}
	}

	void START()
	{

	}

	void PREFIX()
	{

	}


public:

	Calc(const char* rawStr)
	{
		parseStr(rawStr);
		result = 0;
	}

	vector<string> getLexemes()
	{
		return lexemes;
	}

	void printLexemes()
	{
		for (vector<string>::iterator i = lexemes.begin(); i != lexemes.end();++i)
		{
			cout << *i << endl;
		}
	}
};	

	

	
