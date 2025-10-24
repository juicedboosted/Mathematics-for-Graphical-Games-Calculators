#include "Matrix.h"

#include <string>
#include <sstream>
#include <iomanip>

Matrix::Matrix(int _rows, int _columns) // J
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

bool Matrix::IsSquare() const
{
	return rows == columns;
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

float Matrix::GetDeterminant() //M
{
	// Only square matrixes can have a determinant
	// TODO: Print some sorta error message
	if (IsSquare() == false) 0.0f;

	// Check for if we have subdivided the matrix as much as possible
	if (Is2x2()) return GetDeterminantOf2x2Matrix(*this);

	float determinant = 0.0f;

	// Loop over every 'cell' in the first row
	for (int x = 0; x < columns; x++)
	{
		// Chop the matrix up into a smaller one
		Matrix subMatrix = RemoveRowAndColumn(0, x);

		// Figure if we need to plus or minus
		float sign = ((x % 2) == 0) ? 1.0f : -1.0f;

		// Add the current 'matrix' to the final value
		determinant += sign * data[0][x] * subMatrix.GetDeterminant();
	}

	return determinant;
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

float Matrix::GetDeterminantOf2x2Matrix(Matrix matrix)
{
	return (
		(matrix.data[0][0] * matrix.data[1][1]) -
		(matrix.data[1][0] * matrix.data[0][1])
	);
}

bool Matrix::Is2x2()
{
	return rows == 2 && columns == 2;
}

// Remove the provided row/column
// TODO: Make this public?
Matrix Matrix::RemoveRowAndColumn(int row, int column)
{
	// The new matrix will be one row and
	// one column smaller than the og
	Matrix matrix(rows - 1, columns - 1);

	// Loop over every cell in the og matrix and add
	// it to the new matrix if its not in the row
	// or column that we want removed
	int newY = 0;
	for (int y = 0; y < rows; y++)
	{
		// Skip the deleted row
		if (y == row) continue;
		
		int newX = 0;
		for (int x = 0; x < columns; x++)
		{
			// Skip the deleted column
			if (x == column) continue;

			// Set the new data
			matrix.data[newY][newX] = data[y][x];

			// Update the new position since it
			// won't be a 1:1 mapping anymore
			// (missing the row/column)
			newX++;
		}
		newY++;
	}

	return matrix;
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