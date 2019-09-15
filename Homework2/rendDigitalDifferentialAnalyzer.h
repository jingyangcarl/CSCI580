#pragma once
#include "gz.h"

class DigitalDifferentialAnalyzer {
public:
	DigitalDifferentialAnalyzer();
	DigitalDifferentialAnalyzer(GzCoord& start, GzCoord& end, bool initToScanLine);
	void MoveY(float deltaY);

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