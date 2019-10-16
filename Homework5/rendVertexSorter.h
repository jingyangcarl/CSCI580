#pragma once
#include "gz.h"

class VertexSorter {
public:
	VertexSorter();
	VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2);
	VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2, const GzCoord& norm0, const GzCoord& norm1, const GzCoord& norm2);

	void Sort();

	float* getVerTop();
	float* getVerMid();
	float* getVerBot();

	float* getNormTop();
	float* getNormMid();
	float* getNormBot();

private:
	GzCoord ver0, ver1, ver2;
	GzCoord norm0, norm1, norm2;
	GzCoord verTop, verMid, verBot;
	GzCoord normTop, normMid, normBot;
};