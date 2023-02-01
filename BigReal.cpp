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
    BigReal_B = new BigDecimalInt(realNumber.substr(0,this->fractionIndex));
    reverse(realNumber.begin() + this->fractionIndex, realNumber.end());
    BigDecimalInt *BigReal_A_Temp = new BigDecimalInt(realNumber.substr(this->fractionIndex));
    reverse(BigReal_A_Temp->decStr.begin(), BigReal_A_Temp->decStr.end());
    BigReal_A = BigReal_A_Temp;
    this->fractionIndex = BigReal_B->decStr.length() - 1;
    this->realStr = BigReal_B->decStr + '.' + BigReal_A->decStr;
    this->sign = this->BigReal_B->sign;
}
BigReal BigReal::operator+(BigReal& other){
    int biggerA = max(this->BigReal_A->decStr.length(), other.BigReal_A->decStr.length());

    if (this->BigReal_B->sign == '+' && other.BigReal_B->sign == '-')
    {
        other.BigReal_B->sign = '+';
        return *this - other;
    }
    else if (this->BigReal_B->sign == '-' && other.BigReal_B->sign == '+')
    {
        this->BigReal_B->sign = '+';
        return other - *this;
    }


    if (this->fractionIndex < other.fractionIndex)
    {
        swap(*this, other);
    }
    fill_Num_B_With_Zeros(this->BigReal_B->decStr.length() - other.BigReal_B->decStr.length(), other.BigReal_B);
    if (this->BigReal_A->decStr.length() > other.BigReal_A->decStr.length())
    {
        fill_Num_A_With_Zeros(this->BigReal_A->decStr.length() - other.BigReal_A->decStr.length(), other.BigReal_A);
    }
    else if (this->BigReal_A->decStr.length() < other.BigReal_A->decStr.length())
    {
        fill_Num_A_With_Zeros(this->BigReal_A->decStr.length() - other.BigReal_A->decStr.length(), this->BigReal_A);
    }
    string num1 = (this->BigReal_B->sign + this->BigReal_B->decStr + this->BigReal_A->decStr);
    string num2 = (other.BigReal_B->sign + other.BigReal_B->decStr + other.BigReal_A->decStr);
    BigDecimalInt Res = BigDecimalInt(num2) + BigDecimalInt(num1);
    Res.decStr.insert(Res.decStr.length() - biggerA, 1, '.');
    return BigReal(Res.sign + Res.decStr);
}
BigReal BigReal::operator-(BigReal& other){
    int biggerA = max(this->BigReal_A->decStr.length(), other.BigReal_A->decStr.length());
    bool negative_sign = false, isSwaped = false;
    if (this->fractionIndex < other.fractionIndex)
    {
        if (other.BigReal_B->sign == '+')
        {
            negative_sign = true;
        }
        isSwaped = true;
        swap(*this, other);
    }
    fill_Num_B_With_Zeros(this->BigReal_B->decStr.length() - other.BigReal_B->decStr.length(), other.BigReal_B);
    if (this->BigReal_A->decStr.length() > other.BigReal_A->decStr.length())
    {
        fill_Num_A_With_Zeros(this->BigReal_A->decStr.length() - other.BigReal_A->decStr.length(), other.BigReal_A);
    }
    else if (this->BigReal_A->decStr.length() < other.BigReal_A->decStr.length())
    {
        fill_Num_A_With_Zeros(this->BigReal_A->decStr.length() - other.BigReal_A->decStr.length(), this->BigReal_A);
    }
    string num1 = (this->BigReal_B->sign + this->BigReal_B->decStr + this->BigReal_A->decStr);
    string num2 = (other.BigReal_B->sign + other.BigReal_B->decStr + other.BigReal_A->decStr);
    BigDecimalInt *Res;
    if(isSwaped){
        Res = new BigDecimalInt(BigDecimalInt(num2) - BigDecimalInt(num1));
    }
    else{
        Res = new BigDecimalInt(BigDecimalInt(num1) - BigDecimalInt(num2));
    }
    int len = Res->decStr.length();
    if ((len - biggerA) < 0){
        fill_Num_B_With_Zeros(biggerA - len, Res);
        Res->decStr.insert(0, 1, '.');
    }
    else{
        Res->decStr.insert(len - biggerA, 1, '.');
    }
    if(negative_sign){
        Res->sign = '-';
    }
    return BigReal(Res->sign + Res->decStr);
}
void BigReal::fill_Num_A_With_Zeros(int num_of_zeros, BigDecimalInt *other){
    for (int i = 0; i < abs(num_of_zeros); i++)
    {
        other->decStr += '0';
    }
}
void BigReal::fill_Num_B_With_Zeros(int num_of_zeros, BigDecimalInt *other){
    string temp;
    for (int i = 0; i < num_of_zeros; i++)
    {
        temp += '0';
    }
    other->decStr = temp + other->decStr;
}
ostream& operator <<(ostream& out, BigReal BigNumber){
    out << BigNumber.sign << BigNumber.realStr;
    return out;
}
bool BigReal::operator==(BigReal other){
    string num1 = (this->BigReal_B->sign + this->BigReal_B->decStr + this->BigReal_A->decStr);
    string num2 = (other.BigReal_B->sign + other.BigReal_B->decStr + other.BigReal_A->decStr);
    bool res = (BigDecimalInt(num1) == BigDecimalInt(num2));
    return res;
}
bool BigReal::operator>(BigReal other){
    string num1 = (this->BigReal_B->sign + this->BigReal_B->decStr + this->BigReal_A->decStr);
    string num2 = (other.BigReal_B->sign + other.BigReal_B->decStr + other.BigReal_A->decStr);
    bool res = (BigDecimalInt(num1) > BigDecimalInt(num2));
    return res;
}
bool BigReal::operator<(BigReal other){
    string num1 = (this->BigReal_B->sign + this->BigReal_B->decStr + this->BigReal_A->decStr);
    string num2 = (other.BigReal_B->sign + other.BigReal_B->decStr + other.BigReal_A->decStr);
    bool res = (BigDecimalInt(num1) < BigDecimalInt(num2));
    return res;
}