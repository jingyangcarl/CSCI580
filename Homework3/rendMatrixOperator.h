#pragma once
#include "gz.h"

class MatrixOperator {
public:

	MatrixOperator();
	void Reset();
	void GetResult(GzMatrix des);

public:
	// Operations
	void GenerateMatrixRotation(float u, float v, float w, float degree);
	void GenerateMatrixTranslation(float tx, float ty, float tz);
	void GenerateMatrixScale(float sx, float sy, float sz);
	void MatrixCopy(GzMatrix source, GzMatrix destination);
	void MatrixAdd(GzMatrix operand1, GzMatrix operand2);
	void MatrixMul(GzMatrix operand1, GzMatrix operand2);

private:
	GzMatrix result;
};