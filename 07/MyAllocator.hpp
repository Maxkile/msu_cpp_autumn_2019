#include <vector>
#include <deque>
#include <exception>

#pragma once

template<typename T>
class MyAllocator
{   
public:

    using value_type = T;
    using pointer = value_type*;
    using size_type = size_t;

    MyAllocator();

    pointer allocate(size_type);

    void deallocate(pointer);

    size_type getAvailable();

    ~MyAllocator();
};

template<typename T>
MyAllocator<T>::MyAllocator(){}

template<typename T>
MyAllocator<T>::~MyAllocator(){}

template<typename T>
T* MyAllocator<T>::allocate(size_type memSize)
{   
    pointer ptr;
    if ((ptr = static_cast<pointer>(::operator new(sizeof(value_type) * memSize))) == nullptr)
    {
        throw std::bad_alloc();
    }
    else
    {
        return ptr;
    }
}

template<typename T>
void MyAllocator<T>::deallocate(pointer ptr)
{
   ::operator delete(ptr);    
}