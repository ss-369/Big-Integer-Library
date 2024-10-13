# Big-Integer-Library

---


## Description

This project implements a **Big Integer Library** that supports arithmetic operations on arbitrarily large integers. The library is inspired by the `BigInteger` class in Java and allows operations such as addition, subtraction, multiplication, division, exponentiation, GCD, and factorial for numbers with more than 3000 digits.

## Features
- **Basic Arithmetic Operations**: Addition (`+`), Subtraction (`-`), Multiplication (`*`), and Division (`/`)
- **Exponentiation**: Raise a large integer to the power of another
- **GCD**: Calculate the greatest common divisor of two large integers
- **Factorial**: Calculate the factorial of a large number

## Input Format
- The first line contains an integer value indicating the type of operation:
  - `1`: Basic Arithmetic
  - `2`: Exponentiation
  - `3`: GCD
  - `4`: Factorial
- The following line(s) contain the input for the respective operation.

## Example
### Input:
```
1
32789123+99893271223*9203232392-4874223
```

### Output:
```
919340989462382970316
```

## How to Run
1. Compile the program:
   ```bash
   g++ -o big_integer <Roll_Number>_A1_Q1.cpp
   ```

2. Run the program and follow the input format:
   ```bash
   ./big_integer
   ```

---

