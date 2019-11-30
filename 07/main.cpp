#include <iostream>
#include <memory>
#include "MyVector.hpp"
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
   
    cout << v << endl;

    MyVector<int> v2;
    v2 = v;
    v2.pop_back();
    cout << v2 << endl;
}
