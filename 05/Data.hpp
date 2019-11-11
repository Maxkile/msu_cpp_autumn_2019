#include <cstdint>

#pragma once

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

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

