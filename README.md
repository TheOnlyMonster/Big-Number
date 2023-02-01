# Big-Number
 This program let the user do mathmatical operations on infinite numbers.

Different variations of types int and float exist in C++ and other languages. They are limited by minimum and maximum values depending on the number of bytes used to 
store the number. Moreover, sometimes users might need versions of these types with unlimited bounds. Java solves this problem by providing BigInteger and BigDecimal 
classes. As a result, I developed two new C++ types (classes) that can hold unlimited decimal and real values and performs arithmetic operations on them. 

The first class called BigDecimalInt. This class stores infinite numbers without fractions and can performs arithmetic operations on them. BigDecimalInt class have the 
following attribute:<br />

• <strong>Sign</strong>. The default sign for the big number is '+' unless the user enters '-' sign.<br />
• <strong>decStr</strong>. this member stores the big number value after removing unwanted zeros & '+' or '-' signs.<br />
Furthermore, I created the following functions in order to make my code clean.<br />
• <strong>remove_Unwanted_Zeros</strong>. This function removes unwanted zeros in the left side of the big number e.g. "000023341"<br />
• <strong>fill_Num_With_Zeros</strong>. This function is called when we want to add zeros in the left side of the big number e.g. "0065" + "9812"<br />

On the other hand, the second class called BigReal this class extends the first one and can store infinite numbers with fractions. In order to do so, I stored the 
integer and fraction parts in two separate pointers of type BigDecimalInt.<br />

• <strong>BigReal_A</strong>. This pointer points to the number after the fraction point.<br />
• <strong>BigReal_B</strong>. This pointer points to the number before the fraction point.<br />
Also, I stored the fraction point index in a member of type int called <strong>fractionIndex</strong>.
