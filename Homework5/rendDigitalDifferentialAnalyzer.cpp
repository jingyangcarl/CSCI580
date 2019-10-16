#include "stdafx.h"
#include "rendDigitalDifferentialAnalyzer.h"

/*
Description:
This function is a constructor;
Input:
@ void parameter: void;
Output:
@ DigitalDifferentialAnalyzer returnValue: a DigitalDifferentialAnalyzer
*/
DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer() {
	this->startVer[0] = 0.0f; this->startVer[1] = 0.0f; this->startVer[2] = 0.0f;
	this->endVer[0] = 0.0f; this->endVer[1] = 0.0f; this->endVer[2] = 0.0f;
	this->currentVer[0] = startVer[0]; this->currentVer[1] = startVer[1]; this->currentVer[2] = startVer[2];
	this->slopeXToY = 0.0f;
	this->slopeZToY = 0.0f;
}

/*
Description:
This function is a constructor;
Input:
@ const GzCoord& startVer: a start point;
@ const GzCoord& endVer: a end point;
@ const bool initToScanLine: if put the current point to the nearest pixel line;
Output:
@ DigitalDifferentialAnalyzer returnValue: a DigitalDifferentialAnalyzer;
*/
DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const bool initToScanLine) {
	this->startVer[0] = startVer[0]; this->startVer[1] = startVer[1]; this->startVer[2] = startVer[2];
	this->endVer[0] = endVer[0]; this->endVer[1] = endVer[1]; this->endVer[2] = endVer[2];
	this->currentVer[0] = startVer[0]; this->currentVer[1] = startVer[1]; this->currentVer[2] = startVer[2];
	this->slopeXToY = (endVer[0] - startVer[0]) / (endVer[1] - startVer[1]);
	this->slopeZToY = (endVer[2] - startVer[2]) / (endVer[1] - startVer[1]);

	if (initToScanLine) {
		// move current points to nearest pixel scan line
		MoveToNearestPixelLocation();
	}
}

/*
Description:
This function is a constructor;
Input:
@ const GzCoord& startVer: a start point;
@ const GzCoord& endVer: a end point;
@ const GzCoord& startNorm: the start point's normal vector;
@ const GzCoord& endNorm: the end point's normal vector;
@ const bool initToScanLine: if put the current point to the nearest pixel line;
Output:
@ DigitalDifferentialAnalyzer returnValue: a DigitalDifferentialAnalyzer;
*/
DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const bool initToScanLine) {
	// init vertices
	this->startVer[0] = startVer[0]; this->startVer[1] = startVer[1]; this->startVer[2] = startVer[2];
	this->endVer[0] = endVer[0]; this->endVer[1] = endVer[1]; this->endVer[2] = endVer[2];
	this->currentVer[0] = startVer[0]; this->currentVer[1] = startVer[1]; this->currentVer[2] = startVer[2];
	// init normals
	this->startNorm[0] = startNorm[0]; this->startNorm[1] = startNorm[1]; this->startNorm[2] = startNorm[2];
	this->endNorm[0] = endNorm[0]; this->endNorm[1] = endNorm[1]; this->endNorm[2] = endNorm[2];
	this->currentNorm[0] = startNorm[0]; this->currentNorm[1] = startNorm[1]; this->currentNorm[2] = startNorm[2];
	// init slopes
	this->slopeXToY = (endVer[0] - startVer[0]) / (endVer[1] - startVer[1]);
	this->slopeZToY = (endVer[2] - startVer[2]) / (endVer[1] - startVer[1]);
	this->slopeNormXToY = (endNorm[0] - startNorm[0]) / (endVer[1] - startVer[1]);
	this->slopeNormYToY = (endNorm[1] - startNorm[1]) / (endVer[1] - startVer[1]);
	this->slopeNormZToY = (endNorm[2] - startNorm[2]) / (endVer[1] - startVer[1]);
	this->slopeRToY = (endColor[0] - startColor[0]) / (endVer[1] - startVer[1]);
	this->slopeGToY = (endColor[1] - startColor[1]) / (endVer[1] - startVer[1]);
	this->slopeBToY = (endColor[2] - startColor[2]) / (endVer[1] - startVer[1]);

	if (initToScanLine) {
		// move current points to nearest pixel scan line
		MoveToNearestPixelLocation();
	}
}

