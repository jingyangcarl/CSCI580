#pragma once
#include "gz.h"

class DigitalDifferentialAnalyzer {
public:
	DigitalDifferentialAnalyzer();
	DigitalDifferentialAnalyzer(const GzCoord& start, const GzCoord& end, const bool initToScanLine);

	float* MoveY(const float deltaY);
	float* MoveDownward();
	float* MoveToNearestPixelLocation();
	void MoveReset();

	float* getStart();
	float* getEnd();
	float* getCurrent();
	float getSlopeX() const;
	float getSlopeZ() const;

private:
	GzCoord start;
	GzCoord end;
	GzCoord current;
	float slopeX;
	float slopeZ;
};

typedef DigitalDifferentialAnalyzer DDA;