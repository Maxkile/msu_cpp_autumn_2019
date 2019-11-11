#include <sstream>
#include <cassert>
#include <cstring>
#include "Serializer.hpp"
#include "Deserializer.hpp"

int main(int argc, char const *argv[])
{
    constexpr char Separator = ' ';
    Data y {0,"false",0};

    if (argc < 2)
    {
        std::cout << "Too few args! Possible commands: -all,-test,-ser,-des." << std::endl;
        return 1;
    }
    else if (!strcmp(argv[1],"-test"))
    {
        Data x {2,"123",32};
        std::stringstream str;
        Serializer serializer(str);
        serializer.save(x);
        Deserializer deserializer(str);
        const Data::Error err = deserializer.load(y);
    

        assert(err == Data::Error::NoError);
        assert(x.a == y.a);
        assert(x.b == y.b);
        assert(x.c == y.c);
    }
    else if (!strcmp(argv[1],"-all"))
    {
        if (argc < 5)
        {
            std::cout << "Too few args! Possible commands: -all,-test,-ser,-des." << std::endl;
            return 1;
        }
        else
        {
            Data x {static_cast<uint64_t>(atoi(argv[2])),static_cast<bool>(atoi(argv[3])),static_cast<uint64_t>(atoi(argv[4]))};
            std::stringstream str;
            Serializer serializer(str);
            serializer.save(x);
            Deserializer deserializer(str);
            const Data::Error err = deserializer.load(y);
            
            assert(err == Data::Error::NoError);
            assert(x.a == y.a);
            assert(x.b == y.b);
            assert(x.c == y.c);
        }
    }
    else if (!strcmp(argv[1],"-ser"))
    {
        if (argc < 5)
        {
            std::cout << "Too few args! Possible commands: -all,-test,-ser,-des." << std::endl;
            return 1;
        }
        else
        {
            Data x {static_cast<uint64_t>(atoi(argv[2])),static_cast<bool>(atoi(argv[3])),static_cast<uint64_t>(atoi(argv[4]))};
            std::stringstream str;
            Serializer serializer(str);
            const Data::Error err = serializer.save(x);

            assert(err == Data::Error::NoError);

            std::cout << str.str();
        }

    }
    else if (!strcmp(argv[1],"-des"))
    {
        if (argc < 5)
        {
            std::cout << "Too few args! Possible commands: -all,-test,-ser,-des." << std::endl;
            return 1;
        }
        else
        {
            Data y {0,"false",0};
            std::stringstream str;
            str << argv[2] << Separator << argv[3] << Separator << argv[4];
            Deserializer deserializer(str);
            const Data::Error err = deserializer.load(y);

            assert(err == Data::Error::NoError);

            std::cout << y.a << " " << y.b << " " << y.c;    
        }

    }

    return 0;    
}
