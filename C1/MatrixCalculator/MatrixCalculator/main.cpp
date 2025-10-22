#include "Matrix.h"

using namespace std;

// Matrix Calculator made by Jessica/Jessie Marie Harvey-Cross (J) and Maximillian McCarthy (M)
// reads txt file (Matrix A, Matrix B, and a scalar)
// performs the following operations: |A|, A^(T), A^(-1), A * s, A + B, A - B, A * B, B * A, I(identity matrix)

int main() //J
{
	//-- edit this to change what txt file is read -- //
	ifstream file("Text/Matrix.txt");
	//-- ----------------------------------------- -- //
	if (!file.is_open()) {
		cerr << "Error: Could not open file. \n";
		return 0;
	}

	Matrix A = Matrix::ReadMatrix(file);
	Matrix B = Matrix::ReadMatrix(file);
	float scalar;
	file >> scalar;

	cout << "Matrix A:\n";
	A.Print();
	cout << "\n";
	cout << "Matrix B:\n";
	B.Print();
	cout << "\n";
	cout << "Scalar: " << scalar << "\n\n";
	cout << "\n";

	cout << "Determinant of A: " << A.Determinant() << "\n\n";
	cout << "\n";
	cout << "A Transposed:\n";
	A.Transpose().Print();
	cout << "\n";
	
	//add inverse

	cout << "A * Scalar:\n";
	A.ScalarMultiply(scalar).Print();
	cout << "\n";
	if (A.GetRows() == B.GetRows() && A.GetColumns() == B.GetColumns()) {
		cout << "A + B:\n";
		A.Add(B).Print();
		cout << "\n";

		cout << "A - B:\n";
		A.Subtract(B).Print();
		cout << "\n";
	}
	else {
		cout << "Can't add or subtract A and B due to size mismatch.\n\n";
	}

	if (A.GetColumns() == B.GetRows()) {
		cout << "A * B:\n";
		A.Multiply(B).Print();
		cout << "\n";
	}
	else {
		cout << "Can't multiply A and B due to incompatible dimensions.\n\n";
	}

	if (B.GetColumns() == A.GetRows()) {
		cout << "B * A:\n";
		B.Multiply(A).Print();
		cout << "\n";
	}
	else {
		cout << "Can't multiply B and A due to incompatible dimensions.\n\n";
	}

	cout << "Identity Matrix: (" << A.GetRows() << "x" << A.GetRows() << "):\n";
	A.Identity(A.GetRows()).Print();
	cout << "\n";

	return 0;

}


