#include "StdAfx.h"
#include "rendMatrix.h"
#include <math.h>

#define PI (float) 3.14159265358979323846

Matrix::Matrix() {
}

Matrix::Matrix(int row, int col, float value) {
	InitEntries(row, col, 0);
}

Matrix::Matrix(GzMatrix matrix) {
	this->row = 4;
	this->col = 4;
	this->data = new float* [this->row];
	for (int i = 0; i < row; i++) {
		this->data[i] = new float[this->col];
		for (int j = 0; j < col; j++) {
			data[i][j] = matrix[i][j];
		}
	}
}

Matrix::Matrix(GzCoord vector) {
	this->row = 1;
	this->col = 3;
	this->data = new float* [this->row];
	for (int i = 0; i < row; i++) {
		this->data[i] = new float[this->row];
		for (int j = 0; j < col; j++) {
			data[i][j] = vector[j];
		}
	}
}

void Matrix::InitEntries(int row, int col, float value) {
	this->row = row;
	this->col = col;
	this->data = new float* [this->row];
	for (int i = 0; i < row; i++) {
		this->data[i] = new float[this->col];
		for (int j = 0; j < col; j++) {
			data[i][j] = 0;
		}
	}
}

void Matrix::toGzMatrix(GzMatrix matrix) {
	matrix[0][0] = data[0][0]; matrix[0][1] = data[0][1]; matrix[0][2] = data[0][2]; matrix[0][3] = data[0][3];
	matrix[1][0] = data[1][0]; matrix[1][1] = data[1][1]; matrix[1][2] = data[1][2]; matrix[1][3] = data[1][3];
	matrix[2][0] = data[2][0]; matrix[2][1] = data[2][1]; matrix[2][2] = data[2][2]; matrix[2][3] = data[2][3];
	matrix[3][0] = data[3][0]; matrix[3][1] = data[3][1]; matrix[3][2] = data[3][2]; matrix[3][3] = data[3][3];
}

void Matrix::toGzCoord(GzCoord vector) {
	vector[0] = data[0][0];
	vector[1] = data[0][1];
	vector[2] = data[0][2];
}

float Matrix::toFloat() {
	return data[0][0];
}

Matrix& Matrix::generateMatrixRotation(float u, float v, float w, float degree) {
	float radian = degree * PI / 180.0f;
	float rotVector[3] = { u, v, w };
	data[0][0] = rotVector[0] * rotVector[0] + (1.0f - rotVector[0] * rotVector[0]) * cos(radian);
	data[0][1] = rotVector[0] * rotVector[1] * (1.0f - cos(radian)) - rotVector[2] * sin(radian);
	data[0][2] = rotVector[0] * rotVector[2] * (1.0f - cos(radian)) + rotVector[1] * sin(radian);
	data[0][3] = 0.0f;
	data[1][0] = rotVector[0] * rotVector[1] * (1.0f - cos(radian)) + rotVector[2] * sin(radian);
	data[1][1] = rotVector[1] * rotVector[1] + (1.0f - rotVector[1] * rotVector[1]) * cos(radian);
	data[1][2] = rotVector[1] * rotVector[2] * (1.0f - cos(radian)) - rotVector[0] * sin(radian);
	data[1][3] = 0.0f;
	data[2][0] = rotVector[0] * rotVector[2] * (1.0f - cos(radian)) - rotVector[1] * sin(radian);
	data[2][1] = rotVector[1] * rotVector[2] * (1.0f - cos(radian)) + rotVector[0] * sin(radian);
	data[2][2] = rotVector[2] * rotVector[2] + (1.0f - rotVector[2] * rotVector[2]) * cos(radian);
	data[2][3] = 0.0f;
	data[3][0] = 0.0f;
	data[3][1] = 0.0f;
	data[3][2] = 0.0f;
	data[3][3] = 1.0f;
	return *this;
}

Matrix& Matrix::generateMatrixTranslation(float tx, float ty, float tz) {
	InitEntries(4, 4, 0);
	data[0][0] = 1.0f; data[0][1] = 0.0f; data[0][2] = 0.0f; data[0][3] = tx;
	data[1][0] = 0.0f; data[1][1] = 1.0f; data[1][2] = 0.0f; data[1][3] = ty;
	data[2][0] = 0.0f; data[2][1] = 0.0f; data[2][2] = 1.0f; data[2][3] = tz;
	data[3][0] = 0.0f; data[3][1] = 0.0f; data[3][2] = 0.0f; data[3][3] = 1.0f;
	return *this;
}

Matrix& Matrix::generateMatrixScale(float sx, float sy, float sz) {
	InitEntries(4, 4, 0);
	data[0][0] = sx;	data[0][1] = 0.0f;	data[0][2] = 0.0f;	data[0][3] = 0.0f;
	data[1][0] = 0.0f;	data[1][1] = sy;	data[1][2] = 0.0f;	data[1][3] = 0.0f;
	data[2][0] = 0.0f;	data[2][1] = 0.0f;	data[2][2] = sz;	data[2][3] = 0.0f;
	data[3][0] = 0.0f;	data[3][1] = 0.0f;	data[3][2] = 0.0f;	data[3][3] = 1.0f;
	return *this;
}

Matrix& Matrix::normalize() {
	if (row != 1 && col != 1) return *this;

	if (row == 1) {
		float divider(0);
		for (int i = 0; i < col; i++) divider += data[0][i] * data[0][i];
		for (int i = 0; i < col; i++) data[0][i] /= sqrtf(divider);
		return *this;
	}
	else if (col == 1) {
		float divider(0);
		for (int i = 0; i < row; i++) divider += data[i][0] * data[i][0];
		for (int i = 0; i < row; i++) data[i][0] /= sqrtf(divider);
		return *this;
	}
}

Matrix& Matrix::transpose() {
	static Matrix result(col, row);

	for (int i = 0; i < result.row; i++) {
		for (int j = 0; j < result.col; j++) {
			result.data[i][j] = data[j][i];
		}
	}

	return result;
}

Matrix& Matrix::operator+(const Matrix& operand) {
	if (operand.row != row || operand.col != col) return *this;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			data[i][j] += operand.data[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator+(float operand) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			data[i][j] += operand;
		}
	}
	return *this;
}

Matrix& Matrix::operator-(Matrix& operand) {
	if (operand.row != row || operand.col != col) return *this;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			data[i][j] -= operand.data[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-(float operand) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			data[i][j] -= operand;
		}
	}
	return *this;
}

Matrix& Matrix::operator*(Matrix& operand) {
	if (col != operand.row) return *this;

	Matrix result(row, operand.col);
	for (int i = 0; i < result.col; i++) {
		for (int j = 0; j < result.col; j++) {
			for (int k = 0; k < operand.row; k++) {
				result.data[i][j] += this->data[i][k] * operand.data[k][j];
			}
		}
	}
	
	InitEntries(row, operand.col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			data[i][j] = result.data[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*(float operand) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			data[i][j] *= operand;
		}
	}
	return *this;
}

Matrix& Matrix::CrossProduct(Matrix& operand) {
	float x = data[0][0], y = data[0][1], z = data[0][2];
	data[0][0] = y * operand.data[0][2] - z * operand.data[0][1];
	data[0][1] = z * operand.data[0][0] - x * operand.data[0][2];
	data[0][2] = x * operand.data[0][1] - y * operand.data[0][0];
	return *this;
}
