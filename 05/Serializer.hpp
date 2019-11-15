#include "Data.hpp"
#include <iostream>
#include <vector>

#pragma once

class Serializer
{
    std::ostream &out_;
    static constexpr char Separator = ' ';

public:

    explicit Serializer(std::ostream& out) : out_(out){};

    template <class T>
    Data::Error save(T& object)
    {
        return object.serialize(*this);//for data type objects
    }

    template <class ...ArgsT>
    Data::Error operator()(ArgsT&& ...args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:

    template <class T>
    Data::Error checkWrite(T& arg)
    {
        if constexpr (!std::is_same<bool,T>::value)
        {
            if (!std::is_same<uint64_t,T>::value) return Data::Error::CorruptedArchive;
            else
            {
                out_ << arg << Separator;
                return Data::Error::NoError;
            }
        }
        else
        {
            out_ << std::boolalpha;
            out_ << arg << Separator;
            return Data::Error::NoError;
        }
    }

    template <class T,class... Args>
    Data::Error process(T& first,Args&&... args)
    {
        if (checkWrite(first) == Data::Error::CorruptedArchive) return Data::Error::CorruptedArchive;
        return process(std::forward<Args>(args)...);//forwards rvalues rvalues
    }

    template <class T>
    Data::Error process(T& last)
    {
        return checkWrite(last);
    }
};