#include <iostream>
#include <vector>
#include <map>
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

class EmptyStringException: public Exception
{
public:
	EmptyStringException()
	{
		printLog();
	}

	void printLog(const string& str = "",int pos = 0) const override
	{
		cout << "Empty string!" << endl;
	} 

};

class WrongPosException: public Exception
{
public:
	WrongPosException(const string& str)
	{
		printLog(str);
	}

	void printLog(const string& str,int pos = 0) const override
	{
		cout << "Wrong position of " << str << " sign" << endl;
	} 

};

class Calc
{
	double result;
	list<string> lexemes;

	Calc(list<string>& lexemes)
	{
		this->lexemes = lexemes;
		lexemes.clear();//clear unused lexemes list
		result = 0;
	}

	static list<string> parseStr(const char* rawStr)
	{

		list<string> lexemes;
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
				prevWasDigit = false;
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
		if (lexemes.empty()) throw new EmptyStringException();
		else if ((lexemes.back() == "+") || (lexemes.back()  == "-") || (lexemes.back() == "*") || (lexemes.back()  == "/")) throw new NotALexemeException(rawStr,strlen(rawStr) - 1);

		return lexemes;		
	}

	static list<string> processRepeatingOperations(const list<string>& lexemes)
	{	
		list<string> res;
		list<string>::const_iterator it = lexemes.begin();
		if ((*it == "*") || (*it == "/")) throw new WrongPosException(*it);
		for(list<string>::const_iterator i = lexemes.begin(); i != lexemes.end();++i)
		{
			if ((*i == "+") || (*i == "-"))
			{
				int minusNum = 0;
				if (*i == "-") minusNum++;
				do
				{
					i++;
					if (*i == "-") minusNum++;
				} while((*i == "+") || (*i == "-"));
				i--;//rollback
				if (minusNum % 2 == 0) res.push_back("+");
				else res.push_back("-");
			}
			else if ((*i == "*") || (*i == "/"))
			{
				i++;
				if ((*i == "*") || (*i == "/")) throw new WrongPosException(*i);
				else
				{
					i--;
					res.push_back(*i);
				} 
			}
			else
			{
				res.push_back(*i);
			}

		}
		return res;
	}

public:

	static Calc getInstance(const char* rawStr)
	{
		list<string> lexemes = parseStr(rawStr);
		list<string> modLexemes = processRepeatingOperations(lexemes);
		return Calc(modLexemes);
	}


	double calculate()
	{
		list<string>::iterator iter = lexemes.begin();
		result = TERM(iter);	
		while(iter != lexemes.end() || ((*iter == "+") || (*iter == "-")))
		{
			string oper = *iter;
			iter++;
			if (oper == "+") result = result + TERM(iter);
			else if (oper == "-") result = result - TERM(iter);
		}
		return result;
	}

	double TERM(list<string>::iterator& iter)
	{
		result = atof((*iter).c_str());
		while(iter != lexemes.end() || ((*iter == "*") || (*iter == "/")))
		{
			string oper = *iter;
			iter++;
			if (oper == "*") result = result * atof((*iter).c_str());
			else if (oper == "-") result = result / atof((*iter).c_str());
		}
		return 1;
	}

	list<string> getLexemes()
	{
		return lexemes;
	}

	void printLexemes()
	{
		for (list<string>::iterator i = lexemes.begin(); i != lexemes.end();++i)
		{
			cout << *i << endl;
		}
	}
};	

	

	
