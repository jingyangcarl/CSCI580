#include "stdafx.h"
#include "rendDigitalDifferentialAnalyzer.h"

DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer() {
	this->start[0] = 0.0f; this->start[1] = 0.0f; this->start[2] = 0.0f;
	this->end[0] = 0.0f; this->end[1] = 0.0f; this->end[2] = 0.0f;
	this->current[0] = start[0]; this->current[1] = start[1]; this->current[2] = start[2];
	this->slopeX = 0.0f;
	this->slopeZ = 0.0f;
}

DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(GzCoord& start, GzCoord& end, bool initToScanLine) {
	this->start[0] = start[0]; this->start[1] = start[1]; this->start[2] = start[2];
	this->end[0] = end[0]; this->end[1] = end[1]; this->end[2] = end[2];
	this->current[0] = start[0]; this->current[1] = start[1]; this->current[2] = start[2];
	this->slopeX = (end[0] - start[0]) / (end[1] - start[1]);
	this->slopeZ = (end[2] - start[2]) / (end[1] - start[1]);

	if (initToScanLine) {
		// move current points to nearest pixel scan line
		MoveToNearestPixelLocation();
	}
}

/*
Description:
This function is used to move current point, defined as a member variable, along the edge from the start point to the end point by deltaY;
Input:
@ float deltaY: a moving distance along y axis;
Output:
@ float* returnValue: coordinations of the current point;
*/
float* DigitalDifferentialAnalyzer::MoveY(float deltaY) {
	this->current[0] += slopeX * deltaY;
	this->current[1] += deltaY;
	this->current[2] += slopeZ * deltaY;

	return this->current;
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
	return MoveY(floor(start[1]) - start[1]);
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
	this->current[0] = start[0]; 
	this->current[1] = start[1]; 
	this->current[2] = start[2];
}

/*
Description:
This function is used to return the start point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: coordinations of the start point;
*/
float* DigitalDifferentialAnalyzer::getStart() {
	return this->start;
}

/*
Description:
This function is used to return the end point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: coordinations of the end point;
*/
float* DigitalDifferentialAnalyzer::getEnd() {
	return this->end;
}

/*
Description:
This function is used to return the current point;
Input:
@ void parameter: void;
Output:
@ float* returnValue: coordinations of the current point;
*/
float* DigitalDifferentialAnalyzer::getCurrent() {
	return this->current;
}

/*
Description:
This function is used to return a slope of deltaX/deltaY;
Input:
@ void parameter: void;
Output:
@ float returnValue: a slope of deltaX/deltaY;
*/
float DigitalDifferentialAnalyzer::getSlopeX() {
	return this->slopeX;
}

/*
Description:
This function is used to return a slope of deltaZ/deltaY;
Input:
@ void parameter: void;
Output:
@ float returnValue: a slope of deltaZ/deltaY;
*/
float DigitalDifferentialAnalyzer::getSlopeZ() {
	return this->slopeZ;
}