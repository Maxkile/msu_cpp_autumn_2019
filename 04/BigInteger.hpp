#include <iostream>
#include <cstdlib>
#include <cstring>

#pragma once

class BigInteger
{

    char* number;//on 'length' position is '\0'

    int length;//'real' length

    bool isNeg;

    int getDigitsNumber(const int num) const;

    void deleteHighZeroes();

    void strrev(char* str);

    bool absolutelyLesser(const BigInteger& n);

    void sum(BigInteger& term1,const BigInteger& term2);

    void diff(BigInteger& minuend,const BigInteger& subtr);

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


    BigInteger operator-() const;

    
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


    friend std::ostream& operator<<(std::ostream& out,const BigInteger bigInt);

    int getLength() const;

    ~BigInteger();

};