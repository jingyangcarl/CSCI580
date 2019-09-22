#pragma once
#include "gz.h"

class VertexSorter {
public:
	VertexSorter();
	VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2);

	void Sort();

	float* getVerTop();
	float* getVerMid();
	float* getVerBot();

private:
	GzCoord ver0, ver1, ver2;
	GzCoord verTop, verMid, verBot;
};