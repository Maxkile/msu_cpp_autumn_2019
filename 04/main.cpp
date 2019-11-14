#include <iostream>
#include <cstdlib>
#include <limits>
#include "BigInteger.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    bool useInt = false;
    int repeat = 1;
    int leftOperand;
    int rightOperand;
    char op[2];

    if (argc < 4)
    {
        cout << "Too few arguments!" << endl;
        return 1;
    }
    else//operator,operation,operator
    {
        if (!strcmp(argv[1],"-n"))
        {
            repeat = atoi(argv[2]);
            if (repeat < 1)
            {
                cout << "Wrong repeat time!" << endl;
                return 1;
            }
            else
            {
                if (!strcmp(argv[3],"-i"))//use integers as right arguments
                {
                    useInt = true;
                    leftOperand = atoi(argv[4]);
                    strcpy(op,argv[5]);
                    rightOperand = atoi(argv[6]);
                }
                else
                {
                    leftOperand = atoi(argv[3]);
                    strcpy(op,argv[4]);
                    rightOperand = atoi(argv[5]);
                }
            }
            
        }
        else if (!strcmp(argv[1],"-i"))
        {
            useInt = true;
            if (!strcmp(argv[2],"-n"))
            {
                repeat = atoi(argv[3]);
                if (repeat < 1)
                {
                    cout << "Wrong repeat time!" << endl;
                    return 1;
                }
                else
                {
                    leftOperand = atoi(argv[4]);
                    strcpy(op,argv[5]);
                    rightOperand = atoi(argv[6]);
                }
                
            }
            else
            {
                leftOperand = atoi(argv[2]);
                strcpy(op,argv[3]);
                rightOperand = atoi(argv[4]);
            }

        }
        else
        {
            leftOperand = atoi(argv[1]);
            strcpy(op,argv[2]);
            rightOperand = atoi(argv[3]);
        }

        BigInteger res;
        bool compRes;

        std::cout << std::boolalpha; 

        if (useInt)
        {
            BigInteger bi_1(leftOperand);
            int bi_2 = rightOperand;
            if (!strcmp(op,"+"))
            {
                res = bi_1 + bi_2;
                for (int i = 1;i<repeat;++i)
                {
                    res += bi_2;
                }

                cout << res;
            }
            else if (!strcmp(op,"-"))
            {
                res = bi_1 - bi_2;
                for (int i = 1;i<repeat;++i)
                {
                    res -= bi_2;
                }
                cout << res;
            }
            else if (!strcmp(op,"<"))
            {
                compRes = bi_1 < bi_2;
                cout << compRes;
            }
            else if (!strcmp(op,">"))
            {
                compRes = bi_1 > bi_2;
                cout << compRes; 
            }
            else if (!strcmp(op,"<="))
            {
                compRes = bi_1 <= bi_2;
                cout << compRes;
            }
            else if (!strcmp(op,">="))
            {
                compRes = bi_1 >= bi_2;
                cout << compRes;
            }
            else if (!strcmp(op,"=="))
            {
                compRes = bi_1 == bi_2;
                cout << compRes;
            }
            else if (!strcmp(op,"!="))
            {
                compRes = bi_1 != bi_2;
                cout << compRes;
            }
            else
            {
                cout << "Unsupported operator type!";
                return 1;   
            }
        }
        else
        {
            BigInteger bi_1(leftOperand);
            BigInteger bi_2(rightOperand);

            if (!strcmp(op,"+"))
            {
                res = bi_1 + bi_2;
                for (int i = 1;i<repeat;++i)
                {
                    res += bi_2;
                }

                cout << res;
            }
            else if (!strcmp(op,"-"))
            {
                res = bi_1 - bi_2;
                for (int i = 1;i<repeat;++i)
                {
                    res -= bi_2;
                }
                cout << res;
            }
            else if (!strcmp(op,"<"))
            {
                compRes = bi_1 < bi_2;
                cout << compRes;
            }
            else if (!strcmp(op,">"))
            {
                compRes = bi_1 > bi_2;
                cout << compRes; 
            }
            else if (!strcmp(op,"<="))
            {
                compRes = bi_1 <= bi_2;
                cout << compRes;
            }
            else if (!strcmp(op,">="))
            {
                compRes = bi_1 >= bi_2;
                cout << compRes;
            }
            else if (!strcmp(op,"=="))
            {
                compRes = bi_1 == bi_2;
                cout << compRes;
            }
            else if (!strcmp(op,"!="))
            {
                compRes = bi_1 != bi_2;
                cout << compRes;
            }
            else
            {
                cout << "Unsupported operator type!";
                return 1;   
            }
        }
        
    }
}