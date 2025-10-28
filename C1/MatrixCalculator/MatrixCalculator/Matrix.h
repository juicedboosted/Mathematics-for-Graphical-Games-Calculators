#pragma once
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Matrix //J
{
public:
	Matrix(int _rows = 0, int _columns = 0); //J
	Matrix(std::ifstream& _in, int _rows, int _columns); //J

	//get
	int GetRows() const;
	int GetColumns() const;
	bool IsSquare() const;

	//display
	void Print(); //M

	//operations
	float GetDeterminant(); //M
	Matrix Transpose(); //J
	Matrix Inverse(); //M
	Matrix ScalarMultiply(float _scalar); //J
	Matrix Add(Matrix& _other); //J
	Matrix Subtract(Matrix& _other); //J
	Matrix Multiply(Matrix& _other); //J
	Matrix Identity(int _size); //J

	//read file
	static Matrix ReadMatrix(ifstream& _in); //J
	void SetData(vector<vector<float>>& _data); //J

private:
	int rows;
	int columns;

	vector<vector<float>> data;

	std::string ValueAsString(int row, int column); //M

	static float GetDeterminantOf2x2Matrix(Matrix matrix); //M
	bool Is2x2();

	Matrix RemoveRowAndColumn(int row, int column); //M
	float GetSign(int row, int column);
};
