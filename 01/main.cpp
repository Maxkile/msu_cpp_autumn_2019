#include "Calc.hpp"

int main(int argc, char const *argv[])
{
	try{
		if (argv[1] == nullptr)
		{
			cout << "No input expression!" << endl;
			return(1);
		}
		else
		{
			Calc calc(argv[1]);
			cout << calc.calculate();
		} 
	} catch(Exception& exp)
		{
			return(2);
		}
	return 0;
}