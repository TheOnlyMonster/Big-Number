#include "header.h"
BigDecimalInt::BigDecimalInt(string BigNumber){
    removeLeadingZeros(BigNumber);
    if (BigNumber[0] == '-')
    {
        this->sign = '-';
    }

    if (BigNumber[0] == '+' || BigNumber[0] == '-')
    {
        BigNumber.erase(0, 1);
    }
    this->decStr = BigNumber;
}
void BigDecimalInt::removeLeadingZeros(string &BigNumber)
{
    int ctr = 0;
    for (int i = 0; i < BigNumber.length(); i++)
    {
        if (BigNumber[i] == '0' && i + 1 != BigNumber.length())
        {
            ctr++;
        }
        else if (BigNumber[i] != '+' && BigNumber[i] != '-')
        {
            break;
        }
    }
    if (BigNumber[0] == '-')
    {
        BigNumber = '-' + BigNumber.substr(ctr + 1);
    }
    else if(BigNumber[0] == '+'){
        BigNumber = '+' + BigNumber.substr(ctr + 1);
    }
    else{
        BigNumber = BigNumber.substr(ctr);
    }
}
BigDecimalInt& BigDecimalInt::operator+(BigNumber& other){
    BigDecimalInt otherBigDecimal = dynamic_cast<BigDecimalInt&>(other);
    string res;
    // Check the signs of the two numbers and act accordingly
    if (this->sign == '+' && otherBigDecimal.sign == '-')
    {
        otherBigDecimal.sign = '+';
        return *this - otherBigDecimal;
    }
    else if (this->sign == '-' && otherBigDecimal.sign == '+')
    {
        this->sign = '+';
        return otherBigDecimal - *this;
    }else if(this->sign == '-' && otherBigDecimal.sign == '-'){
        res += '-';
    }

    int rem=0; // Remainder
    // Swap the two numbers if the first one is shorter than the second one
    if (this->decStr.length() < otherBigDecimal.decStr.length())
    {
        swap(*this, otherBigDecimal);
    }
    // Fill the shorter number with zeros
    addLeadingZeros(this->decStr.length() - otherBigDecimal.decStr.length(), otherBigDecimal);
     // Add the two numbers digit by digit
    for (int i = this->decStr.length() - 1; i >= 0; i--)
    {
        int temp = 0;
        temp = (int)this->decStr[i] - 48 + rem + (int)otherBigDecimal.decStr[i] - 48;
        rem = 0;
        if (temp >= 10)
        {
            string stemp = to_string(temp);
            res.push_back(stemp[1]);
            rem = stemp[0] - 48;
            if (i - 1 < 0)
            {
                res.push_back(stemp[0]);
            }
        }
        else{
            string stemp = to_string(temp);
            res.push_back(stemp[0]);
        }
    }
    // Reverse the result and return it
    if(res[0]=='-'){
        reverse(res.begin() + 1, res.end());
    }
    else{
        reverse(res.begin(), res.end());
    }
    BigDecimalInt* result = new BigDecimalInt(res);
    return *result;
}
BigDecimalInt& BigDecimalInt::operator-(BigNumber& other){ 
    BigDecimalInt otherBigDecimal = dynamic_cast<BigDecimalInt&>(other);
    // Check the signs of the two numbers and act accordingly
    if (this->sign == '+' && otherBigDecimal.sign == '-')
    {
        otherBigDecimal.sign = '+';
        return *this + otherBigDecimal;
    }
    else if (this->sign == '-' && otherBigDecimal.sign == '+')
    {
        otherBigDecimal.sign='-';
        return *this + otherBigDecimal;
    }


    if (this->sign == '-' && otherBigDecimal.sign == '-')
    {
        otherBigDecimal.sign='+';
    }
    string res;
    int x;
    // Swap the two numbers if the first one is shorter than the second one
    if (this->decStr.length() < otherBigDecimal.decStr.length())
    {
        swap(*this, otherBigDecimal);
        // Change the sign of the result depending on the signs of the two numbers
        if (this->sign == '+' && otherBigDecimal.sign == '+')
        {
            res+='-';
        }
    }
    // Fill the shorter number with zeros
    addLeadingZeros(this->decStr.length() - otherBigDecimal.decStr.length(), otherBigDecimal);
     // Check the signs of the two numbers and act accordingly
    if ((int)this->decStr[0] - 48 < (int)otherBigDecimal.decStr[0] - 48)
    {
        if ((otherBigDecimal.sign == '-' && this->sign == '+') || (this->sign == '+' && otherBigDecimal.sign == '+'))
        {
            res += '-';
        }
        swap(*this, otherBigDecimal);
    }
    if ((int)this->decStr[0] - 48 > (int)otherBigDecimal.decStr[0] - 48)
    {
        if (this->sign == '-' && otherBigDecimal.sign == '+')
        {
            res += '-';
        }
    }
    else if ((int)this->decStr[0] - 48 == (int)otherBigDecimal.decStr[0] - 48)
    {
        for (int i = 0; i < this->decStr.length(); i++)
        {
            if (this->sign == '-' && otherBigDecimal.sign == '+')
            {
                if ((int)this->decStr[i] - 48 > (int)otherBigDecimal.decStr[i] - 48)
                {
                    res += '-';
                    break;
                }
                else if ((int)this->decStr[i] - 48 < (int)otherBigDecimal.decStr[i] - 48)
                {
                    swap(*this, otherBigDecimal);
                    break;
                }
            }
            else if (this->sign == '+' && otherBigDecimal.sign == '-')
            {
                if ((int)this->decStr[i] - 48 > (int)otherBigDecimal.decStr[i] - 48)
                {
                    break;
                }
                else if ((int)this->decStr[i] - 48 < (int)otherBigDecimal.decStr[i] - 48)
                {
                    res += '-';
                    swap(*this, otherBigDecimal);
                    break;
                }
            }
            else if(this->sign=='+' && otherBigDecimal.sign=='+'){
                if ((int)this->decStr[i] - 48 < (int)otherBigDecimal.decStr[i] - 48)
                {
                    res += '-';
                    swap(*this, otherBigDecimal);
                    break;
                }
                else if ((int)this->decStr[i] - 48 > (int)otherBigDecimal.decStr[i] - 48)
                {
                    break;
                }
            }
        }
    }
    for (int i = this->decStr.length()-1; i >= 0 ; i--)
    {
        int rem = 0;
        int temp = 0;
        if ((int)this->decStr[i] - 48 < (int)otherBigDecimal.decStr[i] - 48 && i != 0)
        {
            rem = 10;
            this->decStr[i - 1] -= 1;
        }
        temp = ((int)this->decStr[i] - 48 + rem) - ((int)otherBigDecimal.decStr[i] - 48);
        string stemp = to_string(temp);
        res.push_back(stemp[0]);
    }
    if(res[0]=='-'){
        reverse(res.begin() + 1, res.end());
    }
    else{
        reverse(res.begin(), res.end());
    }
    BigDecimalInt* result = new BigDecimalInt(res);
    return *result;
}
void BigDecimalInt::addLeadingZeros(int num_of_zeros,BigDecimalInt& otherBigDecimal){
    string temp;
    for (int i = 0; i < num_of_zeros; i++)
    {
        temp += '0';
    }
    otherBigDecimal.decStr = temp + otherBigDecimal.decStr;
}
bool BigDecimalInt::operator>(BigNumber& other){
    BigDecimalInt& otherBigDecimal = dynamic_cast<BigDecimalInt&>(other);
    bool same = false;
    if (this->sign == '-' && otherBigDecimal.sign == '+')
    {
        return false;
    }
    else if (this->sign == '+' && otherBigDecimal.sign == '-')
    {
        return true;
    }
    else if (this->sign == '+' && otherBigDecimal.sign == '+')
    {
        if (this->decStr.length() < otherBigDecimal.decStr.length())
        {
            return false;
        }
        else if (this->decStr.length() > otherBigDecimal.decStr.length())
        {
            return true;
        }
        else{
            for (int i = 0; i < this->decStr.length(); i++)
            {
                if (this->decStr[i] < otherBigDecimal.decStr[i])
                {
                    return false;
                    break;
                }
                else if (this->decStr[i] > otherBigDecimal.decStr[i])
                {
                    return true;
                    break;
                }
            }
        }
    }
    if (this->decStr.length() < otherBigDecimal.decStr.length())
    {
        return true;
    }
    else if (this->decStr.length() > otherBigDecimal.decStr.length())
    {
        return false;
    }
    for (int i = 0; i < this->decStr.length(); i++)
    {
        if (this->decStr[i] < otherBigDecimal.decStr[i])
        {
            return true;
            break;
        }
        else if (this->decStr[i] > otherBigDecimal.decStr[i])
        {
            return false;
            break;
        }
        else{
            same = true;
        }
    }
    if (same)
    {
        return false;
    }
    return true;
}
bool BigDecimalInt::operator<(BigNumber& other){
    BigDecimalInt& otherBigDecimal = dynamic_cast<BigDecimalInt&>(other);
    bool same = false;
    if (this->sign == '-' && otherBigDecimal.sign == '+')
    {
        return true;
    }
    else if (this->sign == '+' && otherBigDecimal.sign == '-')
    {
        return false;
    }
    else if (this->sign == '+' && otherBigDecimal.sign == '+')
    {
        if (this->decStr.length() < otherBigDecimal.decStr.length())
        {
            return true;
        }
        else if (this->decStr.length() > otherBigDecimal.decStr.length())
        {
            return false;
        }
        else{
            for (int i = 0; i < this->decStr.length(); i++)
            {
                if (this->decStr[i] < otherBigDecimal.decStr[i])
                {
                    return true;
                    break;
                }
                else if (this->decStr[i] > otherBigDecimal.decStr[i])
                {
                    return false;
                    break;
                }
            }
        }
    }
    if (this->decStr.length() < otherBigDecimal.decStr.length())
    {
        return false;
    }
    else if (this->decStr.length() > otherBigDecimal.decStr.length())
    {
        return true;
    }
    for (int i = 0; i < this->decStr.length(); i++)
    {
        if (this->decStr[i] < otherBigDecimal.decStr[i])
        {
            return false;
        }
        else if (this->decStr[i] > otherBigDecimal.decStr[i])
        {
            return true;
        }
        else{
            same = true;
        }
        
    }
    if (same)
    {
        return false;
    }
    return true;
}
bool BigDecimalInt::operator==(BigNumber& other){
    BigDecimalInt& otherBigDecimal = dynamic_cast<BigDecimalInt&>(other);
    if (this->sign == otherBigDecimal.sign && this->decStr.length() == otherBigDecimal.decStr.length())
    {
        for (int i = 0; i < this->decStr.length(); i++)
        {
            if (this->decStr[i] != otherBigDecimal.decStr[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}