#include "Matrix.h"

using namespace std;

// Matrix Calculator made by Jessica/Jessie Marie Harvey-Cross (J) and Maximillian McCarthy (M)
// reads txt file (Matrix A (4x4), Matrix B (4x4), and a scalar)
// performs the following operations: |A|, A^(T), A^(-1), A * s, A + B, A - B, A * B, B * A, I(identity matrix)

int main() 
{
	ifstream file("Text/Matrix.txt");
	//reminder: setup error check

	Matrix A(file, 4, 4);
	Matrix B(file, 4, 4);
	int scalar;
	file >> scalar;

	cout << "Matrix A:\n";
	A.Print();
	cout << "Matrix B:\n";
	B.Print();
	cout << "Scalar: " << scalar << "\n\n";

	cout << "Determinant of A: " << A.GetDeterminant() << "\n\n";
	cout << "A Transposed:\n";
	A.Transpose().Print();
	
	A.Inverse().Print();

	cout << "A * Scalar:\n";
	A.ScalarMultiply(scalar).Print();
	cout << "A + B:\n";
	A.Add(B).Print();
	cout << "A - B:\n";
	A.Subtract(B).Print();
	cout << "A * B:\n";
	A.Multiply(B).Print();
	cout << "B * A:\n";
	B.Multiply(A).Print();
	cout << "Identity Matrix:\n";
	A.Identity(A.GetRows()).Print();

	return 0;

}


