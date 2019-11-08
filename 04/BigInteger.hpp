#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class BigInteger
{

    char* number;//on 'length' position is '\0'
    int length;//'real' length
    bool isNeg;

    int getDigitsNumber(const int num) const;

    void deleteHighZeroes();

    void strrev(char* str);

    bool absolutelyLesser(const BigInteger& n);

public:

    BigInteger();

    BigInteger(const int source);

    BigInteger(const BigInteger& source);

    BigInteger& operator=(const BigInteger& source);

    bool operator==(const BigInteger& source) const;

    bool operator!=(const BigInteger& source) const;


    bool operator>(const BigInteger& source) const;

    bool operator<(const BigInteger& source) const;

    bool operator>=(const BigInteger& source) const;

    bool operator<=(const BigInteger& source) const;
    
    
    BigInteger& operator+=(const BigInteger& source);

    BigInteger operator+(const BigInteger& source);

    BigInteger& operator-=(const BigInteger& source);


    BigInteger operator-(const BigInteger& source);




    
    bool operator==(const int source);

    bool operator!=(const int source);

    bool operator<(const int source);

    bool operator>(const int source);

    bool operator<=(const int source);

    bool operator>=(const int source);



    BigInteger& operator+=(const int source);

    BigInteger operator+(const int source);

    BigInteger operator-=(const int source);

    BigInteger operator-(const int source);

    
    void sum(BigInteger& term1,const BigInteger& term2);

    void diff(BigInteger& minuend,const BigInteger& subtr);

    friend ostream& operator<<(ostream& out,BigInteger bigInt);

    BigInteger operator-() const;

    int getLength() const;

    ~BigInteger();

};