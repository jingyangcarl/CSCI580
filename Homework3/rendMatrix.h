#pragma once
#include "gz.h"

class Matrix {

	Matrix();
	Matrix(GzMatrix matrix);
	Matrix(GzCoord vector);

	Matrix& operator+(Matrix& operand);
	Matrix& operator+(float& operand);
	Matrix& operator-(Matrix& operand);
	Matrix& operator-(float& operand);
	Matrix& operator*(Matrix& operand);

private:
	int row;
	int col;
	float** data;
};