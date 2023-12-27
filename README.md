# Arbitrary-precision Integers Project

Author: Peng Yixin
Master of Computational Science and Engineering
email:pengy107@mcmaster.ca

## Table of Contents
- [Introduction](#introduction)
- [Constructor](#constructor)
  - [Default constructor](#default-constructor)
  - [Constructor that takes a signed 64-bit integer](#constructor-that-takes-a-signed-64-bit-integer)
  - [Constructor that takes a string](#constructor-that-takes-a-string)
- [Operator overloading](#Operator-overloading)
  - [add, add and assign](#add-add-and-assign)
  - [subtract, subtract and assign](#subtract-subtract-and-assign)
  - [multiply, multiply and assign](#multiply-multiply-and-assign)
  - [negation operations](#negation-operations)
  - [comparison operations](#comparison-operations)
  - [assignment operations](#assignment-operations)
  - [insertion operators](#insertion-operators)

## Introduction

This project aims to develop a new C++ class, named "bigint", to handle arbitrary-precision integers. We use vector to storee integers, the first digit of the vector represents positive and negative, 0 represents a positive number, 1 represents a negative number, and the rest of the digits are limited from 0 to 9. The class has three key constructors: the default constructor, which creates an empty arbitrary-precision integer object, a constructor that converts int64_t to a vector, and a constructor that converts a string to a vector. These allow users to easily create arbitrary-precision integer objects.

In addition, we have overloaded several operators, including add(+), add and assign (+=), subtract(-), subtract and assign (-=), multiply (\*), multiply and assign (\*=), negation operations (unary -), comparison operations (==, !=, <, >, <= and >=), assignment operations (=), and insertion operators (<<). With the implementation of these features, we provide users with a powerful and easy-to-use class of arbitrary-precision integers. Next, we'll take a look at the specific implementation and usage of each of these features.

## Constructor

### Default constructor

A default constructor, creating the integer 0.
```C++
// Create a new default object
bigint A;
cout << "A: " << A << '\n';
```
```C++
// The output:
A: 0
```
### Constructor that takes a signed 64-bit integer

When we receive an integer of type of int64_t, First we judge if it is positive or negative. If it is negative, insert the first term of vector v into 1; Otherwise, 0 is inserted. Next, the absolute value of the integer is obtained and the loop is entered. In the loop, if the absolute value is greater than 9, divide the integer by 10 and insert the remainder into the second position of the vector v. Next, continue to cycle through the number obtained by dividing by 10 until the whole number is less than or equal to 9. Eventually, an integer is inserted into the second position of the vector v, forming a vector representation that represents the arbitrary precision of the integer.

```C++
// Create a new object
bigint B(2023);
cout << "B: " << B << '\n';
bigint C(-1226);
cout << "C: " << C << '\n';
```
```C++
// The output:
B: 2023
C: -1226
```

### Constructor that takes a string

When processing a string type integer as a parameter, if the string is empty, 0 is inserted into the vector v; if the string is not empty, the first bit of the string is checked first. If the first bit is '-', insert 1 into the first bit of vector v and delete the symbol in the string; if the first bit is '+', insert 0 into the first bit of vector v and delete the symbol in the string; If the first bit is a number, it means that the string is a positive number, and 0 is inserted into the first bit of the vector v. If the first digit does not meet the above conditions, an exception of "The first character must be digit or sign" will be thrown.

Put the processed string into a for loop and insert each number into the vector v bit by bit. Before inserting, care needs to be taken to convert the characters into numbers. This can be achieved by subtracting 48, since the value of the number 0 in ASCII encoding is 48. If a digit of the string is not a digit, the exception "Input must be digit" is thrown.

```C++
// Create a new object
try
    {
        string str = "+8tq3";
        bigint A(str);
        cout << "A: " << A << '\n';
    }
    catch (const invalid_argument &e)
    {
        cout << "Error: " << e.what() << '\n';
    }

    string str1 = "0";
    bigint B(str1);
    cout << "B: " << B << '\n';
    string str2 = "-2023";
    bigint C(str2);
    cout << "C: " << C << '\n';
```
```C++
// The output:
Error: Input must be digit
B: 0
C: -2023
```

## Operator overloading

Before proceeding with method overloading, I wrote a member function called zero, the main goal of which is to eliminate invalid leading zeros in the bigint numeric representation. If the second element is zero and the vector length is more than 2, the zero element is deleted. Eventually, the processed result object is returned

### add, add and assign

First, judge the two objects: if both are positive numbers, their sum is also positive, and the first bit of the new integer (newint) is 0; if both are negative numbers, their sum is also negative, and the new integer The first bit of is 1; if one is positive and one is negative, the subtraction operation is called. In the process of performing the addition of two numbers, we define the variable i to represent the number of digits of the first addend minus 1, the variable j to represent the number of digits of the other addend minus 1, and a carry variable (carrier). When i or j is greater than 0, add the i-th and j-th bits of the two addends, as well as the carry carrier. Divide the resulting sum by 10, insert the remainder into the second item of vector v, and the resulting quotient is used as the carry for the next cycle. When i and j are both 0, it means the loop is complete. Finally, determine whether the carry variable carrier still has a value. If it is not 0, insert it into the second item of the vector v.

```C++
// A:0; B:100000000000000000000; C:-999888777666555444; D:2024
cout << "A+B: " << (A + B) << '\n';
cout << "A+C: " << (A + C) << '\n';
cout << "B+C: " << (B + C) << '\n';
cout << "C+D: " << (C + D) << '\n';
```
```C++
// The output:
A+B: 100000000000000000000
A+C: -999888777666555444
B+C: 99000111222333444556
C+D: -999888777666553420
```

Then we implement the "+=" operator overload, which is used to implement the addition assignment operation. By calling the + operator overload, the current object (*this) is added to the incoming rhs and the result is assigned to the current object.

```C++
// E:2; F:100
E += F;
cout << "E+=F: " << E << '\n';
```
```C++
// The output:
E+=F: 102
```

### subtract, subtract and assign


In the method overload of the subtraction operation, the main function handles the subtraction of two positive numbers, and when the subtraction is greater than the subtraction. All other cases can be translated into this situation. For example, if one of the subtractions and the subtraction are positive and the other is negative, we can call addition to complete the operation. In the case where two positive numbers are subtracted and the minus is less than the subtracted number, we can swap the absolute values of the two numbers and make the new result (newint) negative. Now, let's focus on the implementation of the main function, i.e., the handling of two positive numbers subtracting, especially when the subtraction is greater than the subtraction.

First, we introduced the variable i, which is used to denote the number of digits of the minus 1, the variable j, which is used to denote the number of digits of the subtracted number minus 1, and a borrow. Write a loop that subtracts 1 from i and j after each iteration. When i>0 and j>0, the ith digit of the minus first subtracts the borrow and then subtracts the j-digit of the subtracted digit. If the resulting number is greater than 0, insert the number into the second digit of the newint and set the borrow to 0. If the resulting number is less than 0, add 10 to the number and set the borrow to 1. When i>0 and j=0, it is equivalent to the subtraction of 0, and the others remain unchanged.

```C++
// A:0; B:100000000000000000000; C:-999888777666555444; D:2024
cout << "A-B: " << (A - B) << '\n';
cout << "A-C: " << (A - C) << '\n';
cout << "B-C: " << (B - C) << '\n';
cout << "C-D: " << (C - D) << '\n';
```
```C++
// The output:
A-B: -100000000000000000000
A-C: 999888777666555444
B-C: 100999888777666555444
C-D: -999888777666557468
```

Similar to additive assignments. We subtract the current object (*this) from the passed rhs by calling the "-" operator overload, and assign the result to the current object, which implements the subtraction assignment operation.

```C++
// E:2; F:100
E -= F;
cout << "E-=F: " << E << '\n';
```
```C++
// The output:
E-=F: -98
```

### multiply, multiply and assign

In the method overload of multiplication, we introduce the variable i, which is used to represent the number of digits of the multiplier minus 1, the variable j, which is used to represent the number of digits of the second multiplier minus 1, and create a new bigint object newint to store the result of multiplication. Next, through a two-layer loop design, the outer loop traverses every bit in the rhs and the inner loop traverses every bit in the left operand this. In the inner loop, we multiply the resulting rhs.v[j] by the entire operand, and store the resulting number in the temporary bigint variable mul. Depending on the number of digits, we will make up 0 accordingly. For example, if rhs.v[j] is a digit number, you don't need to add 0; If it's a number in the tens place, add 1 0, and so on, to get the final mul. Finally, a series of muls are obtained through the outer loop, and they are added together to get the final result.

Finally, we determine the symbol of newint by determining whether the two multipliers have the same sign. If both multipliers are positive or both negative, the sign for newint is positive; If one is positive and the other is negative, then the sign of newint is negative. In this way, by multiplying and accumulating bit by bit, we have completed the operation of multiplying two large integers.

```C++
// A:0; B:100000000000000000000; C:-999888777666555444; D:2024
cout << "A*B: " << (A * B) << '\n';
cout << "A*C: " << (A * C) << '\n';
cout << "B*C: " << (B * C) << '\n';
cout << "C*D: " << (C * D) << '\n';
```
```C++
// The output:
A*B: 0
A*C: -0
B*C: -99988877766655544400000000000000000000
C*D: -2023774885997108218656
```
We do this by calling the "*" operator overload to multiply the current object (*this) by passing in rhs.

```C++
// E:2; F:100
E *= F;
cout << "E*=F: " << E << '\n';
```
```C++
// The output:
E*=F: 200
```

### comparison operations

When determining whether two bigint variables are equal, first check whether they are the same size. If the sizes are different, return false directly; if the sizes are the same, continue to compare each item one by one. Returns false if any items are different; returns true if all items are the same after the loop ends. When judging whether two bigints are not equal, the opposite result of "==" is output.

```C++
// A:0; B:100; C:-99; D:100
cout << "A == B: " << (A == B) << '\n';
cout << "B == C: " << (B == C) << '\n';
cout << "B != C: " << (B != C) << '\n';
cout << "B == D: " << (B == D) << '\n';
```
```C++
// The output:
A == B: 0
B == C: 0
B != C: 1
B == D: 1
```
Next, I'll do the less than or equal method overloading. First, judge whether the two input numbers are positive or negative, because the negative number must be smaller than the positive number. If two positive numbers are compared, the one with smaller size must be smaller than the one with larger size. If the sizes are the same, the loop judgment starts from the second item. Once the corresponding bit on one side is smaller, the side is smaller overall. If two negative numbers are compared, the rules are reversed. The less than, greater than, and greater than or equal method overloads can be implemented by using the overloads of the less than or equal operator.

```C++
// A:0; B:100; C:-99; D:100
cout << "A < B: " << (A <= B) << '\n';
cout << "B <= C: " << (B <= C) << '\n';
cout << "B >= C: " << (B >= C) << '\n';
cout << "B < D: " << (B < D) << '\n';
cout << "B <= D: " << (B <= D) << '\n';
```
```C++
// The output:
A < B: 1
B <= C: 0
B >= C: 1
B < D: 0
B <= D: 1
```

### negation operations

In the negation operation, I create a new bigint variable "result" and assign it to the current object "this". Then I check the first bit of "result". If the first bit is 0, replace it with 1; if the first bit is 1, replace it with 0.

```C++
// A:0; B:100; C:-99
cout << "-A: " << -A << '\n';
cout << "-B: " << -B << '\n';
cout << "-C: " << -C << '\n';
```
```C++
// The output:
-A: -0
-B: -100
-C: 99
```

### assignment operations

This code is an overloaded implementation of the assignment operator "=" in the "bigint" class. The assignment operation of two objects is implemented by assigning the integer representation "v" of the right operand "rhs" to the integer representation of the current object.

```C++
// C:-99
bigint D = C;
cout << "D: " << D << '\n';

```
```C++
// The output:
D: -99
```

### insertion operators

Next, I customized the output stream operator "<<" to first check the bitness of the object. If there is only one bit (which is the case when the default constructor is defined), the character '0' is output. Next, I determine its sign. If the first bit is 1, indicating a negative number, the symbol '-' will be output; if the first bit is 0, indicating a positive number, no symbol will be output. I then iterate through each digit starting from the second digit of the integer, inserting each digit into the output stream. Finally, I return the output stream object to complete the operation.


