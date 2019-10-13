#include "CalcList.cpp"
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <string>

int main(int argc, char const *argv[])
{
	try
	{
		Calc calc = Calc::getInstance("+12*3-----/+-12+++--++3/1--+-*++23");
		cout << calc.calculate() << endl;
		// calc.printLexemes();
	} catch(Exception* exp)
		{
			exit(1);
		};

	return 0;
}