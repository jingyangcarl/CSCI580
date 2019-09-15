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
		MoveY(floor(start[1]) - start[1]);
	}
}

/*
Description:
This function is used to move current point, defined as a member variable, along the edge from the start point to the end point by deltaY;
Input:
@ float deltaY: a moving distance along y axis;
Output:
@ void returnValue: void;
*/
void DigitalDifferentialAnalyzer::MoveY(float deltaY) {
	this->current[0] += slopeX * deltaY;
	this->current[1] += deltaY;
	this->current[2] += slopeZ * deltaY;
}

float* DigitalDifferentialAnalyzer::getStart() {
	return this->start;
}

float* DigitalDifferentialAnalyzer::getEnd() {
	return this->end;
}

float* DigitalDifferentialAnalyzer::getCurrent() {
	return this->current;
}

float DigitalDifferentialAnalyzer::getSlopeX() {
	return this->slopeX;
}

float DigitalDifferentialAnalyzer::getSlopeZ() {
	return this->slopeZ;
}