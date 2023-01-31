#include "header.h"
BigDecimalInt::BigDecimalInt(string BigNumber){
    remove_Unwanted_Zeros(BigNumber);
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
void BigDecimalInt::remove_Unwanted_Zeros(string &BigNumber)
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
BigDecimalInt BigDecimalInt::operator+(BigDecimalInt other){
    if (this->sign == '+' && other.sign == '-')
    {
        other.sign = '+';
        return *this - other;
    }
    else if (this->sign == '-' && other.sign == '+')
    {
        this->sign = '+';
        return other - *this;
    }

    string res;
    int rem=0;
    if (this->sign == '-' && other.sign == '-')
    {
        res += '-';
    }

    if (this->decStr.length() < other.decStr.length())
    {
        swap(*this, other);
    }

    fill_Num_With_Zeros(this->decStr.length() - other.decStr.length(), other);

    for (int i = this->decStr.length() - 1; i >= 0; i--)
    {
        int temp = 0;
        temp = (int)this->decStr[i] - 48 + rem + (int)other.decStr[i] - 48;
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

    if(res[0]=='-'){
        reverse(res.begin() + 1, res.end());
    }
    else{
        reverse(res.begin(), res.end());
    }
    return BigDecimalInt(res);
}
BigDecimalInt BigDecimalInt::operator-(BigDecimalInt other){ 
    if (this->sign == '+' && other.sign == '-')
    {
        other.sign = '+';
        return *this + other;
    }
    else if (this->sign == '-' && other.sign == '+')
    {
        other.sign='-';
        return *this + other;
    }


    if (this->sign == '-' && other.sign == '-')
    {
        other.sign='+';
    }
    string res;
    int x;
    if (this->decStr.length() < other.decStr.length())
    {
        swap(*this, other);
        if (this->sign == '+' && other.sign == '+')
        {
            res+='-';
        }
    }
    fill_Num_With_Zeros(this->decStr.length() - other.decStr.length(), other);
    if ((int)this->decStr[0] - 48 < (int)other.decStr[0] - 48)
    {
        if ((other.sign == '-' && this->sign == '+') || (this->sign == '+' && other.sign == '+'))
        {
            res += '-';
        }
        swap(*this, other);
    }
    if ((int)this->decStr[0] - 48 > (int)other.decStr[0] - 48)
    {
        if (this->sign == '-' && other.sign == '+')
        {
            res += '-';
        }
    }
    else if ((int)this->decStr[0] - 48 == (int)other.decStr[0] - 48)
    {
        for (int i = 0; i < this->decStr.length(); i++)
        {
            if (this->sign == '-' && other.sign == '+')
            {
                if ((int)this->decStr[i] - 48 > (int)other.decStr[i] - 48)
                {
                    res += '-';
                    break;
                }
                else if ((int)this->decStr[i] - 48 < (int)other.decStr[i] - 48)
                {
                    swap(*this, other);
                    break;
                }
            }
            else if (this->sign == '+' && other.sign == '-')
            {
                if ((int)this->decStr[i] - 48 > (int)other.decStr[i] - 48)
                {
                    break;
                }
                else if ((int)this->decStr[i] - 48 < (int)other.decStr[i] - 48)
                {
                    res += '-';
                    swap(*this, other);
                    break;
                }
            }
            else if(this->sign=='+' && other.sign=='+'){
                if ((int)this->decStr[i] - 48 < (int)other.decStr[i] - 48)
                {
                    res += '-';
                    swap(*this, other);
                    break;
                }
                else if ((int)this->decStr[i] - 48 > (int)other.decStr[i] - 48)
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
        if ((int)this->decStr[i] - 48 < (int)other.decStr[i] - 48 && i != 0)
        {
            rem = 10;
            this->decStr[i - 1] -= 1;
        }
        temp = ((int)this->decStr[i] - 48 + rem) - ((int)other.decStr[i] - 48);
        string stemp = to_string(temp);
        res.push_back(stemp[0]);
    }
    if(res[0]=='-'){
        reverse(res.begin() + 1, res.end());
    }
    else{
        reverse(res.begin(), res.end());
    }
    return BigDecimalInt(res);
}
void BigDecimalInt::fill_Num_With_Zeros(int num_of_zeros,BigDecimalInt& other){
    string temp;
    for (int i = 0; i < num_of_zeros; i++)
    {
        temp += '0';
    }
    other.decStr = temp + other.decStr;
}
ostream& operator <<(ostream& out, BigDecimalInt BigNumber){
    out << BigNumber.sign + BigNumber.decStr;
    return out;
}
bool BigDecimalInt::operator>(BigDecimalInt other){
    bool same = false;
    if (this->sign == '-' && other.sign == '+')
    {
        return false;
    }
    else if (this->sign == '+' && other.sign == '-')
    {
        return true;
    }
    else if (this->sign == '+' && other.sign == '+')
    {
        if (this->decStr.length() < other.decStr.length())
        {
            return false;
        }
        else if (this->decStr.length() > other.decStr.length())
        {
            return true;
        }
        else{
            for (int i = 0; i < this->decStr.length(); i++)
            {
                if (this->decStr[i] < other.decStr[i])
                {
                    return false;
                    break;
                }
                else if (this->decStr[i] > other.decStr[i])
                {
                    return true;
                    break;
                }
            }
        }
    }
    if (this->decStr.length() < other.decStr.length())
    {
        return true;
    }
    else if (this->decStr.length() > other.decStr.length())
    {
        return false;
    }
    for (int i = 0; i < this->decStr.length(); i++)
    {
        if (this->decStr[i] < other.decStr[i])
        {
            return true;
            break;
        }
        else if (this->decStr[i] > other.decStr[i])
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
bool BigDecimalInt::operator<(BigDecimalInt other){
    bool same = false;
    if (this->sign == '-' && other.sign == '+')
    {
        return true;
    }
    else if (this->sign == '+' && other.sign == '-')
    {
        return false;
    }
    else if (this->sign == '+' && other.sign == '+')
    {
        if (this->decStr.length() < other.decStr.length())
        {
            return true;
        }
        else if (this->decStr.length() > other.decStr.length())
        {
            return false;
        }
        else{
            for (int i = 0; i < this->decStr.length(); i++)
            {
                if (this->decStr[i] < other.decStr[i])
                {
                    return true;
                    break;
                }
                else if (this->decStr[i] > other.decStr[i])
                {
                    return false;
                    break;
                }
            }
        }
    }
    if (this->decStr.length() < other.decStr.length())
    {
        return false;
    }
    else if (this->decStr.length() > other.decStr.length())
    {
        return true;
    }
    for (int i = 0; i < this->decStr.length(); i++)
    {
        if (this->decStr[i] < other.decStr[i])
        {
            return false;
        }
        else if (this->decStr[i] > other.decStr[i])
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
bool BigDecimalInt::operator==(BigDecimalInt other){
    if (this->sign == other.sign && this->decStr.length() == other.decStr.length())
    {
        for (int i = 0; i < this->decStr.length(); i++)
        {
            if (this->decStr[i] != other.decStr[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
