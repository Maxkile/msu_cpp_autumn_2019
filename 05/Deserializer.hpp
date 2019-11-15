#include "Data.hpp"
#include <iostream>
#include <string>

#pragma once

class Deserializer
{
    std::istream &in_;

public:

    explicit Deserializer(std::istream& in) : in_(in){};

    
    template <class T>
    Data::Error load(T& object)
    {
        T& modified = object;
        const Data::Error err =  modified.deserialize(*this);
        if (err == Data::Error::NoError)
        {
            object = std::move(modified);
        }
        return err;
    }

    template <class ...ArgsT>
    Data::Error operator()(ArgsT&& ...args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:

    template <class T>
    Data::Error checkRead(T& arg)
    {  
        std::string text;
        in_ >> text;
        if constexpr (std::is_same<bool,T>::value)
        {           
            if (text == "true")
            {
                arg = true;
            }
            else if (text == "false")
            {
                arg = false;
            }
            else return Data::Error::CorruptedArchive;
        }
        else if (text[0] == '-')//negative,but we have unsigned
        {
            return Data::Error::CorruptedArchive;
        }
        else
        {
            try
            {
                arg = static_cast<uint64_t>(std::stoi(text));
            }
            catch (std::out_of_range& oor)
            {
                return Data::Error::CorruptedArchive;
            }
            catch (std::exception& exp)
            {
                std::cerr << exp.what() << std::endl;//log
                return Data::Error::CorruptedArchive;
            }

        }
        return Data::Error::NoError;
    }

    template <class T,class... Args>
    Data::Error process(T& first,Args&&... args)
    {
        if (checkRead(first) == Data::Error::CorruptedArchive) return Data::Error::CorruptedArchive;
        return process(std::forward<Args>(args)...);//forwards rvalues rvalues
    }

    template <class T>
    Data::Error process(T& last)
    {
        return checkRead(last);
    }
};