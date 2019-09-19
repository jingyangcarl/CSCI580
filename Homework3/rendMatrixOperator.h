#pragma once
#include "gz.h"

class MatrixOperator {
public:

	MatrixOperator();

	GzMatrix* GetResult();

private:
	void ResultReset();

public:
	// Operations
	GzMatrix* MatrixAdd(GzMatrix& operand1, GzMatrix& operand2);
	GzMatrix* MatrixMul(GzMatrix& operand1, GzMatrix& operand2);
	GzMatrix* GenerateMatrixRotation(float u, float v, float w, float angle);
	GzMatrix* GenerateMatrixTransformation(float tx, float ty, float tz);
	GzMatrix* GenerateMatrixScale(float sx, float sy, float sz);

private:
	GzMatrix result;
};