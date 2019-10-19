#pragma once
#include "gz.h"

class DigitalDifferentialAnalyzer {
public:
	DigitalDifferentialAnalyzer();
	DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const bool initToScanLine);
	DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const bool initToScanLine);
	DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const GzColor& startColor, const GzColor& endColor, const bool initToScanLine);
	DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const GzColor& startColor, const GzColor& endColor, const GzTextureIndex& startUV, const GzTextureIndex& endUV, const bool initToScanLine);

	float* MoveY(const float deltaY);
	float* MoveDownward();
	float* MoveToNearestPixelLocation();
	void MoveReset();

	float* getStartVer();
	float* getEndVer();
	float* getCurrentVer();
	float* getStartNorm();
	float* getEndNorm();
	float* getCurrentNorm();
	float* getStartColor();
	float* getEndColor();
	float* getCurrentColor();
	float* getStartUV();
	float* getEndUV();
	float* getCurrentUV();

private:
	GzCoord startVer; GzCoord endVer; GzCoord currentVer;
	GzCoord startNorm; GzCoord endNorm; GzCoord currentNorm;
	GzColor startColor; GzColor endColor; GzColor currentColor;
	GzTextureIndex startUV; GzTextureIndex endUV; GzTextureIndex currentUV;
	float slopeXToY;
	float slopeZToY;
	float slopeNormXToY;
	float slopeNormYToY;
	float slopeNormZToY;
	float slopeRToY;
	float slopeGToY;
	float slopeBToY;
	float slopeUtoY;
	float slopeVtoY;
};

typedef DigitalDifferentialAnalyzer DDA;