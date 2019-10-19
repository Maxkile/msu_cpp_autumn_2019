#include "allocator.hpp"

LinerAllocator::LinerAllocator(size_t maxSize):maxSize(maxSize),left(maxSize)
{
    if (maxSize == 0)
    {
        pointerStart = nullptr;
        movingPointer = nullptr;
    } 
    else
    {
        pointerStart = (char*)malloc(maxSize*sizeof(char));
        movingPointer = pointerStart; 
    } 
}

char* LinerAllocator::alloc(size_t size)
{
    if ((left == 0) || (size > left))
    {
        return nullptr;   
    }
    else 
    {   
        left -= size;
        char* oldPointer = movingPointer;
        movingPointer += size*sizeof(char);
        return oldPointer;
    }
}

size_t LinerAllocator::getMaxSize()
{
    return maxSize;
}

size_t LinerAllocator::getLeftSize()
{
    return left;
}

void LinerAllocator::reset()
{
    movingPointer = pointerStart;
    left = maxSize;
}

LinerAllocator::~LinerAllocator()
{
    free(pointerStart);
}
