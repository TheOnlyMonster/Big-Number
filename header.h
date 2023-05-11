#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <algorithm>
using namespace std;
/* 
This class represents a BigNumber, which is a numerical value stored as a string of decimal digits. 
It supports standard comparison and mathematical operations, such as <, >, ==, + and -. 
It also defines an overload for the << operator for printing a BigNumber to the console.
*/
class BigNumber {
    protected:
        // Sign of the number
        char sign = '+';
        // String representation of the number
        std::string decStr;
    public:
        // Overloaded operator to check if one BigNumber object is less than another
        virtual bool operator<(BigNumber&) = 0;
        // Overloaded operator to check if one BigNumber object is greater than another
        virtual bool operator>(BigNumber&) = 0;
        // Overloaded operator to compare two BigNumber objects
        virtual bool operator==(BigNumber&) = 0;
        // Overloaded operator to add two BigNumber objects
        virtual BigNumber& operator+(BigNumber&) = 0;
        // Overloaded operator to subtract two BigNumber objects
        virtual BigNumber& operator-(BigNumber&) = 0;
        friend std::ostream& operator<<(std::ostream& out, const BigNumber& other){
            out << other.sign << other.decStr;
            return out;
        }
};
/* 
BigDecimalInt class represents an integer number that has a decimal point and uses BigNumber as its base class.
This class has several methods to compare, add, and subtract values with other BigNumber objects.
It also takes a string as a parameter when creating an instance. Additionally, it also has private methods to remove and add leading zeros.
*/
class BigDecimalInt : public BigNumber {
private:
    void removeLeadingZeros(std::string&);
    void addLeadingZeros(int, BigDecimalInt&);
public:
    friend class BigReal;
    BigDecimalInt(std::string);
    bool operator<(BigNumber&) override;
    bool operator>(BigNumber&) override;
    bool operator==(BigNumber&) override;
    BigDecimalInt& operator+(BigNumber&) override;
    BigDecimalInt& operator-(BigNumber&) override;
};
/*
This class provides an implementation of the BigNumber abstract class, designed to hold large real numbers. 
It has implementations of addition, subtraction, comparison, and equality operators. 
It also contains private methods to pad zeros before and after the decimal point.
*/
class BigReal : public BigNumber {
    private:
        // Index of the decimal point
        int fractionIndex;
        // Pointers to two BigDecimalInt objects
        BigDecimalInt *numAfterPoint;
        BigDecimalInt *numBeforePoint;
        // Function to fill the first BigDecimalInt object with zeros
        void padZerosAfterDecimal(int, BigReal &);
        // Function to fill the second BigDecimalInt object with zeros
        void padZerosBeforeDecimal(int, BigDecimalInt *);
    public:
        // Constructor to initialize the BigReal object
        BigReal(string);
        BigReal& operator+(BigNumber&) override; 
        BigReal& operator-(BigNumber&) override;
        bool operator==(BigNumber&) override;
        bool operator>(BigNumber&) override;
        bool operator<(BigNumber&) override;
};
#endif