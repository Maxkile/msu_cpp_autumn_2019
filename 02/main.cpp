#include "allocator.hpp"
#include <iostream>
#include <cstring>

int main(int argc, char const **argv)
{
    if (argv[1] != nullptr)
    {
        LinerAllocator allocator(strtoul(argv[1],NULL,0));
        std::cout << allocator.getMaxSize()  << std::endl;
        for(int i = 2;i<argc;++i)
        {
            if (!strcmp(argv[i],"--reset"))
            {
                allocator.reset();
                //After reset
                std::cout << allocator.getLeftSize() << std::endl;
            }
            else if (allocator.alloc(strtoul(argv[i],NULL,0)) != nullptr)
            {
                //Can allocate
                std::cout <<  allocator.getLeftSize()  << std::endl;
            }
            else
            {
                //Can't allocate
                std::cout << "!" << strtoul(argv[i],NULL,0) << std::endl;
            }               
        }
    }
    else
    {
        std::cout << "No input" << std::endl;
    }
    return 0;
}
