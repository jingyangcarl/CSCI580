#pragma once
#include "gz.h"

class VertexSorter {
public:
	VertexSorter();
	VertexSorter(GzCoord& ver0, GzCoord& ver1, GzCoord& ver2);

	void Sort();

	float* getVerTop();
	float* getVerMid();
	float* getVerBot();

private:
	GzCoord ver0, ver1, ver2;
	GzCoord verTop, verMid, verBot;
};