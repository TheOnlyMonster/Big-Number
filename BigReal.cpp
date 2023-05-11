#include "header.h"
BigReal::BigReal(string realNumber){
    this->fractionIndex = realNumber.length();
    for (int i = 0; i < realNumber.length(); i++)
    {
        if (realNumber[i] == '.')
        {
            this->fractionIndex = i;
            break;
        }
    }
    realNumber.erase(this->fractionIndex, 1);
    numBeforePoint = new BigDecimalInt(realNumber.substr(0,this->fractionIndex));
    reverse(realNumber.begin() + this->fractionIndex, realNumber.end());
    BigDecimalInt *numAfterPoint_Temp = new BigDecimalInt(realNumber.substr(this->fractionIndex));
    reverse(numAfterPoint_Temp->decStr.begin(), numAfterPoint_Temp->decStr.end());
    numAfterPoint = numAfterPoint_Temp;
    this->fractionIndex = numBeforePoint->decStr.length() - 1;
    this->decStr = numBeforePoint->decStr + '.' + numAfterPoint->decStr;
    this->sign = this->numBeforePoint->sign;
}
BigReal& BigReal::operator+(BigNumber& other){
    BigReal& otherBigReal = dynamic_cast<BigReal&>(other);
    int biggerA = max(this->numAfterPoint->decStr.length(), otherBigReal.numAfterPoint->decStr.length());

    if (this->numBeforePoint->sign == '+' && otherBigReal.numBeforePoint->sign == '-')
    {
        otherBigReal.numBeforePoint->sign = '+';
        return *this - otherBigReal;
    }
    else if (this->numBeforePoint->sign == '-' && otherBigReal.numBeforePoint->sign == '+')
    {
        this->numBeforePoint->sign = '+';
        return otherBigReal - *this;
    }
    if (this->fractionIndex < otherBigReal.fractionIndex)
    {
        swap(*this, otherBigReal);
    }
    padZerosBeforeDecimal(this->numBeforePoint->decStr.length() - otherBigReal.numBeforePoint->decStr.length(), otherBigReal.numBeforePoint);
    padZerosAfterDecimal(this->numAfterPoint->decStr.length() - otherBigReal.numAfterPoint->decStr.length(), otherBigReal);
    string num1 = (this->numBeforePoint->sign + this->numBeforePoint->decStr + this->numAfterPoint->decStr);
    string num2 = (otherBigReal.numBeforePoint->sign + otherBigReal.numBeforePoint->decStr + otherBigReal.numAfterPoint->decStr);
    BigNumber *myNum = new BigDecimalInt(num1);
    dynamic_cast<BigDecimalInt*>(myNum);
    BigDecimalInt &Res = BigDecimalInt(num2) + *myNum;
    Res.decStr.insert(Res.decStr.length() - biggerA, 1, '.');
    BigReal* result = new BigReal(Res.sign + Res.decStr);
    return *result;
}
BigReal& BigReal::operator-(BigNumber& other){
    BigReal& otherBigReal = dynamic_cast<BigReal&>(other);
    int biggerA = max(this->numAfterPoint->decStr.length(), otherBigReal.numAfterPoint->decStr.length());
    bool negative_sign = false, isSwapped = false;
    if (this->fractionIndex < otherBigReal.fractionIndex)
    {
        if (otherBigReal.numBeforePoint->sign == '+')
        {
            negative_sign = true;
        }
        isSwapped = true;
        swap(*this, otherBigReal);
    }
    padZerosBeforeDecimal(this->numBeforePoint->decStr.length() - otherBigReal.numBeforePoint->decStr.length(), otherBigReal.numBeforePoint);
    padZerosAfterDecimal(this->numAfterPoint->decStr.length() - otherBigReal.numAfterPoint->decStr.length(), otherBigReal);
    string num1 = (this->numBeforePoint->sign + this->numBeforePoint->decStr + this->numAfterPoint->decStr);
    string num2 = (otherBigReal.numBeforePoint->sign + otherBigReal.numBeforePoint->decStr + otherBigReal.numAfterPoint->decStr);
    BigDecimalInt *Res;
    BigNumber *myNum;
    if(isSwapped){
        myNum = new BigDecimalInt(num1);
        dynamic_cast<BigDecimalInt*>(myNum);
        Res = new BigDecimalInt(BigDecimalInt(num2) - *myNum);
    }
    else{
        myNum = new BigDecimalInt(num2);
        dynamic_cast<BigDecimalInt*>(myNum);
        Res = new BigDecimalInt(BigDecimalInt(num1) - *myNum);
    }
    int len = Res->decStr.length();
    if ((len - biggerA) < 0){
        padZerosBeforeDecimal(biggerA - len, Res);
        Res->decStr.insert(0, 1, '.');
    }
    else{
        Res->decStr.insert(len - biggerA, 1, '.');
    }
    if(negative_sign){
        Res->sign = '-';
    }
    BigReal* result = new BigReal(Res->sign + Res->decStr);
    return *result;
}
void BigReal::padZerosAfterDecimal(int numOfZeros, BigReal& other){
    string temp;
    for (int i = 0; i < abs(numOfZeros); i++)
    {
        temp += '0';
    }
    if (this->numAfterPoint->decStr.length() > other.numAfterPoint->decStr.length())
    {
        other.numAfterPoint->decStr += temp;
    }
    else if (this->numAfterPoint->decStr.length() < other.numAfterPoint->decStr.length())
    {
        this->numAfterPoint->decStr += temp;
    }
}
void BigReal::padZerosBeforeDecimal(int numOfZeros, BigDecimalInt *other){
    string temp;
    for (int i = 0; i < numOfZeros; i++)
    {
        temp += '0';
    }
    other->decStr = temp + other->decStr;
}
bool BigReal::operator==(BigNumber& other){
    BigReal& otherBigReal = dynamic_cast<BigReal&>(other);
    padZerosAfterDecimal(this->numAfterPoint->decStr.length() - otherBigReal.numAfterPoint->decStr.length(), otherBigReal);
    string num1 = (this->numBeforePoint->sign + this->numBeforePoint->decStr + this->numAfterPoint->decStr);
    string num2 = (otherBigReal.numBeforePoint->sign + otherBigReal.numBeforePoint->decStr + otherBigReal.numAfterPoint->decStr);
    BigNumber *myNum = new BigDecimalInt(num2);
    dynamic_cast<BigDecimalInt*>(myNum);
    bool res = (BigDecimalInt(num1) == *myNum);
    return res;
}
bool BigReal::operator>(BigNumber& other){
    BigReal& otherBigReal = dynamic_cast<BigReal&>(other);
    padZerosAfterDecimal(this->numAfterPoint->decStr.length() - otherBigReal.numAfterPoint->decStr.length(), otherBigReal);
    string num1 = (this->numBeforePoint->sign + this->numBeforePoint->decStr + this->numAfterPoint->decStr);
    string num2 = (otherBigReal.numBeforePoint->sign + otherBigReal.numBeforePoint->decStr + otherBigReal.numAfterPoint->decStr);
    BigNumber *myNum = new BigDecimalInt(num2);
    dynamic_cast<BigDecimalInt*>(myNum);
    bool res = (BigDecimalInt(num1) > *myNum);
    return res;
}
bool BigReal::operator<(BigNumber& other){
    BigReal& otherBigReal = dynamic_cast<BigReal&>(other);
    padZerosAfterDecimal(this->numAfterPoint->decStr.length() - otherBigReal.numAfterPoint->decStr.length(), otherBigReal);
    string num1 = (this->numBeforePoint->sign + this->numBeforePoint->decStr + this->numAfterPoint->decStr);
    string num2 = (otherBigReal.numBeforePoint->sign + otherBigReal.numBeforePoint->decStr + otherBigReal.numAfterPoint->decStr);
    BigNumber *myNum = new BigDecimalInt(num2);
    dynamic_cast<BigDecimalInt*>(myNum);
    bool res = (BigDecimalInt(num1) < *myNum);
    return res;
}