#include "MatrSum.hpp"

Matrix::Row::Row(const size_t rowNumber,int* row):rowNumber(rowNumber),row(row){}

int& Matrix::Row::operator[](size_t j)
{
    std::cout << "NON CONST" << std::endl;
    if ((j >= rowNumber) || (j < 0))
    {
        throw std::out_of_range("Out of range!");
    } 
    else
    {
        return row[j];
    }
}

const int Matrix::Row::operator[](size_t j) const
{
    std::cout << "CONST" << std::endl;
    if ((j >= rowNumber) || (j < 0))
    {
        throw std::out_of_range("Out of range!");
    } 
    else
    {
        return row[j];
    }
}

void Matrix::m_create()
{
    matrix = new int*[rows];//int pointer array
    for (size_t i = 0; i<rows;++i)
    {
        matrix[i] = new int[columns];//int array
    }
}

Matrix::Matrix(const size_t rows,const size_t columns):rows(rows),columns(columns)
{
    m_create();
}

Matrix::Matrix(const size_t size):rows(size),columns(size)
{
    m_create();
}

Matrix::Matrix(const Matrix& source):rows(source.rows),columns(source.columns)
{
    m_create();
    for(size_t i = 0;i<source.rows;++i)
    {
        for(size_t j = 0;j<source.columns;++j)
        {
            matrix[i][j] = source[i][j];
        }
    }
}

const Matrix::Row Matrix::operator[](const size_t i) const
{
     std::cout << "CONST OUTER" << std::endl;
    if ((i >= rows) || (i < 0))
    {
        throw std::out_of_range("Out of range!");
    } 
    else
    {
        return Row(columns,matrix[i]);
    }
}

Matrix::Row Matrix::operator[](const size_t i)
{
    std::cout << "NON CONST OUTER" << std::endl;
    if ((i >= rows) || (i < 0))
    {
        throw std::out_of_range("Out of range!");
    } 
    else
    {
        return Row(columns,matrix[i]);
    }
}


Matrix& Matrix::operator=(const int number)
{
    for(size_t i = 0;i<rows;++i)
    {
        for(size_t j = 0;j<columns;++j)
        {
            matrix[i][j] = number;
        }
    }
    return (*this);
}

Matrix& Matrix::operator*=(const int number)
{
    for(size_t i = 0;i<rows;++i)
    {
        for(size_t j = 0;j<columns;++j)
        {
            matrix[i][j] *= number;
        }
    }
    return (*this);
}

bool Matrix::operator==(const Matrix& other) const
{
    if ((other.getColumnsNumber() != columns) || (other.getRowsNumber() != rows))
    {
         return false;
    }
    else
    {
        for(size_t i = 0;i<rows;++i)
        {
            for(size_t j = 0;j<columns;++j)
            {
                if (matrix[i][j] != other[i][j]) return false;
            }
        }
    return true;
    }

}

bool Matrix::operator!=(const Matrix& other) const
{
    return !((*this) == other);
}

size_t Matrix::getRowsNumber() const
{
    return rows;
}

size_t Matrix::getColumnsNumber() const
{
    return columns;
}  

void Matrix::print() const
{
    for(size_t i = 0;i<rows;++i)
    {
        for(size_t j = 0;j<columns;++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix::~Matrix()
{
    for(size_t i = 0;i<rows;++i)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
}
