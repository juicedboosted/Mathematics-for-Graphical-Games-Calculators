#include "Matrix.h"

Matrix::Matrix(int _rows, int _columns)
{
    rows = _rows;
    columns = _columns;
    data.resize(_rows, vector<float>(_columns, 0));
}

Matrix::Matrix(std::ifstream& _in, int _rows, int _columns)
{
    rows = _rows;
    columns = _columns;
    data.resize(_rows, vector<float>(_columns));
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            _in >> data[i][j];
        }
    }
}

int Matrix::GetRows() const
{
    return rows;
}

int Matrix::GetColumns() const
{
    return columns;
}
//u can do this one max :3
void Matrix::Print()
{

}
//u can do this one max :3
float Matrix::Determinant()
{
    
}

Matrix Matrix::Transpose()
{
    Matrix transposeM(columns, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            transposeM.data[j][i] = data[i][j];
        }
    }
    return transposeM;
}
//u can do this one max :3
Matrix Matrix::Inverse()
{
    //return Matrix();
}

Matrix Matrix::ScalarMultiply(float _scalar)
{
    Matrix scalarM(rows, columns);
    for (int i = 0; i < rows; i++) {\
        for (int j = 0; j < columns; j++) {
            scalarM.data[i][j] = data[i][j] * _scalar;
        }
    }
    return scalarM;
}

Matrix Matrix::Add(Matrix& _other)
{
    //reminder: setup error check
    Matrix addM(rows, columns);
    for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                addM.data[i][j] = data[i][j] + _other.data[i][j];
            }
    }
    return addM;
}

Matrix Matrix::Subtract(Matrix& _other)
{
    //reminder: setup error check
    Matrix subtractM(rows, columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            subtractM.data[i][j] = data[i][j] - _other.data[i][j];
        }
    }
    return subtractM;
}

Matrix Matrix::Multiply(Matrix& _other)
{
    //reminder: setup error check
    Matrix multiplyM(rows, _other.columns);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < _other.columns; j++) {
            for (int k = 0; k < columns; k++) {
                multiplyM.data[i][j] += data[i][k] * _other.data[k][j];
            }
        }
    }
    return multiplyM;
}

Matrix Matrix::Identity(int _size)
{
    Matrix identityM(_size, _size);
    for (int i = 0; i < _size; i++) {
        identityM.data[i][i] = 1;
    }
    return identityM;
}
