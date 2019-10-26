#pragma once

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cassert>

class Matrix{

    class Row
    {
        int rowNumber;
        int* row;//copying the pointer here

        public:

            Row(int rowNumber,int* row);

            int& operator[](int j );
            
    };

	int rows;
	int columns;

    int** matrix;

    void m_create();

public:

    Matrix(const int rows,const int columns);

    Matrix(const int size);

    Matrix(Matrix& source);

    Row operator[](const int i);


    Matrix& operator=(const int number);

    Matrix& operator*=(const int number);

    bool operator==(Matrix& other);

    bool operator!=(Matrix& other);

    int getRowsNumber() const;

    int getColumnsNumber() const;

    void print();
    
    ~Matrix();

};