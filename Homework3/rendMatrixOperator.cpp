#include "stdafx.h"
#include "rendMatrixOperator.h"

#define PI (float) 3.14159265358979323846

MatrixOperator::MatrixOperator() {
	ResultReset();
}

GzMatrix* MatrixOperator::GetResult() {
	
}

void MatrixOperator::ResultReset() {
	result[0][0] = 0.0f; result[0][1] = 0.0f; result[0][2] = 0.0f; result[0][3] = 0.0f;
	result[1][0] = 0.0f; result[1][1] = 0.0f; result[1][2] = 0.0f; result[1][3] = 0.0f;
	result[2][0] = 0.0f; result[2][1] = 0.0f; result[2][2] = 0.0f; result[2][3] = 0.0f;
	result[3][0] = 0.0f; result[3][1] = 0.0f; result[3][2] = 0.0f; result[3][3] = 0.0f;
}

GzMatrix* MatrixOperator::MatrixAdd(GzMatrix& operand1, GzMatrix& operand2) {
	ResultReset();
	result[0][0] = operand1[0][0] + operand2[0][0]; result[0][1] = operand1[0][1] + operand2[0][1]; result[0][2] = operand1[0][2] + operand2[0][2]; result[0][3] = operand1[0][3] + operand2[0][3];
	result[1][0] = operand1[1][0] + operand2[1][0]; result[1][1] = operand1[1][1] + operand2[1][1]; result[1][2] = operand1[1][2] + operand2[1][2]; result[1][3] = operand1[1][3] + operand2[1][3];
	result[2][0] = operand1[2][0] + operand2[2][0]; result[2][1] = operand1[2][1] + operand2[2][1]; result[2][2] = operand1[2][2] + operand2[2][2]; result[2][3] = operand1[2][3] + operand2[2][3];
	result[3][0] = operand1[3][0] + operand2[3][0]; result[3][1] = operand1[3][1] + operand2[3][1]; result[3][2] = operand1[3][2] + operand2[3][2]; result[3][3] = operand1[3][3] + operand2[3][3];
	return &result;
}

GzMatrix* MatrixOperator::MatrixMul(GzMatrix& operand1, GzMatrix& operand2) {
	ResultReset();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i][j] = 0.0f;
			for (int k = 0; k < 4; k++) {
				result[i][j] += operand1[i][k] * operand2[k][j];
			}
		}
	}
	return &result;
}

GzMatrix* MatrixOperator::GenerateMatrixRotation(float u, float v, float w, float angle) {
	float radian = angle * PI / 180.0f;
	float rotVector[3] = { u, v, w };
	result[0][0] = rotVector[0] * rotVector[0] + (1 - rotVector[0] * rotVector[0]) * cos(radian);
	result[0][1] = rotVector[0] * rotVector[1] * (1 - cos(radian)) - rotVector[2] * sin(radian);
	result[0][2] = rotVector[0] * rotVector[2] * (1 - cos(radian)) + rotVector[1] * sin(radian);
	result[0][3] = 0.0f;
	result[1][0] = rotVector[0] * rotVector[1] * (1 - cos(radian)) + rotVector[2] * sin(radian);
	result[1][1] = rotVector[1] * rotVector[1] + (1 - rotVector[1] * rotVector[1]) * cos(radian);
	result[1][2] = rotVector[1] * rotVector[2] * (1 - cos(radian)) - rotVector[0] * sin(radian);
	result[1][3] = 0.0f;
	result[2][0] = rotVector[0] * rotVector[2] * (1 - cos(radian)) - rotVector[1] * sin(radian);
	result[2][1] = rotVector[1] * rotVector[2] * (1 - cos(radian)) + rotVector[0] * sin(radian);
	result[2][2] = rotVector[2] * rotVector[2] + (1 - rotVector[2] * rotVector[2]) * cos(radian);
	result[2][3] = 0.0f;
	result[3][0] = 0.0f;
	result[3][1] = 0.0f;
	result[3][2] = 0.0f;
	result[3][3] = 1.0f;
	return &result;
}

GzMatrix* MatrixOperator::GenerateMatrixTransformation(float tx, float ty, float tz) {
	return nullptr;
}

GzMatrix* MatrixOperator::GenerateMatrixScale(float sx, float sy, float sz) {
	return nullptr;
}
