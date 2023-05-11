# BigNumber Library

This repository contains a C++ library for working with BigNumber objects, which represent large numerical values stored as strings of decimal digits. The library provides support for standard comparison and mathematical operations, such as `<`, `>`, `==`, `+`, and `-`. It also includes an overload for the `<<` operator to print BigNumber objects to the console.

## Installation

To use this library in your C++ project, follow these steps:

1. Clone the repository or download the source code files.
2. Include the `header.h` file in your project.

```cpp
#include "header.h"
```
## BigNumber Class

The `BigNumber` class is an abstract base class that defines the common interface for working with large numbers. It includes the following pure virtual member functions:

• `bool operator<(BigNumber&)`: Overloaded operator to check if one `BigNumber` object is less than another.

• `bool operator>(BigNumber&)`: Overloaded operator to check if one `BigNumber` object is greater than another.

• `bool operator==(BigNumber&)`: Overloaded operator to compare two `BigNumber` objects.

• `BigNumber& operator+(BigNumber&)`: Overloaded operator to add two `BigNumber` objects.

• `BigNumber& operator-(BigNumber&)`: Overloaded operator to subtract two `BigNumber` objects.

## BigDecimalInt Class

The `BigDecimalInt` class is derived from `BigNumber` and represents an integer number with a decimal point. It provides methods to compare, add, and subtract values with other `BigNumber` objects. The constructor takes a string as a parameter to initialize the instance.

## BigReal Class

The `BigReal` class is also derived from `BigNumber` and is designed to hold large real numbers. It implements addition, subtraction, comparison, and equality operators. The constructor takes a string as a parameter to initialize the instance.

## Example

Here's a simple example demonstrating the usage of the `BigNumber` library:
```cpp
#include <iostream>
#include "header.h"

int main() {
    // Create BigDecimalInt objects
    BigDecimalInt num1("123456789");
    BigDecimalInt num2("987654321");

    // Add two BigDecimalInt objects
    BigNumber& sum = num1 + num2;

    // Print the result
    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
```
## Contributing

Contributions to this library are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.
