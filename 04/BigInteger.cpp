#include "BigInteger.hpp"

using namespace std;

int BigInteger::getDigitsNumber(const int num) const
{
    if ( num < 10 )
        return 1;
    else if ( num < 100 )
        return 2;
    else if ( num < 1000)
        return 3;
    else if ( num < 10000)
        return 4;
    else if (num < 100000)
        return 5;
    else if (num < 1000000)
        return 6;
    else if (num < 10000000)
        return 7;
    else if (num < 100000000)
        return 8;
    else if (num < 1000000000)
        return 9;
    else return 10;
}

void BigInteger::deleteHighZeroes()
{
    int newLength = length;
    for(int i = length - 1;i>=0;--i)
    {
        if (number[i] == '0') newLength--;
        else break;
    }
    if (newLength == 0)//number is  zero
    {
        isNeg = false;//for correct output
        newLength++;
    } 
    length = newLength;
}


void BigInteger::strrev(char* str)
{
    char* temp = (char*) malloc(sizeof(char) * (length + 1));
    memcpy(temp,str,(length + 1));
    temp[length] = '\0';
    for (int i=0; i< length;i++) 
    {
        str[i] = temp[length-i-1];
    }
    
    free(temp);

}

int BigInteger::numReverse(const int source) const
{
    int num,res;
    res = 0;
    num = source;
    while(num)
    {
        res = res * 10 + num % 10;
        num /= 10;
    }
    return res;
}

bool BigInteger::absolutelyLesser(const BigInteger& n)
{
    if ((isNeg) && (!n.isNeg))
    {
        return -(*this) < n;
    }
    else if (!(isNeg) && (n.isNeg))
    {
        return (*this) < -n;
    }
    else if ((isNeg) && (n.isNeg))
    {
        return -(*this) < -n;
    }
    else
    {
        return (*this) < n;
    }
}

BigInteger::BigInteger()
{
    number = (char*) malloc(sizeof(char) * 2);
    number[0] = '0';
    number[1] = '\0';
    length = 1;
    isNeg = false;
}

BigInteger::BigInteger(const int source)
{
    int digN = getDigitsNumber(abs(source));
    isNeg = source < 0;
    length = digN;
    number = (char*) malloc(sizeof(char) * (length + 1));
    sprintf(number,"%d",abs(source));
    strrev(number);
    number[length] = '\0';
}

BigInteger::BigInteger(const BigInteger& source)
{
    number = (char*) malloc(sizeof(char) * (source.length + 1));
    isNeg = source.isNeg;
    length = source.length;
    memcpy(number,source.number,length + 1);
}

BigInteger& BigInteger::operator=(const BigInteger& source)
{
    free(number);
    length = source.length;
    number = (char*) malloc(sizeof(char) * (length + 1));
    isNeg = source.isNeg;
    memcpy(number,source.number,length + 1);
    return *this;
}

bool BigInteger::operator==(const BigInteger& source) const
{
    if (length != source.length) return false;
    else
    {
        for(int i = 0;i<length;++i)
        {
            if (number[i] != source.number[i]) return false;
        }
    }
    return true;
}

bool BigInteger::operator!=(const BigInteger& source) const
{
    return !(*this == source);
}


bool BigInteger::operator>(const BigInteger& source) const
{
    if (source.isNeg && !isNeg) return true;
    else if (!source.isNeg && isNeg) return false;
    else if (source.isNeg && isNeg)
    {
        if (length > source.length) return false;
        else if (length < source.length) return true;
        else
        {
            for(int i = length - 1;i >=0;--i)
            {
                if (number[i] > source.number[i]) return false;
                else if (number[i] < source.number[i]) return true;
            }
        }
    }
    else//both positive
    {
        if (length > source.length) return true;
        else if (length < source.length) return false;
        else
        {
            for(int i = length - 1;i >=0;--i)
            {
                if (number[i] > source.number[i]) return true;
                else if (number[i] < source.number[i]) return false;
            }
        }
    }
    return false;
}

bool BigInteger::operator<(const BigInteger& source) const
{
    if (source.isNeg && !isNeg) return false;
    else if (!source.isNeg && isNeg) return true;
    else if (source.isNeg && isNeg)
    {
        if (length > source.length) return true;
        else if (length < source.length) return false;
        else
        {
            for(int i = length - 1;i >=0;--i)
            {
                if (number[i] > source.number[i]) return true;
                else if (number[i] < source.number[i]) return false;
            }
        }
    }
    else//both positive
    {
        if (length > source.length) return false;
        else if (length < source.length) return true;
        else
        {
            for(int i = length - 1;i >=0;--i)
            {
                if (number[i] > source.number[i]) return false;
                else if (number[i] < source.number[i]) return true;
            }
        }
    }
    return false;
}

bool BigInteger::operator>=(const BigInteger& source) const
{
    return ((*this == source) || (*this > source));
}

bool BigInteger::operator<=(const BigInteger& source) const
{
    return ((*this == source) || (*this < source));
}



