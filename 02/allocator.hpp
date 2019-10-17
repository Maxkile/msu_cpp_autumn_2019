#pragma once
#include <cstdlib>

class LinerAllocator
{
    size_t maxSize;
    size_t left;
    char* pointerStart;
    char* movingPointer;

public:

    LinerAllocator(size_t maxSize);

    char* alloc(size_t size);

    size_t getMaxSize();

    size_t getLeftSize();

    void reset();

    ~LinerAllocator();

};




