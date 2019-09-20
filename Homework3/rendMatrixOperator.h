#pragma once
#include "gz.h"

class MatrixOperator {
public:

	MatrixOperator();
	void Reset();
	void GetResultVector(GzCoord des, bool normalize = false);
	void GetResultMatrix(GzMatrix des);

	// Operations
	void GenerateMatrixRotation(float u, float v, float w, float degree);
	void GenerateMatrixTranslation(float tx, float ty, float tz);
	void GenerateMatrixScale(float sx, float sy, float sz);
	void MatrixCopy(GzMatrix source, GzMatrix destination);
	void MatrixAdd(GzCoord operand1, GzCoord operand2);
	void MatrixAdd(GzMatrix operand1, GzMatrix operand2);
	void MatrixSubtract(GzCoord operand1, GzCoord operand2);
	void MatrixDotMul(GzCoord operand1, float operand2);
	float MatrixDotMul(GzCoord operand1, GzCoord operand2);
	void MatrixDotMul(GzMatrix operand1, GzCoord operand2);
	void MatrixDotMul(GzCoord operand1, GzMatrix operand2);
	void MatrixDotMul(GzMatrix operand1, GzMatrix operand2);
	void MatrixCrossMul(GzCoord operand1, GzCoord operand2);

private:
	// resultMatris is used to save results from matrix operations;
	GzMatrix resultMatrix;
	// resultCoord is used to save results from coord (vector) operations;
	GzCoord resultVector;
};