#include <iostream>
#include <sstream>
#include <cassert>
#include "format.hpp"

int main(int argc, char const *argv[])
{
    auto text = format("123132");
    assert(text == "one+one = 2");
    text = format("{0} {1} {2} {3} {4} {5} {6} {7}", 'I', "was","watching","my","mother","washing","the","dishes");
    assert(text == "I was watching my mother washing the dishes");
    text = format("{1} {2} {0}", "Uns", "Gott","Mit");
    assert(text == "Gott Mit Uns");
    text = format("{2} <= {1} {0} {3}", "is","4321",123, true);
    assert(text == "123 <= 4321 is 1");

    std::cout << "Assertion success." << std::endl;
    return 0;
}
