#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstring>

#include "BinSort.hpp"


using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 4)//without "--gen" flag 
    {
        if (argc < 3)
        {
            cerr << "Input and output filenames are required. If you want to generate data for sorting, use \"--gen\" flag." << endl;
            return 1;
        }
        else
        {
            string fileName(argv[1]);
            string outFileName(argv[2]);
            ifstream input(fileName);
            try
            {
                if (!input)
                {
                    throw runtime_error(fileName);
                }
                swapsort::fileSort(fileName,outFileName);
            }
            catch(exception& exc)
            {
                cerr << exc.what() << endl;
                return 1;
            }
            input.close();
            return 0;
        }
    }
    else//with "--gen" flag 
    {
        if (!strcmp(argv[2],"--gen"))
        {
            cout << "Wrong flag. Must be \"--gen\"" << endl;
            return 1;
        }
        else
        {
            string fileName(argv[2]);
            string outFileName(argv[3]);
            swapsort::generateRandom(fileName,1000);
            ifstream input(fileName);
            try
            {
                if (!input)
                {
                    throw runtime_error(fileName);
                }
                swapsort::fileSort(fileName,outFileName);
            }
            catch(exception& exc)
            {
                cerr << exc.what() << endl;
                return 1;
            }
            input.close();
            return 0;
        }

    }
    
}
