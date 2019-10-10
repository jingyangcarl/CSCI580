#include "StdAfx.h"
#include "rendMatrix.h"
#include <math.h>

#define PI (float) 3.14159265358979323846

/*
Description:
This function is a constructor;
Input:
@ void parameter: void;
Output:
@ Matrix returnValue: a Matrix;
*/
Matrix::Matrix() {
}

/*
Description:
This function is a constructor;
Input:
@ int row: a row number;
@ int col: a column number;
@ float value: a default entry value;
Output:
@ Matrix returnValue: a Matrix;
*/
Matrix::Matrix(int row, int col, float value) {
	InitEntries(row, col, 0);
}

/*
Description:
This function is a constructor;
Input:
@ GzMatrix: a GzMatrix;
Output:
@ Matrix returnValue: a Matrix;
*/
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

/*
Description:
This function is a constructor;
Input:
@ GzCoord: a column vector;
Output:
@ Matrix returnValue: a Matrix;
*/
Matrix::Matrix(GzCoord vector) {
	this->row = 1;
	this->col = 3;
	this->data = new float* [this->row];
	for (int i = 0; i < row; i++) {
		this->data[i] = new float[this->col];
		for (int j = 0; j < col; j++) {
			data[i][j] = vector[j];
		}
	}
}

/*
Description:
This function is a constructor;
Input:
@ GzCoord: a column vector;
@ float fourth: a fourth value added after the column vector;
Output:
@ Matrix returnValue: a Matrix;
*/
Matrix::Matrix(GzCoord vector, float fourth) {
	this->row = 1;
	this->col = 4;
	this->data = new float* [this->row];
	this->data[0] = new float[this->col];
	for (int j = 0; j < col - 1; j++) {
		data[0][j] = vector[j];
	}
	this->data[0][this->col - 1] = fourth;
}

/*
Description:
This function is used to initialize all entries to a given value;
Input:
@ int row: a row number;
@ int col: a column number;
@ float value: a default entry value;
Output:
@ void returnValue: void;
*/
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

/*
Description:
This function is used to visit matrix entires;
Input:
@ void parameter: void;
Output:
@ float** returnValue: matrix entires;
*/
float** Matrix::getData() const {
	return data;
}

/*
Description:
This function is used to visit matrix entry at given location;
Input:
@ const int row: a row number;
@ const int col: a column number;
Output:
@ float returnValue: matrix entry at given location;
*/
float Matrix::getData(const int row, const int col) const {
	if (row >= this->row && row < 0) return -1;
	if (col >= this->col && col < 0) return -1;

	return this->data[row][col];
}

/*
Description:
This function is used to copy data entries to a GzMatrix, if the matrix size is less than GzMatrix (4 by 4) return nothing;
Input:
@ GzMatrix matrix: an empty GzMatrix;
Output:
@ GzMatrix matrix: a filled GzMatrix;
*/
void Matrix::toGzMatrix(GzMatrix matrix) {
	if (row < 4) return;
	if (col < 4) return;
	matrix[0][0] = data[0][0]; matrix[0][1] = data[0][1]; matrix[0][2] = data[0][2]; matrix[0][3] = data[0][3];
	matrix[1][0] = data[1][0]; matrix[1][1] = data[1][1]; matrix[1][2] = data[1][2]; matrix[1][3] = data[1][3];
	matrix[2][0] = data[2][0]; matrix[2][1] = data[2][1]; matrix[2][2] = data[2][2]; matrix[2][3] = data[2][3];
	matrix[3][0] = data[3][0]; matrix[3][1] = data[3][1]; matrix[3][2] = data[3][2]; matrix[3][3] = data[3][3];
}

/*
Description:
This function is used to copy data entries to a GzCoord, if the matrix size is less than GzCoord (1 by 3) return nothing;
Input:
@ GzCoord vector: an empty GzCoord;
Output:
@ GzCoord vector: a filled GzCoord;
*/
void Matrix::toGzCoord(GzCoord vector, bool normalize) {
	if (row < 1) return;
	if (col < 3) return;
	if (normalize) {
		float divider(0);
		for (int i = 0; i < col; i++) divider += data[0][i] * data[0][i];
		for (int i = 0; i < col; i++) vector[i] = data[0][i] / sqrt(divider);
	}
	else {
		vector[0] = data[0][0];
		vector[1] = data[0][1];
		vector[2] = data[0][2];
	}
}

