#include "stdafx.h"
#include "rendMatrixOperator.h"

#define PI (float) 3.14159265358979323846

MatrixOperator::MatrixOperator() {
	Reset();
}

void MatrixOperator::Reset() {
	result[0][0] = 0.0f; result[0][1] = 0.0f; result[0][2] = 0.0f; result[0][3] = 0.0f;
	result[1][0] = 0.0f; result[1][1] = 0.0f; result[1][2] = 0.0f; result[1][3] = 0.0f;
	result[2][0] = 0.0f; result[2][1] = 0.0f; result[2][2] = 0.0f; result[2][3] = 0.0f;
	result[3][0] = 0.0f; result[3][1] = 0.0f; result[3][2] = 0.0f; result[3][3] = 0.0f;
}

void MatrixOperator::GetResult(GzMatrix des) {
	des[0][0] = result[0][0]; des[0][1] = result[0][1]; des[0][2] = result[0][2]; des[0][3] = result[0][3];
	des[1][0] = result[1][0]; des[1][1] = result[1][1]; des[1][2] = result[1][2]; des[1][3] = result[1][3];
	des[2][0] = result[2][0]; des[2][1] = result[2][1]; des[2][2] = result[2][2]; des[2][3] = result[2][3];
	des[3][0] = result[3][0]; des[3][1] = result[3][1]; des[3][2] = result[3][2]; des[3][3] = result[3][3];
}

void MatrixOperator::GenerateMatrixRotation(float u, float v, float w, float degree) {
	float radian = degree * PI / 180.0f;
	float rotVector[3] = { u, v, w };
	result[0][0] = rotVector[0] * rotVector[0] + (1.0f - rotVector[0] * rotVector[0]) * cos(radian);
	result[0][1] = rotVector[0] * rotVector[1] * (1.0f - cos(radian)) - rotVector[2] * sin(radian);
	result[0][2] = rotVector[0] * rotVector[2] * (1.0f - cos(radian)) + rotVector[1] * sin(radian);
	result[0][3] = 0.0f;
	result[1][0] = rotVector[0] * rotVector[1] * (1.0f - cos(radian)) + rotVector[2] * sin(radian);
	result[1][1] = rotVector[1] * rotVector[1] + (1.0f - rotVector[1] * rotVector[1]) * cos(radian);
	result[1][2] = rotVector[1] * rotVector[2] * (1.0f - cos(radian)) - rotVector[0] * sin(radian);
	result[1][3] = 0.0f;
	result[2][0] = rotVector[0] * rotVector[2] * (1.0f - cos(radian)) - rotVector[1] * sin(radian);
	result[2][1] = rotVector[1] * rotVector[2] * (1.0f - cos(radian)) + rotVector[0] * sin(radian);
	result[2][2] = rotVector[2] * rotVector[2] + (1.0f - rotVector[2] * rotVector[2]) * cos(radian);
	result[2][3] = 0.0f;
	result[3][0] = 0.0f;
	result[3][1] = 0.0f;
	result[3][2] = 0.0f;
	result[3][3] = 1.0f;
}

void MatrixOperator::GenerateMatrixTransformation(float tx, float ty, float tz) {
	result[0][0] = 1.0f;
	result[0][1] = 0.0f;
	result[0][2] = 0.0f;
	result[0][3] = tx;
	result[1][0] = 0.0f;
	result[1][1] = 1.0f;
	result[1][2] = 0.0f;
	result[1][3] = ty;
	result[2][0] = 0.0f;
	result[2][1] = 0.0f;
	result[2][2] = 1.0f;
	result[2][3] = tz;
	result[3][0] = 0.0f;
	result[3][1] = 0.0f;
	result[3][2] = 0.0f;
	result[3][3] = 1.0f;
}

void MatrixOperator::GenerateMatrixScale(float sx, float sy, float sz) {
	result[0][0] = sx;
	result[0][1] = 0.0f;
	result[0][2] = 0.0f;
	result[0][3] = 0.0f;
	result[1][0] = 0.0f;
	result[1][1] = sy;
	result[1][2] = 0.0f;
	result[1][3] = 0.0f;
	result[2][0] = 0.0f;
	result[2][1] = 0.0f;
	result[2][2] = sz;
	result[2][3] = 0.0f;
	result[3][0] = 0.0f;
	result[3][1] = 0.0f;
	result[3][2] = 0.0f;
	result[3][3] = 1.0f;
}

void MatrixOperator::MatrixCopy(GzMatrix source, GzMatrix destination) {
	destination[0][0] = source[0][0]; destination[0][1] = source[0][1]; destination[0][2] = source[0][2]; destination[0][3] = source[0][3];
	destination[1][0] = source[1][0]; destination[1][1] = source[1][1]; destination[1][2] = source[1][2]; destination[1][3] = source[1][3];
	destination[2][0] = source[2][0]; destination[2][1] = source[2][1]; destination[2][2] = source[2][2]; destination[2][3] = source[2][3];
	destination[3][0] = source[3][0]; destination[3][1] = source[3][1]; destination[3][2] = source[3][2]; destination[3][3] = source[3][3];
}

void MatrixOperator::MatrixAdd(GzMatrix operand1, GzMatrix operand2) {
	Reset();
	result[0][0] = operand1[0][0] + operand2[0][0]; result[0][1] = operand1[0][1] + operand2[0][1]; result[0][2] = operand1[0][2] + operand2[0][2]; result[0][3] = operand1[0][3] + operand2[0][3];
	result[1][0] = operand1[1][0] + operand2[1][0]; result[1][1] = operand1[1][1] + operand2[1][1]; result[1][2] = operand1[1][2] + operand2[1][2]; result[1][3] = operand1[1][3] + operand2[1][3];
	result[2][0] = operand1[2][0] + operand2[2][0]; result[2][1] = operand1[2][1] + operand2[2][1]; result[2][2] = operand1[2][2] + operand2[2][2]; result[2][3] = operand1[2][3] + operand2[2][3];
	result[3][0] = operand1[3][0] + operand2[3][0]; result[3][1] = operand1[3][1] + operand2[3][1]; result[3][2] = operand1[3][2] + operand2[3][2]; result[3][3] = operand1[3][3] + operand2[3][3];
}

void MatrixOperator::MatrixMul(GzMatrix operand1, GzMatrix operand2) {
	Reset();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = 0.0f;
			for (int k = 0; k < 4; k++) {
				result[i][j] += operand1[i][k] * operand2[k][j];
			}
		}
	}
}
