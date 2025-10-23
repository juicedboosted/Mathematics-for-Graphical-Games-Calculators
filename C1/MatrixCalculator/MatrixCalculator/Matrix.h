#pragma once
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Matrix //J
{
public:
	Matrix(int _rows, int _columns);
	Matrix(std::ifstream& _in, int _rows, int _columns);

	//get
	int GetRows() const;
	int GetColumns() const;
	bool IsSquare() const;

	//display
	void Print();

	//operations
	float Determinant();
	Matrix Transpose();
	Matrix Inverse();
	Matrix ScalarMultiply(float _scalar);
	Matrix Add(Matrix& _other);
	Matrix Subtract(Matrix& _other);
	Matrix Multiply(Matrix& _other);
	Matrix Identity(int _size);

	//read file
	static Matrix ReadMatrix(ifstream& _in);
	void SetData(vector<vector<float>>& _data);

private:
	int rows;
	int columns;

	vector<vector<float>> data;

	std::string ValueAsString(int row, int column); //M
	int GetSign(int row, int column); //M
	Matrix RemoveRowAndColumn(int row, int column); //M
};

