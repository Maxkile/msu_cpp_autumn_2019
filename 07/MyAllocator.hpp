#include <exception>
#include <type_traits>

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

    template<typename... Args>
    void construct(pointer,Args&&...);

    void destroy(pointer);

    ~MyAllocator();
};

template<typename T>
MyAllocator<T>::MyAllocator(){}

template<typename T>
MyAllocator<T>::~MyAllocator(){}

template<typename T>
template<typename... Args>
void MyAllocator<T>::construct(pointer ptr,Args&&... args)
{
    ::new(static_cast<void*>(ptr)) value_type(std::forward<Args>(args)...);//constuctor from raw mem
}

template<typename T>
void MyAllocator<T>::destroy(pointer ptr)
{
    //Complier automatically detects if it is primitive or not and to call destructor or not
    static_cast<T*>(ptr)->~T();
}

template<typename T>
T* MyAllocator<T>::allocate(size_type elemNumber)
{   
    pointer ptr;
    if ((ptr = static_cast<pointer>(::operator new(sizeof(value_type) * elemNumber))) == nullptr)//raw mem
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