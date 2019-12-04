#include "MyIterator.hpp"
#include "MyAllocator.hpp"
#pragma once

template <typename T,typename Allocator = MyAllocator<T>>
class MyVector
{
public:

    using value_type = T;
    using pointer = value_type*;
    using vector = MyVector<T>;
    using iterator = MyIterator<T>;
    using allocator_type = MyAllocator<T>;
    using size_type = size_t;

explicit MyVector(size_type initialLength = 0);

    MyVector(const vector&);

    MyVector(const vector&,const allocator_type&);
    //not taking allocator
    MyVector& operator=(const vector&);

    void reserve(size_type);


    void resize(size_type);

    void resize(size_type,const value_type&);

    void clear();

    void push_back(const value_type&);

    void push_back(value_type&&);

    void pop_back();

    bool empty();

    iterator begin();

    iterator end();

    iterator rbegin();

    iterator rend();

    allocator_type get_allocator() const;

    value_type& operator[](size_type);

    const value_type operator[](size_type) const;

    void shrink_to_fit();

    size_type capacity() const;

    size_type size() const ;

    ~MyVector();

private:
    pointer first_;
    pointer last_;//for size
    pointer end_;//for capacity

    Allocator allocator_;
    
    //Does not checking out of bounds
    void copy(pointer dest,pointer src,size_type size);

    //Does not checking out of bounds
    void fillwith_(pointer src,size_type from,const value_type& value);

    void reallocate_(size_type newCapacity);

    void deleteVector_();
};



template<typename T,typename Allocator>
MyVector<T,Allocator>::MyVector(size_type initialLength)
{
    first_ = allocator_.allocate(initialLength);
    last_ = first_;
    
    end_ = first_ +  initialLength;
}

template<typename T,typename Allocator>
MyVector<T,Allocator>::MyVector(const vector& other)
{
    first_ = allocator_.allocate(other.capacity());
    last_ = first_ + other.size();
    end_ = first_ + other.capacity();

    copy(first_,other.first_,other.size());
}

template<typename T,typename Allocator>
MyVector<T,Allocator>::MyVector(const vector& other,const allocator_type& allocator)
{
    allocator_ = allocator;
    first_ = allocator_.allocate(other.capacity());
    last_ = first_ +  other.size();
    end_ = first_ +  other.capacity();

    copy(first_,other.first_,other.size());
}

template<typename T,typename Allocator>
MyVector<T,Allocator>& MyVector<T,Allocator>::operator=(const vector& other)
{
    deleteVector_();
    allocator_ = other.get_allocator(); 
    first_ = allocator_.allocate(other.capacity());
    last_ = first_ + other.size();
    end_ = first_ + other.capacity();

    copy(first_,other.first_,other.size());

    return *this;
}


template<typename T,typename Allocator>
void MyVector<T,Allocator>::reserve(size_type newCapacity)
{
    if (newCapacity > capacity())
    {   
        reallocate_(newCapacity);
    }
}

template<typename T,typename Allocator>
void MyVector<T,Allocator>::resize(size_type newSize)
{
    if (size() < newSize)
    {
        size_type oldSize = size();
        reallocate_(newSize);
        last_ = first_ + newSize;
        fillwith_(first_,oldSize,value_type());//default constructor
    }
    else if (size() > newSize)
    {
        last_ = first_ + newSize;
        reallocate_(newSize);
    }
}

template<typename T,typename Allocator>
void MyVector<T,Allocator>::resize(size_type newSize,const value_type& value)
{
    if (size() < newSize)
    {
        size_type oldSize = size();
        reallocate_(newSize);
        last_ = first_ + newSize;
        fillwith_(first_,oldSize,value);
    }
    else if (size() > newSize)
    {
        last_ = first_ +  newSize;
        reallocate_(newSize);
    }
}


template<typename T,typename Allocator>
void MyVector<T,Allocator>::clear()
{
    for(size_type i = 0;i < size();++i)
    {
        allocator_.destroy(first_ + i);
    }
    last_ = first_;
}

