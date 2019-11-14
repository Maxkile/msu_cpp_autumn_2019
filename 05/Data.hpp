#include <cstdint>
#include <iostream>

#pragma once

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;
    
    Data& operator=(Data&& moved)//moving operator
    {
        std::cout << "HERE" << std::endl;
        if (this == &moved)
            return *this;
        a = moved.a;
        b = moved.b;
        c = moved.c;
        moved.a = 0;
        moved.b = 0;
        moved.c = 0;
        return *this;
    }

    enum class Error
    {
        NoError,
        CorruptedArchive
    };

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

