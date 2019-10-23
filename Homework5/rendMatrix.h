#pragma once
#include "gz.h"

class Matrix {
public:
	Matrix();
	Matrix(int row, int col, float value = 0);
	Matrix(GzMatrix matrix);
	Matrix(const GzCoord& vector);
	Matrix(GzCoord vector, float fourth);

	void InitEntries(int row, int col, float value = 0);

	// These functions are used to copy data out;
	float** getData() const;
	float getData(const int row, const int col) const;
	void toGzMatrix(GzMatrix matrix);
	void toGzCoord(GzCoord vector, bool normalize = false);
	void toGzColor(GzColor color);
	float toFloat();

	// These functions are used to generate a transformation matrix;
	static Matrix& generateMatrixRotation(const float u, const float v, const float w, const float degree);
	static Matrix& generateMatrixTranslation(const float tx, const float ty, const float tz);
	static Matrix& generateMatrixScale(const float sx, const float sy, const float sz);
	static Matrix& generateIdentity(int row);

	// These functions are used to apply matrix operations;
	Matrix& operator+(const Matrix& operand);
	Matrix& operator+=(const Matrix& operand);
	Matrix& operator+(const float operand);
	Matrix& operator-();
	Matrix& operator-(const Matrix& operand);
	Matrix& operator-(const float operand);
	Matrix& operator*(const Matrix& operand);
	Matrix& operator*=(const Matrix& operand);
	Matrix& operator*=(const float operand);
	Matrix& operator*(const float operand);
	Matrix& operator/=(const float operand);
	Matrix& CrossProduct(const Matrix& operand);
	Matrix& ParallelProduct(const Matrix& operand);
	Matrix& normalize();
	Matrix& transpose();

private:
	int row;
	int col;
	float** data;
};