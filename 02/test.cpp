#include "allocator.hpp"
#include <iostream>
#include <cstring>

int main(int argc, char const *argv[])
{
    LinerAllocator allocator(100);
    char* pointer = allocator.alloc(101);
    // std::cout << (pointer) << std::endl;    
    // allocator.reset();
    return 0;
}