BigInteger& BigInteger::operator+=(const BigInteger& source)
{
    BigInteger extra;
    if (absolutelyLesser(source))
    {
        extra = *this;
        *this = source;
    }
    else
    {
        extra = source;
    }


    if (!isNeg && !extra.isNeg)//both positive
    {
        sum(*this,extra);
    }
    else if (isNeg && extra.isNeg)
    {
        extra.isNeg = false;
        isNeg = false;
        sum(*this,extra);
        isNeg = true;
    }
    else//length of *this > source.length
    {
        diff(*this,extra);
    }
    
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& source)
{
    BigInteger res(*this);
    return res+=source;
}

BigInteger& BigInteger::operator-=(const BigInteger& source)
{
    BigInteger extra;
    bool signChanged = false;
    if (absolutelyLesser(source))
    {
        extra = *this;
        *this = source;
        signChanged = true;//need to store because difference is not symmetric
    }
    else
    {
        extra = source;
    }

    if (!isNeg && extra.isNeg)
    {
        extra.isNeg = false;
        sum(*this,extra);
    }
    else if (isNeg && !extra.isNeg)
    {
        extra.isNeg = false;
        isNeg = false;
        sum(*this,extra);
        isNeg = true;
    }
    else//length of *this > source.length
    {

        diff(*this,extra);
    }
    
    if (signChanged) isNeg = !isNeg;

    return *this;
}


BigInteger BigInteger::operator-(const BigInteger& source)
{
    BigInteger res(*this);
    return res-=source;
}





bool BigInteger::operator==(const int source)
{
    BigInteger fromInt(source);
    return (*this == fromInt);
}

bool BigInteger::operator!=(const int source)
{
    BigInteger fromInt(source);
    return (*this != fromInt);
}

bool BigInteger::operator<(const int source)
{
    BigInteger fromInt(source);
    return (*this < fromInt);
}

bool BigInteger::operator>(const int source)
{
    BigInteger fromInt(source);
    BigInteger res(*this);
    return (res > fromInt);
}

bool BigInteger::operator<=(const int source)
{
    BigInteger fromInt(source);
    return (*this <= fromInt);
}

bool BigInteger::operator>=(const int source)
{
    BigInteger fromInt(source);
    return (*this >= fromInt);
}



BigInteger& BigInteger::operator+=(const int source)
{
    BigInteger fromInt(source);
    return (*this += fromInt);
}

BigInteger BigInteger::operator+(const int source)
{
    BigInteger fromInt(source);
    BigInteger res(*this);
    return (res = res + fromInt);
}

BigInteger BigInteger::operator-=(const int source)
{
    BigInteger fromInt(source);
    return (*this -= fromInt);
}

BigInteger BigInteger::operator-(const int source)
{
    BigInteger fromInt(source);
    BigInteger res(*this);
    return (res = res - fromInt);
}


void BigInteger::sum(BigInteger& term1,const BigInteger& term2)//we want the biggest number of two to be *this
{

    int pos;
    int transfer = 0;

    for(pos = 0; pos < term2.length;++pos)
    {
        int res = (term1.number[pos] - '0') + (term2.number[pos] - '0') + transfer;
        transfer = 0;
        if (res >= 10)
        {
            transfer++;
            res -= 10;
        }
        term1.number[pos] = res + '0';
    }
    while((transfer != 0) && (pos < term1.length))
    {
        int res = (term1.number[pos] - '0') + transfer;
        transfer = 0;
        if (res >= 10)
        {
            transfer++;
            res -= 10;
        }
        term1.number[pos] = res + '0';
        pos++;
    }
    if (transfer != 0)
    {
        term1.number = (char*) realloc(term1.number,sizeof(char) * (term1.length + 1));
        length++;
        term1.number[term1.length - 1] = transfer + '0';
    }
}

void BigInteger::diff(BigInteger& minuend,const BigInteger& subtr)
{
    int pos;
    int transfer = 0;

    for(pos = 0;pos < subtr.length;++pos)
    {
        int res = (minuend.number[pos] - '0') - (subtr.number[pos] - '0') - transfer;
        transfer = 0;
        if (res < 0)
        {
            transfer++;
            res += 10;
        }
        minuend.number[pos] = res + '0';
    }
    while((transfer != 0) && (pos < minuend.length))
    {
        int res = (minuend.number[pos] - '0') - transfer;
        transfer = 0;
        if (res < 0)
        {
            transfer++;
            res += 10;
        }
        minuend.number[pos] = res + '0';
        pos++;
    }
    minuend.deleteHighZeroes();

}


BigInteger BigInteger::operator-() const
{
    BigInteger res(*this);
    res.isNeg = !res.isNeg;
    return res;
}

int BigInteger::getLength() const
{
    return length;
}


BigInteger::~BigInteger()
{
    free(number);
}

ostream& operator<<(ostream& out,BigInteger bigInt)
{
    if (bigInt.isNeg) out << '-';
    
    for(int i = (bigInt.length - 1);i >=0;--i)
    {
        out << bigInt.number[i];
    }

    return out;
}