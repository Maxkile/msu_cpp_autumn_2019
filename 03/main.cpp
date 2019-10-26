#include "MatrSum.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cout << "Input one of these commands: \"--elem\",\"--sizes\",\"--compare\",\"--mult\",\"--default\"" << std::endl;
        return(1);
    }
    else
    {
        try
        {
            const size_t rows = 6;
            const size_t cols = 4;
            Matrix m1(rows, cols);
            Matrix m2(rows, cols);
            m1 = 2;
            m2 = 3;
            if (!strcmp(argv[1],"--elem"))
            {
                if (argc < 4)
                {
                    std::cout << "Row and column expected!" << std::endl;
                    return(1);
                }
                else
                {
                    std::cout << m1[atoi(argv[2])][atoi(argv[3])] << std::endl;   
                }
            }
            else if (!strcmp(argv[1],"--sizes"))
            {
                std::cout << m1.getRowsNumber() << ' ' << m1.getColumnsNumber() << std::endl;
            }
            else if (!strcmp(argv[1],"--compare"))
            {
                std::cout << std::boolalpha;
                std::cout << (m1 == m2) << std::endl;
            }
            else if (!strcmp(argv[1],"--mult"))
            {
                if (argc < 3)
                {
                    std::cout << "Number expected!" << std::endl;
                    return(1);
                }
                else
                {
                    std::cout << (m1*=atoi(argv[2]))[0][0] << std::endl;
                }
            }
            else if (!strcmp(argv[1],"--default"))
            {
                const size_t rows = 5;
                const size_t cols = 3;

                Matrix m(rows, cols);

                assert(m.getRowsNumber() == 5);
                assert(m.getColumnsNumber() == 3);

                m[1][2] = 5; // строка 1, колонка 2
                
                m *= 3; // умножение на число

                Matrix m1(rows, cols);

                if (m1 == m)
                {
                    std::cout << "EQUAL" << std::endl;
                }
            }
            else
            {
                std::cout << "Input one of these commands: \"--elem\",\"--sizes\",\"--compare\",\"--mult\",\"--default\"" << std::endl;
                return(1);
            }
        }
        catch(std::exception& exc)
        {
            std::cout << exc.what() << std::endl;
            return(2);
        }
        
    return(0);
        
    }
    
}