template<typename T,typename Allocator>
void MyVector<T,Allocator>::push_back(const value_type& elem)
{   
    if (last_ == end_)//need to reallocate
    {
        size_type capacity_ = capacity();
        capacity_ = capacity_ * 2 + 1;//reallocation is slow, so we reallocate extra
        reallocate_(capacity_);
    }
    allocator_.construct(first_ + size(),elem);
    last_++;
}

template<typename T,typename Allocator>
void MyVector<T,Allocator>::push_back(value_type&& elem)
{   
    if (last_ == end_)//need to reallocate
    {
        size_type capacity_ = capacity();
        capacity_ = capacity_ * 2 + 1;//reallocation is slow, so we reallocate extra
        reallocate_(capacity_);
    }
    allocator_.construct(first_ + size(),std::forward<value_type>(elem));
    last_++;        
}

template<typename T,typename Allocator>
void MyVector<T,Allocator>::pop_back()
{   
    if (size() > 0) last_--;
}

template<typename T,typename Allocator>
bool MyVector<T,Allocator>::empty()
{
    return (size() == 0);
}

template<typename T,typename Allocator>
typename MyVector<T,Allocator>::iterator MyVector<T,Allocator>::begin()
{
    return iterator(first_ ,first_);
}

template<typename T,typename Allocator>
typename MyVector<T,Allocator>::iterator MyVector<T,Allocator>::end()
{
    return iterator(last_ - 1,last_ - 1);
}

template<typename T,typename Allocator>
typename MyVector<T,Allocator>::iterator MyVector<T,Allocator>::rbegin()
{
    return iterator(last_ - 1,last_ - 1);
}

template<typename T,typename Allocator>
typename MyVector<T,Allocator>::iterator MyVector<T,Allocator>::rend()
{
    return iterator(first_,first_ );
}

template<typename T,typename Allocator>
typename MyVector<T,Allocator>::allocator_type MyVector<T,Allocator>::get_allocator() const
{
    return allocator_;
}

template<typename T,typename Allocator>
typename MyVector<T,Allocator>::value_type& MyVector<T,Allocator>::operator[](size_type ind)
{
    return *(first_ + ind);
}

template<typename T,typename Allocator>
const typename MyVector<T,Allocator>::value_type MyVector<T,Allocator>::operator[](size_type ind)  const
{
    return *(first_ + ind);
}

template<typename T,typename Allocator>
void MyVector<T,Allocator>::shrink_to_fit()
{
    reallocate_(size());
}

template<typename T,typename Allocator>
typename MyVector<T,Allocator>::size_type MyVector<T,Allocator>::capacity() const
{
    return (end_ - first_);
}

template<typename T,typename Allocator>
typename MyVector<T,Allocator>::size_type MyVector<T,Allocator>::size() const
{
    return (last_ - first_);
}

template<typename T,typename Allocator>
MyVector<T,Allocator>::~MyVector()
{
    deleteVector_();        
}

template<typename T,typename Allocator>
void MyVector<T,Allocator>::copy(pointer dest,pointer src,size_type size)
{
    for(size_type i = 0;i < size;++i)
    {
        allocator_.construct(dest + i,src[i]);
    }
}

template<typename T,typename Allocator>
void MyVector<T,Allocator>::fillwith_(pointer src,size_type from,const value_type& value)
{
    for(size_type i = from;i < size();++i)
    {
        allocator_.construct(src + i,value);
    }
}
template<typename T,typename Allocator>
void MyVector<T,Allocator>::reallocate_(size_type newCapacity)
{
    size_type oldSize = size();

    value_type buffer[oldSize];
    copy(buffer,first_,oldSize);
    
    deleteVector_();//delete oldMemory
    first_ = allocator_.allocate(newCapacity);
    last_ = first_ +  oldSize;
    end_ = first_ +  newCapacity;

    copy(first_,buffer,oldSize);
}
template<typename T,typename Allocator>
void MyVector<T,Allocator>::deleteVector_()
{   
    for(size_type i = 0;i < size();++i)
    {
        allocator_.destroy(first_ + i);
    }
    allocator_.deallocate(first_);
    last_ = nullptr;
    end_ = nullptr;
}