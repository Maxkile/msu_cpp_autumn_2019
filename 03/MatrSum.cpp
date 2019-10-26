#include "MatrSum.hpp"

Matrix::Row::Row(int rowNumber,int* row):rowNumber(rowNumber),row(row){}

int& Matrix::Row::operator[](int j )
{
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
    for (int i = 0; i<rows;++i)
    {
        matrix[i] = new int[columns];//int array
    }
}

Matrix::Matrix(const int rows,const int columns):rows(rows),columns(columns)
{
    m_create();
}

Matrix::Matrix(const int size):rows(size),columns(size)
{
    m_create();
}

Matrix::Matrix(Matrix& source):rows(source.rows),columns(source.columns)
{
    m_create();
    for(int i = 0;i<source.rows;++i)
    {
        for(int j = 0;j<source.columns;++j)
        {
            matrix[i][j] = source[i][j];
        }
    }
}

Matrix::Row Matrix::operator[](const int i)
{
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
    for(int i = 0;i<rows;++i)
    {
        for(int j = 0;j<columns;++j)
        {
            matrix[i][j] = number;
        }
    }
    return (*this);
}

Matrix& Matrix::operator*=(const int number)
{
    for(int i = 0;i<rows;++i)
    {
        for(int j = 0;j<columns;++j)
        {
            matrix[i][j] *= number;
        }
    }
    return (*this);
}

bool Matrix::operator==(Matrix& other)
{
    if ((other.getColumnsNumber() != columns) || (other.getRowsNumber() != rows)) return false;
    else
    {
        for(int i = 0;i<rows;++i)
        {
            for(int j = 0;j<columns;++j)
            {
                if (matrix[i][j] != other[i][j]) return false;
            }
        }
    return true;
    }

}

bool Matrix::operator!=(Matrix& other)
{
    return !((*this) == other);
}

int Matrix::getRowsNumber() const
{
    return rows;
}

int Matrix::getColumnsNumber() const
{
    return columns;
}  

void Matrix::print()
{
    for(int i = 0;i<rows;++i)
    {
        for(int j = 0;j<columns;++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix::~Matrix()
{
    for(int i = 0;i<rows;++i)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
}
