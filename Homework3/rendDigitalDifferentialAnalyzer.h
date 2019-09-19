#pragma once
#include "gz.h"

class DigitalDifferentialAnalyzer {
public:
	DigitalDifferentialAnalyzer();
	DigitalDifferentialAnalyzer(GzCoord& start, GzCoord& end, bool initToScanLine);

	float* MoveY(float deltaY);
	float* MoveDownward();
	float* MoveToNearestPixelLocation();
	void MoveReset();

	float* getStart();
	float* getEnd();
	float* getCurrent();
	float getSlopeX();
	float getSlopeZ();

private:
	GzCoord start;
	GzCoord end;
	GzCoord current;
	float slopeX;
	float slopeZ;
};

typedef DigitalDifferentialAnalyzer DDA;