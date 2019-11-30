#include <iterator>

#pragma once 

template<typename Iter>
class MyIterator : std::iterator<std::forward_iterator_tag, Iter>//type of iterator and type of returned expression
{
    Iter current_;
    Iter end_;

public:
    MyIterator(Iter&& begin,Iter&& end): current_(std::move(begin)), end_(std::move(end)){}

    MyIterator(const Iter& begin,const Iter& end): current_(begin), end_(end){}

    bool operator==(const MyIterator& another) const
    {
        return current_ == another.current_;
    }

    bool operator!=(const MyIterator& another) const
    {
        return !(*this == another);
    }
    

    int operator*() const
    {
        return *current_;
    }

    void operator++()
    {
        if (current_ != end_)
        {
            ++current_;
        }
    }

};