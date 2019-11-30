#include "MyIterator.hpp"
#include "MyAllocator.hpp"
#include <vector>

#pragma once

template <typename T,typename Allocator = MyAllocator<T>>
class MyVector
{
    T* first;
    T* last;//for size
    T* end;//for capacity

    Allocator allocator_;

    void reallocate(size_t newCapacity)
    {
        size_type oldSize = size();

        std::vector<value_type> temp;
        temp.reserve(oldSize);
        for(size_type i = 0; i < oldSize;++i)
        {
            temp.push_back(first[i]);
        }
        
        deleteVector();//delete oldMemory

        first = allocator_.allocate(newCapacity);
        last = first + sizeof(value_type) * oldSize;
        end = first + sizeof(value_type) * newCapacity;

        for(size_t i = 0;i < oldSize;++i)
        {
            first[i] = temp[i];
        }    
    }

    void deleteVector()
    {
        allocator_.deallocate(first);
        last = nullptr;
        end = nullptr;
    }

public:

    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const reference;
    using vector = MyVector<T>;
    using iterator = MyIterator<T>;
    using allocator_type = MyAllocator<T>;
    using size_type = size_t;

explicit MyVector(size_type initialLength = 0)
    {
        first = allocator_.allocate(initialLength);
        last = first;
        
        end = first + sizeof(value_type) * initialLength;
    }

    MyVector(const vector& other)
    {
        first = allocator_.allocate(other.capacity());
        last = first + sizeof(T) * other.size();
        end = first + sizeof(T) * other.capacity();

        for(size_type i = 0;i < other.size();++i)
        {
            first[i] = other.first[i];
        }
    }

    MyVector(const vector& other,const allocator_type& allocator)
    {
        allocator_ = allocator;
        first = allocator_.allocate(other.capacity());
        last = first + sizeof(T) * other.size();
        end = first + sizeof(T) * other.capacity();

        for(size_type i = 0;i < other.size();++i)
        {
            first[i] = other.first[i];
        }
    }

    //not taking allocator
    MyVector& operator=(const vector& other)
    {
        deleteVector();
        // allocator_ = other.get_allocator();
        first = allocator_.allocate(other.capacity());
        last = first + sizeof(T) * other.size();
        end = first + sizeof(T) * other.capacity();

        for(size_type i = 0;i < other.size();++i)
        {
            first[i] = other.first[i];
        }
        return *this;
    }

    void push_back(const value_type& elem)
    {   
        if (last == end)//need to reallocate
        {
            size_type capacity_ = capacity();
            capacity_ = capacity_ * 2 + 1;//reallocation is slow, so we reallocate extra
            reallocate(capacity_);
        }
        first[size()] = elem;
        last += sizeof(T);
    }

    void push_back(value_type&& elem)
    {   
        if (last == end)//need to reallocate
        {
            size_type capacity_ = capacity();
            capacity_ = capacity_ * 2 + 1;//reallocation is slow, so we reallocate extra
            reallocate(capacity_);
        }
        
        first[size()] = elem;
        last += sizeof(T);
    }

    void pop_back()
    {   
        last -= sizeof(T);
    }

    allocator_type get_allocator()
    {
        return allocator_;
    }

    reference operator[](size_type ind)
    {
        return first[ind];
    }

    const_reference operator[](size_type ind) const
    {
        return first[ind];
    }

    friend std::ostream& operator<<(std::ostream& out,const MyVector<T> v)
    {       
        for(MyVector::size_type i = 0;i < v.size();++i)
        {
            out << v[i] << " ";
        }

        return out;
    }

    size_type capacity() const
    {
        return (end - first)/sizeof(value_type);
    }

    size_type size() const 
    {
        return (last - first)/sizeof(value_type);
    }

    ~MyVector()
    {
        deleteVector();        
    }
};