/*
Description:
This function is a constructor;
Input:
@ const GzCoord& startVer: a start point;
@ const GzCoord& endVer: a end point;
@ const GzCoord& startNorm: the start point's normal vector;
@ const GzCoord& endNorm: the end point's normal vector;
@ const 
@ const bool initToScanLine: if put the current point to the nearest pixel line;
Output:
@ DigitalDifferentialAnalyzer returnValue: a DigitalDifferentialAnalyzer;
*/
DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const GzColor& startColor, const GzColor& endColor, const bool initToScanLine) {
	// init vertices
	this->startVer[0] = startVer[0]; this->startVer[1] = startVer[1]; this->startVer[2] = startVer[2];
	this->endVer[0] = endVer[0]; this->endVer[1] = endVer[1]; this->endVer[2] = endVer[2];
	this->currentVer[0] = startVer[0]; this->currentVer[1] = startVer[1]; this->currentVer[2] = startVer[2];
	// init normals
	this->startNorm[0] = startNorm[0]; this->startNorm[1] = startNorm[1]; this->startNorm[2] = startNorm[2];
	this->endNorm[0] = endNorm[0]; this->endNorm[1] = endNorm[1]; this->endNorm[2] = endNorm[2];
	this->currentNorm[0] = startNorm[0]; this->currentNorm[1] = startNorm[1]; this->currentNorm[2] = startNorm[2];
	// init colors
	this->startColor[0] = startColor[0]; this->startColor[1] = startColor[1]; this->startColor[2] = startColor[2];
	this->endColor[0] = endColor[0]; this->endColor[1] = endColor[1]; this->endColor[2] = endColor[2];
	this->currentColor[0] = startColor[0]; this->currentColor[1] = startColor[1]; this->currentColor[2] = startColor[2];
	// init slopes
	this->slopeXToY = (endVer[0] - startVer[0]) / (endVer[1] - startVer[1]);
	this->slopeZToY = (endVer[2] - startVer[2]) / (endVer[1] - startVer[1]);
	this->slopeNormXToY = (endNorm[0] - startNorm[0]) / (endVer[1] - startVer[1]);
	this->slopeNormYToY = (endNorm[1] - startNorm[1]) / (endVer[1] - startVer[1]);
	this->slopeNormZToY = (endNorm[2] - startNorm[2]) / (endVer[1] - startVer[1]);
	this->slopeRToY = (endColor[0] - startColor[0]) / (endVer[1] - startVer[1]);
	this->slopeGToY = (endColor[1] - startColor[1]) / (endVer[1] - startVer[1]);
	this->slopeBToY = (endColor[2] - startColor[2]) / (endVer[1] - startVer[1]);

	if (initToScanLine) {
		// move current points to nearest pixel scan line
		MoveToNearestPixelLocation();
	}
}

/*
Description:
This function is used to move current point, defined as a member variable, along the edge from the start point to the end point by deltaY;
Input:
@ const float deltaY: a moving distance along y axis;
Output:
@ float* returnValue: coordinations of the current point;
*/
float* DigitalDifferentialAnalyzer::MoveY(const float deltaY) {
	// move current vertex
	this->currentVer[0] += deltaY ? slopeXToY * deltaY : 0;
	this->currentVer[1] += deltaY;
	this->currentVer[2] += deltaY ? slopeZToY * deltaY : 0;
	// move current normal
	this->currentNorm[0] += deltaY ? slopeNormXToY * deltaY : 0;
	this->currentNorm[1] += deltaY ? slopeNormYToY * deltaY : 0;
	this->currentNorm[2] += deltaY ? slopeNormZToY * deltaY : 0;
	// move current color
	this->currentColor[0] += deltaY ? slopeRToY * deltaY : 0;
	this->currentColor[1] += deltaY ? slopeGToY * deltaY : 0;
	this->currentColor[2] += deltaY ? slopeBToY * deltaY : 0;

	return this->currentVer;
}

/*
Description:
This function is used to move the current point downward for one pixel, which calls DigitalDifferentialAnalyzer::MoveY(float);
Input:
@ void parameter: void;
Output:
@ float* returnValue: coordinations of the current point;
*/
float* DigitalDifferentialAnalyzer::MoveDownward() {
	return MoveY(-1.0);
}

/*
Description:
This function is used to move the current point to its nearest (downward) pixel location;
Input:
@ void parameter: void;
Output:
@ float* returnValue: coordinations of the current point;
*/
float* DigitalDifferentialAnalyzer::MoveToNearestPixelLocation() {
	return MoveY(floor(startVer[1]) - startVer[1]);
}

/*
Description:
This function is used to move the current point back to the start point;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void DigitalDifferentialAnalyzer::MoveReset() {
	// reset vertex location
	this->currentVer[0] = startVer[0]; 
	this->currentVer[1] = startVer[1]; 
	this->currentVer[2] = startVer[2];
	// reset normal
	this->currentNorm[0] = startNorm[0];
	this->currentNorm[1] = startNorm[1];
	this->currentNorm[2] = startNorm[2];
	// reset color
	this->currentColor[0] = startColor[0];
	this->currentColor[1] = startColor[1];
	this->currentColor[2] = startColor[2];
}

/*
Description:
This function is used to return the start point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: coordinations of the start point;
*/
float* DigitalDifferentialAnalyzer::getStartVer() {
	return this->startVer;
}

/*
Description:
This function is used to return the end point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: coordinations of the end point;
*/
float* DigitalDifferentialAnalyzer::getEndVer() {
	return this->endVer;
}

/*
Description:
This function is used to return the current point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: coordinations of the current point;
*/
float* DigitalDifferentialAnalyzer::getCurrentVer() {
	return this->currentVer;
}

/*
Description:
This function is used to return the normal of the start point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: normal vector of the start point;
*/
float* DigitalDifferentialAnalyzer::getStartNorm() {
	return this->startNorm;
}

/*
Description:
This function is used to return the normal of the end point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: normal vector of the start point;
*/
float* DigitalDifferentialAnalyzer::getEndNorm() {
	return this->endNorm;
}

/*
Description:
This function is used to return the normal of the current point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: normal vector of the start point;
*/
float* DigitalDifferentialAnalyzer::getCurrentNorm() {
	return this->currentNorm;
}

/*
Description:
This function is used to return the color of the start point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: color of the start point;
*/
float* DigitalDifferentialAnalyzer::getStartColor() {
	return this->startColor;
}

/*
Description:
This function is used to return the color of the end point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: color of the end point;
*/
float* DigitalDifferentialAnalyzer::getEndColor() {
	return this->endColor;
}

/*
Description:
This function is used to return the color of the current point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: color of the current point;
*/
float* DigitalDifferentialAnalyzer::getCurrentColor() {
	return this->currentColor;
}