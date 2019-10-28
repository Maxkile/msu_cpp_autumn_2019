#pragma once

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cassert>

class Matrix{

    class Row
    {
        size_t rowNumber;
        int* row;//copying the pointer here

        public:

        Row(size_t rowNumber,int* row);

        int& operator[](const size_t j);
            
    };

	size_t rows;
	size_t columns;

    int** matrix;

    void m_create();

public:

    Matrix(const size_t rows,const size_t columns);

    Matrix(const size_t size);

    Matrix(const Matrix& source);

    Row operator[](const size_t i);

    Matrix& operator=(const int number);

    Matrix& operator*=(const int number);

    bool operator==(const Matrix& other) const;

    bool operator!=(const Matrix& other) const;

    size_t getRowsNumber() const;

    size_t getColumnsNumber() const;

    void print() const;
    
    ~Matrix();

};