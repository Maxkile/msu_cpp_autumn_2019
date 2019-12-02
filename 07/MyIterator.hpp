#include <iterator>

#pragma once 

template<typename Iter>
class MyIterator : std::iterator<std::random_access_iterator_tag, Iter>//type of iterator and type of returned expression
{
public:

    using value_type = Iter;
    using pointer = value_type*;
    using iterator = MyIterator<value_type>;
    using index_type = int;

    MyIterator(pointer begin, pointer from);

    MyIterator(const iterator& another);

    MyIterator& operator=(const iterator& another);

    bool operator==(const iterator& another) const;

    bool operator!=(const iterator& another) const;

    bool operator>(const iterator& another) const;

    bool operator>=(const iterator& another) const;

    bool operator<(const iterator& another) const;

    bool operator<=(const iterator& another) const;

    value_type& operator[](index_type ind);

    const value_type& operator[](index_type ind) const;

    value_type& operator*();

    const value_type operator*() const;

    iterator operator+(index_type ind);

    iterator& operator+=(index_type ind);

    iterator operator-(index_type ind);

    iterator& operator-=(index_type ind);

    iterator& operator++();

    void operator++(int unused);

    iterator& operator--();

    void operator--(int unused);

private:
    pointer begin_;
    pointer current_;
};


template<typename Iter>
MyIterator<Iter>::MyIterator(pointer begin, pointer from): begin_(begin),current_(from){}

template<typename Iter>
MyIterator<Iter>::MyIterator(const iterator& another): begin_(another.begin_),current_(another.current_){}

template<typename Iter>
MyIterator<Iter>& MyIterator<Iter>::operator=(const iterator& another)
{
    begin_ = another.begin_;
    current_ = another.current_;
    return *this;
}

template<typename Iter>
bool MyIterator<Iter>::operator==(const iterator& another) const
{
    return current_ == another.current_;
}

template<typename Iter>
bool MyIterator<Iter>::operator!=(const iterator& another) const
{
    return !(*this == another);
}

template<typename Iter>
bool MyIterator<Iter>::operator>(const iterator& another) const
{
    return current_ > another.current_;
}

template<typename Iter>
bool MyIterator<Iter>::operator>=(const iterator& another) const
{
    return current_ >= another.current_;
}

template<typename Iter>
bool MyIterator<Iter>::operator<(const iterator& another) const
{
    return current_ < another.current_;
}

template<typename Iter>
bool MyIterator<Iter>::operator<=(const iterator& another) const
{
    return current_ <= another.current_;
}


template<typename Iter>
typename MyIterator<Iter>::value_type& MyIterator<Iter>::operator[](index_type ind)
{
    return *(begin_ + ind);
}

template<typename Iter>
const typename MyIterator<Iter>::value_type& MyIterator<Iter>::operator[](index_type ind) const
{
    return *(begin_ + ind);
}

template<typename Iter>
typename MyIterator<Iter>::value_type& MyIterator<Iter>::operator*()
{
    return *current_;
}

template<typename Iter>
const typename MyIterator<Iter>::value_type MyIterator<Iter>::operator*() const
{
    return *current_;
}

template<typename Iter>
typename MyIterator<Iter>::iterator MyIterator<Iter>::operator+(index_type ind)
{
    return iterator(begin_,current_ + ind);
}

template<typename Iter>
typename MyIterator<Iter>::iterator& MyIterator<Iter>::operator+=(index_type ind)
{
    current_ += ind;
    return *(this);
}

template<typename Iter>
typename MyIterator<Iter>::iterator MyIterator<Iter>::operator-(index_type ind)
{
    return iterator(begin_,current_ - ind);
}

template<typename Iter>
typename MyIterator<Iter>::iterator& MyIterator<Iter>::operator-=(index_type ind)
{
    current_ -= ind;
    return *(this);
}

template<typename Iter>
typename MyIterator<Iter>::iterator& MyIterator<Iter>::operator++()
{
    ++current_;
    return *this;
}

template<typename Iter>
void MyIterator<Iter>::operator++(int unused)
{
    current_++;
}

template<typename Iter>
typename MyIterator<Iter>::iterator& MyIterator<Iter>::operator--()
{
    --current_;
    return *this;
}

template<typename Iter>
void MyIterator<Iter>::operator--(int unused)
{
    current_--;
}