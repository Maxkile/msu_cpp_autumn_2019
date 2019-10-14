#include "CalcSimple.cpp"
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <string>
#include <list>
#include <cstdlib>

int main(int argc, char const *argv[])
{
	try{
		if (argv[1] == nullptr)
		{
			cout << "No input expression!" << endl;
			exit(1);
		}
		else
		{
			Calc calc(argv[1]);
			cout << calc.calculate();
		} 
	} catch(Exception* exp)
		{
			exit(2);
		}
	return 0;
}