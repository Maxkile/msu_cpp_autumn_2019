#include <vector>
#include <deque>
#include <exception>

#pragma once

template<typename T>
class MyAllocator
{
    T* usingMem_;//using memory in current block
    std::deque<std::vector<T>> memBlocks_;
    // size_t available_;//memory available_ in current block

public:
    MyAllocator();

    T* allocate(size_t);

    void deallocate(T*,size_t);

    size_t getAvailable();
    ~MyAllocator();
};

template<typename T>
MyAllocator<T>::MyAllocator(){}

template<typename T>
MyAllocator<T>::~MyAllocator(){}

// template<typename T>
// size_t MyAllocator<T>::getAvailable()
// {
//     return available_;
// }

template<typename T>
T* MyAllocator<T>::allocate(size_t memSize)
{
    memBlocks_.emplace_back(std::vector<T> (memSize));
    usingMem_ = &(memBlocks_.back().front());
    T* allocated = usingMem_;
    // if (memSize > available_)
    // {
    //     memBlocks_.emplace_back(std::vector<T> (memSize));//emplacing block
    //     available_ = memSize;
    //     usingMem_ = &(memBlocks_.back().front());//pointer to the first element of first deque element
    // }
    // available_ -= memSize;
    // T* allocated = usingMem_;
    // usingMem_ += sizeof(T) * memSize;//moving pointer,not like this
    return allocated;
}

template<typename T>
void MyAllocator<T>::deallocate(T* pointer)
{
    if (memSize > memBlocks_.back().size() || (memBlocks_.size() == 1))//trying to deallocate more than we have in block
    {
        throw std::bad_alloc();
    }
    else
    {
        memBlocks_.pop_back();
        if (memBlocks_.size() == 0)
        {
            usingMem_ = nullptr;
        }
        else
        {
            usingMem_ = &(memBlocks_.back().front());
        }
    }
    
}