#include "Matrix.h"

#include <string>
#include <sstream>
#include <iomanip>

Matrix::Matrix(int _rows, int _columns) //J
{
	rows = _rows;
	columns = _columns;
	data.resize(_rows, vector<float>(_columns, 0));
}

Matrix::Matrix(std::ifstream& _in, int _rows, int _columns) //J
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

int Matrix::GetRows() const //J
{
	return rows;
}

int Matrix::GetColumns() const //J
{
	return columns;
}

void Matrix::SetData(vector<vector<float>>& _data) //J
{
	data = _data;
	rows = _data.size();
	if (_data.empty()) {
		columns = 0;
	}
	else {
		columns = _data[0].size();
	}
}

void Matrix::Print() //M
{
	// Figure out what size the largest cell will be
	int cellWidth = 0;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < columns; x++)
		{
			// Convert it to a string then get its width
			int currentCellWidth = ValueAsString(y, x).length();
			if (currentCellWidth > cellWidth) cellWidth = currentCellWidth;
		}
	}

	// If the cell width is small as then
	// give it some additional padding because
	// it looks heaps nicer
	if (cellWidth <= 2) cellWidth += 2;

	// pre-bake a section divider row thingy
	std::string rowDivider = "";
	for (int i = 0; i < columns; i++)
	{
		rowDivider += ("+" + std::string(cellWidth, '-'));
	}
	rowDivider += "+\n";

	// Loop over all the data and draw it
	std::string printContent = "";
	for (int y = 0; y < rows; y++)
	{
		// Add the divider
		printContent += rowDivider;

		// Add the actual data
		for (int x = 0; x < columns; x++)
		{
			// Measure the current number and 
			// calculate padding to ensure it 
			// fits in the middle of the cell
			int numberWidth = ValueAsString(y, x).length();
			int paddingLeft = (cellWidth - numberWidth) / 2;
			int paddingRight = cellWidth - (numberWidth + paddingLeft);

			// Draw everything
			printContent += (
				"|" +
				std::string(paddingLeft, ' ') +
				ValueAsString(y, x) +
				std::string(paddingRight, ' ')
			);
		}

		// add the end of the current row
		printContent += "|\n";
	}

	// Add the final end bottom bit thing
	printContent += rowDivider;
	
	// Draw the matrix
	std::cout << printContent;
}

float Matrix::Determinant() //M
{
	return 1;
}

Matrix Matrix::Transpose() //J
{
	Matrix transposeM(columns, rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			transposeM.data[j][i] = data[i][j];
		}
	}
	return transposeM;
}

Matrix Matrix::Inverse() //M
{
	return Matrix(1, 1);
}

Matrix Matrix::ScalarMultiply(float _scalar) //J
{
	Matrix scalarM(rows, columns);
	for (int i = 0; i < rows; i++) {\
		for (int j = 0; j < columns; j++) {
			scalarM.data[i][j] = data[i][j] * _scalar;
		}
	}
	return scalarM;
}

Matrix Matrix::Add(Matrix& _other) //J
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

Matrix Matrix::Subtract(Matrix& _other) //J
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

Matrix Matrix::Multiply(Matrix& _other) //J
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

Matrix Matrix::Identity(int _size) //J
{
	Matrix identityM(_size, _size);
	for (int i = 0; i < _size; i++) {
		identityM.data[i][i] = 1;
	}
	return identityM;
}

std::string Matrix::ValueAsString(int row, int column) //M
{
	// Ensure we use a valid coordinate thing
	if (row > rows || column > columns)
	{
		return "NaN";
	}

	// Chuck the float into the stream so that
	// we can shop down most of the .0000 rubbish
	std::ostringstream stream;
	stream << std::setprecision(5) << std::noshowpoint << std::defaultfloat << data[row][column];
	std::string output = stream.str();

	// Remove trailing zeros and also any leftover points (.)
	if (output.find('.') != std::string::npos)
	{
		// Loop through the string and remove unneeded characters
		while (!output.empty() && output.back() == '0') output.pop_back();
		if (!output.empty() && output.back() == '.') output.pop_back();
	}

	// Give back the full formatted float
	return output;
}

Matrix Matrix::ReadMatrix(ifstream& _in) //J
{
	//reads numbers until blank line
	vector<vector<float>> values;
	string line;

	while (getline(_in, line)) {
		if (line.empty()) {
			break;
		}
		stringstream stream(line);
		vector<float> row;
		float number;

		while (stream >> number) {
			row.push_back(number);
		}

		if (!row.empty()) {
			values.push_back(row);
		}
	}
	if (values.empty()) {
		return Matrix(0, 0);
	}

	//counts how many numbers per line
	int rows = values.size();
	int columns = values[0].size();

	//fills matrix
	Matrix result(values.size(), values[0].size());
	result.SetData(values);

	return result;
}

