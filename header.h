#ifndef HEADER_H
#define HEADER_H
#include <bits/stdc++.h>
using namespace std;
class BigDecimalInt{
    private:
        char sign = '+'; // The Default Sign for The Big Number Is + Unless The User Enters '-' Sign
        string decStr; // This Member Stores The Big Number Value After Removing Unwanted Zeros & '+' or '-' Signs
        void remove_Unwanted_Zeros(string &); // This Function Removes Unwanted Zeros In The Left Side of The Big Number e.g. "000023341"
        void fill_Num_With_Zeros(int, BigDecimalInt &); // This Function Is Called When We want to Add Zeros In The Left Side of The Big Number e.g. "0065" + "9812"
    public:
        friend class BigReal;
        BigDecimalInt(string);
        bool operator<(BigDecimalInt);
        bool operator>(BigDecimalInt);
        bool operator==(BigDecimalInt);
        BigDecimalInt operator+(BigDecimalInt);
        BigDecimalInt operator-(BigDecimalInt);
        friend ostream& operator <<(ostream&, BigDecimalInt);
};
class BigReal{
    private:
        char sign = '+'; // The Default Sign for The Big Number Is + Unless The User Enters '-' Sign
        int fractionIndex; // This Member Stores The Fraction Point Index
        string realStr; // This Member Stores The Whole Number With The Fraction Point Value After Removing Unwanted Zeros & '+' or '-' Signs
        BigDecimalInt *BigReal_A; // This Pointer Points To The Number After The Fraction Point
        BigDecimalInt *BigReal_B; // This Pointer Points To The Number Before The Fraction Point
        void fill_Num_A_With_Zeros(int, BigDecimalInt *); // This Function Fills Num After The Fraction Point With Zeros
        void fill_Num_B_With_Zeros(int, BigDecimalInt *); // This Function Fills Num Before The Fraction Point With Zeros
    public:
        BigReal(string);
        BigReal operator+(BigReal&); 
        BigReal operator-(BigReal&);
        friend ostream& operator <<(ostream&, BigReal);
        bool operator==(BigReal);
        bool operator>(BigReal);
        bool operator<(BigReal);
};
#endif