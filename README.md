## Overview

This project implements a C++ class called **SquareMat** that represents square matrices and supports various matrix operations. The class includes functions for matrix addition, subtraction, multiplication (both matrix and scalar), modulo operation, exponentiation, determinant calculation, and matrix comparisons (equality and inequality). All operations are implemented manually without the use of advanced data structures like STL vectors, and dynamic memory management is handled using `new` and `delete`.

---

## Requirements

Before running the project, ensure that your system has the following tools:

- C++11 or later
- g++ (C++ compiler)

---

## File Structure

The project is divided into several files:

- **SquareMat.h** – Header file containing the declaration of the `SquareMat` class and its member functions.
- **SquareMat.cpp** – Implementation file for the `SquareMat` class, containing the definitions of the matrix operations.
- **main.cpp** – A test or demonstration file that showcases how to use the `SquareMat` class and performs basic operations.
- **Makefile** – A Makefile for compiling the project and running tests.

---


## Running the Project

After downloading all the files, run the following commands in your terminal:

1. **Build the project**:  
   `make Main`

2. **Run unit tests**:  
   `make test`

3. **Check for memory leaks**:  
   `make valgrind`

4. **Clean up**:  
   `make clean`

---


## Explanation of Functions

- **SquareMat(int n)** - Creates an n x n square matrix initialized with zeros.

- **SquareMat operator+(const SquareMat& other)** - Adds two matrices.

- **SquareMat operator-(const SquareMat& other)** - Subtracts two matrices.

- **SquareMat operator*(const SquareMat& other)** - Multiplies two matrices.

- **SquareMat operator*(int scalar)** - Multiplies the matrix by a scalar value.

- **SquareMat operator%(int mod)** - Applies modulo operation element-wise on the matrix.

- **SquareMat operator^(int power)** - Raises the matrix to a given integer power.

- **int determinant()** - Calculates the determinant of the matrix using recursion.

- **bool operator==(const SquareMat& other)** - Checks if two matrices are equal.

- **bool operator!=(const SquareMat& other)** - Checks if two matrices are not equal.  

- **SquareMat operator-()** - Negates the matrix.

- **SquareMat& operator++()** - Prefix increment (increment each element by 1).

- **SquareMat operator++(int)** - Postfix increment (increment each element by 1).

- **SquareMat& operator--()** - Prefix decrement (decrement each element by 1).

- **SquareMat operator--(int)** - Postfix decrement (decrement each element by 1).

- **int operator()(int row, int col)** - Accesses the element at position (row, col) (gets the value).

- **void set(int row, int col, int value)** - Sets the element at position (row, col) to value.

- **void print()** - Prints the matrix in a readable format.


---



## Contact
- Email: emuna002@gmail.com
