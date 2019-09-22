#pragma once
#include "gz.h"

class Matrix {
public:
	Matrix();
	Matrix(int rol, int col, float value = 0);
	Matrix(GzMatrix matrix);
	Matrix(GzCoord vector);
	Matrix(GzCoord vector, float fourth);

	void InitEntries(int rol, int col, float value = 0);
	float** getData();
	float getData(int rol, int col);

	void toGzMatrix(GzMatrix matrix);
	void toGzCoord(GzCoord vector);
	float toFloat();
	Matrix& generateMatrixRotation(float u, float v, float w, float degree);
	Matrix& generateMatrixTranslation(float tx, float ty, float tz);
	Matrix& generateMatrixScale(float sx, float sy, float sz);
	Matrix& normalize();
	Matrix& transpose();

	Matrix& operator+(const Matrix& operand);
	Matrix& operator+(float operand);
	Matrix& operator-(Matrix& operand);
	Matrix& operator-(float operand);
	Matrix& operator*(Matrix& operand);
	Matrix& operator*(float operand);
	Matrix& operator/=(float operand);
	Matrix& CrossProduct(Matrix& operand);

private:
	int row;
	int col;
	float** data;
};