/*
Description:
This function is used to copy data entries to a GzColor, if the matrix size is less than GzCoord (1 by 3) return nothing;
Input:
@ GzCoord vector: an empty GzCoord;
Output:
@ GzCoord vector: a filled GzCoord;
*/
void Matrix::toGzColor(GzColor color) {
	if (row < 1) return;
	if (col < 3) return;
	color[0] = data[0][0];
	color[1] = data[0][1];
	color[2] = data[0][2];
}

/*
Description:
This function is used to return the very first entry;
Input:
@ void parameter: void;
Output:
@ float returnValue: the first entry;
*/
float Matrix::toFloat() {
	return data[0][0];
}

/*
Description:
This static function is used to generate a rotation matrix around a given rotation central vector and rotation angle, the result will saved in the result matrix;
Input:
@ float u: x coordination of the rotation vector;
@ float v: y coordination of the rotation vector;
@ float w: z coordination of the rotation vector;
@ float degree: rotation degree around the rotation vector;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::generateMatrixRotation(const float u, const float v, const float w, const float degree) {
	Matrix* result = new Matrix(4, 4);
	float radian = degree * PI / 180.0f;
	float rotVector[3] = { u, v, w };
	result->data[0][0] = rotVector[0] * rotVector[0] + (1.0f - rotVector[0] * rotVector[0]) * cos(radian);
	result->data[0][1] = rotVector[0] * rotVector[1] * (1.0f - cos(radian)) - rotVector[2] * sin(radian);
	result->data[0][2] = rotVector[0] * rotVector[2] * (1.0f - cos(radian)) + rotVector[1] * sin(radian);
	result->data[0][3] = 0.0f;
	result->data[1][0] = rotVector[0] * rotVector[1] * (1.0f - cos(radian)) + rotVector[2] * sin(radian);
	result->data[1][1] = rotVector[1] * rotVector[1] + (1.0f - rotVector[1] * rotVector[1]) * cos(radian);
	result->data[1][2] = rotVector[1] * rotVector[2] * (1.0f - cos(radian)) - rotVector[0] * sin(radian);
	result->data[1][3] = 0.0f;
	result->data[2][0] = rotVector[0] * rotVector[2] * (1.0f - cos(radian)) - rotVector[1] * sin(radian);
	result->data[2][1] = rotVector[1] * rotVector[2] * (1.0f - cos(radian)) + rotVector[0] * sin(radian);
	result->data[2][2] = rotVector[2] * rotVector[2] + (1.0f - rotVector[2] * rotVector[2]) * cos(radian);
	result->data[2][3] = 0.0f;
	result->data[3][0] = 0.0f;
	result->data[3][1] = 0.0f;
	result->data[3][2] = 0.0f;
	result->data[3][3] = 1.0f;
	return *result;
}

/*
Description:
This static function is used to generate a translation matrix, the result will be saved in the result matrix;
Input:
@ float tx: x coordination of the translation matrix;
@ float ty: y coordination of the translation matrix;
@ float tz: z coordination of the translation matrix;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::generateMatrixTranslation(const float tx, const float ty, const float tz) {
	Matrix* result = new Matrix(4, 4);
	result->data[0][0] = 1.0f; result->data[0][1] = 0.0f; result->data[0][2] = 0.0f; result->data[0][3] = tx;
	result->data[1][0] = 0.0f; result->data[1][1] = 1.0f; result->data[1][2] = 0.0f; result->data[1][3] = ty;
	result->data[2][0] = 0.0f; result->data[2][1] = 0.0f; result->data[2][2] = 1.0f; result->data[2][3] = tz;
	result->data[3][0] = 0.0f; result->data[3][1] = 0.0f; result->data[3][2] = 0.0f; result->data[3][3] = 1.0f;
	return *result;
}

/*
Description:
This static function is used to generate a scale matrix, the result will be saved in the result matrix;
Input:
@ float sx: x coordination of the translation matrix;
@ float sy: y coordination of the translation matrix;
@ float sz: z coordination of the translation matrix;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::generateMatrixScale(const float sx, const float sy, const float sz) {
	Matrix* result = new Matrix(4, 4);
	result->data[0][0] = sx;	result->data[0][1] = 0.0f;	result->data[0][2] = 0.0f;	result->data[0][3] = 0.0f;
	result->data[1][0] = 0.0f;	result->data[1][1] = sy;	result->data[1][2] = 0.0f;	result->data[1][3] = 0.0f;
	result->data[2][0] = 0.0f;	result->data[2][1] = 0.0f;	result->data[2][2] = sz;	result->data[2][3] = 0.0f;
	result->data[3][0] = 0.0f;	result->data[3][1] = 0.0f;	result->data[3][2] = 0.0f;	result->data[3][3] = 1.0f;
	return *result;
}

/*
Description:
This function is used to generate a square identity matrix;
Input:
@ int row: row number / column number;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::generateIdentity(int row) {
	Matrix* result = new Matrix(row, row);
	for (int i = 0; i < row; i++) {
		result->data[i][i] = 1.0f;
	}
	return *result;
}

/*
Description:
This function is a overload of operator+ with a Matrix;
Input:
@ const Matrix& operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator+(const Matrix& operand) {
	if (operand.row != row || operand.col != col) return *this;

	Matrix* result = new Matrix(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result->data[i][j] = this->data[i][j] + operand.data[i][j];
		}
	}
	return *result;
}

/*
Description:
This function is a overload of operator+= with a Matrix;
Input:
@ const Matrix& operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator+=(const Matrix& operand) {
	if (operand.row != row || operand.col != col) return *this;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			this->data[i][j] += operand.data[i][j];
		}
	}
	return *this;
}

/*
Description:
This function is a overload of operator+ with a float number;
Input:
@ const float operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator+(const float operand) {
	Matrix* result = new Matrix(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result->data[i][j] = this->data[i][j] + operand;
		}
	}
	return *result;
}

/*
Description:
This function is a overload of unary operator-;
Input:
@ void parameter: void;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator-() {
	Matrix* result = new Matrix(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result->data[i][j] = -this->data[i][j];
		}
	}
	return *result;
}

/*
Description:
This function is a overload of operator- with a Matrix;
Input:
@ const Matrix& operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator-(const Matrix& operand) {
	if (operand.row != row || operand.col != col) return *this;

	Matrix* result = new Matrix(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result->data[i][j] = this->data[i][j] - operand.data[i][j];
		}
	}
	return *result;
}

/*
Description:
This function is a overload of operator- with a float number;
Input:
@ const float operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator-(const float operand) {
	Matrix* result = new Matrix(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result->data[i][j] = this->data[i][j] - operand;
		}
	}
	return *result;
}

/*
Description:
This function is a overload of operator* with a Matrix;
Input:
@ const Matrix& operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator*(const Matrix& operand) {
	if (col != operand.row) return *this;

	Matrix* result = new Matrix(row, operand.col);
	for (int i = 0; i < result->row; i++) {
		for (int j = 0; j < result->col; j++) {
			for (int k = 0; k < operand.row; k++) {
				result->data[i][j] += this->data[i][k] * operand.data[k][j];
			}
		}
	}
	return *result;
}

/*
Description:
This function is a overload of operator*= with a Matrix;
Input:
@ const Matrix& operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator*=(const Matrix& operand) {
	if (col != operand.row) return *this;

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			float value(0);
			for (int k = 0; k < operand.row; k++) {
				value += this->data[i][k] * operand.data[k][j];
			}
			this->data[i][j] = value;
		}
	}
	return *this;
}

/*
Description:
This function is a overload of operator*= with a float number;
Input:
@ const Matrix& operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator*=(const float operand) {
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			this->data[i][j] *= operand;
		}
	}
	return *this;
}

/*
Description:
This function is a overload of operator* with a float number;
Input:
@ const float operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator*(const float operand) {
	Matrix* result = new Matrix(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result->data[i][j] = this->data[i][j] * operand;
		}
	}
	return *result;
}

/*
Description:
This function is a overload of operator/= with a float number;
Input:
@ const float operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::operator/=(const float operand) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			data[i][j] /= operand;
		}
	}
	return *this;
}

/*
Description:
This function is used to calculate the cross product with another Matrix;
Input:
@ const Matrix& operand: a left hand operand;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::CrossProduct(const Matrix& operand) {
	Matrix* result = new Matrix(row, col);
	float x = data[0][0], y = data[0][1], z = data[0][2];
	result->data[0][0] = y * operand.data[0][2] - z * operand.data[0][1];
	result->data[0][1] = z * operand.data[0][0] - x * operand.data[0][2];
	result->data[0][2] = x * operand.data[0][1] - y * operand.data[0][0];
	return *result;
}

/*
Description:
This function is used to normalize the Matrix;
Input:
@ void parameter: void;
Output:
@ Matrix& returnValue: a reference to the result;
*/
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

/*
Description:
This function is used to transpose the Matrix;
Input:
@ void parameter: void;
Output:
@ Matrix& returnValue: a reference to the result;
*/
Matrix& Matrix::transpose() {
	Matrix* result = new Matrix(col, row);
	for (int i = 0; i < result->row; i++) {
		for (int j = 0; j < result->col; j++) {
			result->data[i][j] = data[j][i];
		}
	}

	return *result;
}