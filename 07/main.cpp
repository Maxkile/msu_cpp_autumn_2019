#include <iostream>
#include <memory>
#include "MyVector.hpp"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    MyVector<int> v; 
    v.push_back(2);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);
    v.push_back(123);
    v.push_back(2);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);
    v.push_back(123);
    v.push_back(2);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);
    v.push_back(123);
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);
    v.push_back(123);
    v.push_back(3);
    v.push_back(4);
    v.push_back(2);
    v.push_back(123);
   
    cout << v[10] << endl;
    MyVector<int> v2;
    v2 = v;
    v2.pop_back();
    cout << v2.capacity() << endl;
    v2.shrink_to_fit();
    cout << v2.capacity() << endl;
    
    v2.resize(1,-1);
    cout << v2.capacity() << v2.size() << endl;
  

    MyVector<string> v3;
    v3.push_back("qwer");
    v3.push_back("q");
    v3.push_back("wqeqwe");
    v3.push_back("qweqweqwwee");
    for(MyVector<string>::iterator it = v3.begin(); it != v3.end() + 1;++it)
    {
        cout  << *it << endl;
    }

    MyVector<string>::iterator iter = v3.end();
    std::cout << *iter << std::endl;
}
