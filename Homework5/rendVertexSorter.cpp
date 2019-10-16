#include "stdafx.h"
#include "rendVertexSorter.h"

/*
Description:
This function is a constructor;
Input:
@ void parameter: void;
Output:
@ VertexSorter returnValue: a VertexSorter;
*/
VertexSorter::VertexSorter() {
}

/*
Description:
This function is a constructor;
Input:
@ const GzCoord& ver0: a vertex;
@ const GzCoord& ver1: a vertex;
@ const GzCoord& ver2: a vertex;
Output:
@ VertexSorter returnValue: a VertexSorter;
*/
VertexSorter::VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2) {
	this->ver0[0] = ver0[0]; this->ver0[1] = ver0[1]; this->ver0[2] = ver0[2];
	this->ver1[0] = ver1[0]; this->ver1[1] = ver1[1]; this->ver1[2] = ver1[2];
	this->ver2[0] = ver2[0]; this->ver2[1] = ver2[1]; this->ver2[2] = ver2[2];
	this->verTop[0] = 0.0; this->verTop[1] = 0.0f; this->verTop[2] = 0.0;
	this->verBot[0] = 0.0; this->verBot[1] = 0.0f; this->verBot[2] = 0.0;
	this->verMid[0] = 0.0; this->verMid[1] = 0.0f; this->verMid[2] = 0.0;
}

/*
Description:
This function is a constructor;
Input:
@ const GzCoord& ver0: a vertex;
@ const GzCoord& ver1: a vertex;
@ const GzCoord& ver2: a vertex;
@ cosnt GzCoord& norm0: the normal vector at ver0;
@ cosnt GzCoord& norm1: the normal vector at ver1;
@ cosnt GzCoord& norm2: the normal vector at ver2;
Output:
@ VertexSorter returnValue: a VertexSorter;
*/
VertexSorter::VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2, const GzCoord& norm0, const GzCoord& norm1, const GzCoord& norm2) {
	this->ver0[0] = ver0[0]; this->ver0[1] = ver0[1]; this->ver0[2] = ver0[2];
	this->ver1[0] = ver1[0]; this->ver1[1] = ver1[1]; this->ver1[2] = ver1[2];
	this->ver2[0] = ver2[0]; this->ver2[1] = ver2[1]; this->ver2[2] = ver2[2];
	this->norm0[0] = norm0[0]; this->norm0[1] = norm0[1]; this->norm0[2] = norm0[2];
	this->norm1[0] = norm1[0]; this->norm1[1] = norm1[1]; this->norm1[2] = norm1[2];
	this->norm2[0] = norm2[0]; this->norm2[1] = norm2[1]; this->norm2[2] = norm2[2];
	this->verTop[0] = 0.0; this->verTop[1] = 0.0f; this->verTop[2] = 0.0;
	this->verBot[0] = 0.0; this->verBot[1] = 0.0f; this->verBot[2] = 0.0;
	this->verMid[0] = 0.0; this->verMid[1] = 0.0f; this->verMid[2] = 0.0;
	this->normTop[0] = 0.0; this->normTop[1] = 0.0f; this->normTop[2] = 0.0;
	this->normBot[0] = 0.0; this->normBot[1] = 0.0f; this->normBot[2] = 0.0;
	this->normMid[0] = 0.0; this->normMid[1] = 0.0f; this->normMid[2] = 0.0;
}

/*
Description:
This function is used to sort ver0, ver1, ver2 and save the sorted value to verTop, verMid, and verBot. The normals go with vertices;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void VertexSorter::Sort() {

	if (ver0[1] > ver1[1] && ver0[1] > ver2[1]) {
		// verTop is ver0
		verTop[0] = ver0[0]; verTop[1] = ver0[1]; verTop[2] = ver0[2];
		normTop[0] = norm0[0]; normTop[1] = norm0[1]; normTop[2] = norm0[2];
		if (ver1[1] > ver2[1]) {
			// verMid is ver1 and verBot is ver2
			verMid[0] = ver1[0]; verMid[1] = ver1[1]; verMid[2] = ver1[2];
			normMid[0] = norm1[0]; normMid[1] = norm1[1]; normMid[2] = norm1[2];
			verBot[0] = ver2[0]; verBot[1] = ver2[1]; verBot[2] = ver2[2];
			normBot[0] = norm2[0]; normBot[1] = norm2[1]; normBot[2] = norm2[2];
		}
		else {
			// verMid is ver2 and verBot is ver1
			verMid[0] = ver2[0]; verMid[1] = ver2[1]; verMid[2] = ver2[2];
			normMid[0] = norm2[0]; normMid[1] = norm2[1]; normMid[2] = norm2[2];
			verBot[0] = ver1[0]; verBot[1] = ver1[1]; verBot[2] = ver1[2];
			normBot[0] = norm1[0]; normBot[1] = norm1[1]; normBot[2] = norm1[2];
		}
	}
	else if (ver1[1] > ver0[1] && ver1[1] > ver2[1]) {
		// verTop is ver1
		verTop[0] = ver1[0]; verTop[1] = ver1[1]; verTop[2] = ver1[2];
		normTop[0] = norm1[0]; normTop[1] = norm1[1]; normTop[2] = norm1[2];
		if (ver0[1] > ver2[1]) {
			// verMid is ver0 and verBot is ver2
			verMid[0] = ver0[0]; verMid[1] = ver0[1]; verMid[2] = ver0[2];
			normMid[0] = norm0[0]; normMid[1] = norm0[1]; normMid[2] = norm0[2];
			verBot[0] = ver2[0]; verBot[1] = ver2[1]; verBot[2] = ver2[2];
			normBot[0] = norm2[0]; normBot[1] = norm2[1]; normBot[2] = norm2[2];
		}
		else {
			// verMid is ver2 and verBot is ver0
			verMid[0] = ver2[0]; verMid[1] = ver2[1]; verMid[2] = ver2[2];
			normMid[0] = norm2[0]; normMid[1] = norm2[1]; normMid[2] = norm2[2];
			verBot[0] = ver0[0]; verBot[1] = ver0[1]; verBot[2] = ver0[2];
			normBot[0] = norm0[0]; normBot[1] = norm0[1]; normBot[2] = norm0[2];
		}
	}
	else if (ver2[1] > ver0[1] && ver2[1] > ver1[1]) {
		// verTop is 2
		verTop[0] = ver2[0]; verTop[1] = ver2[1]; verTop[2] = ver2[2];
		normTop[0] = norm2[0]; normTop[1] = norm2[1]; normTop[2] = norm2[2];
		if (ver0[1] > ver1[1]) {
			// verMid is ver0 and verBot is ver1
			verMid[0] = ver0[0]; verMid[1] = ver0[1]; verMid[2] = ver0[2];
			normMid[0] = norm0[0]; normMid[1] = norm0[1]; normMid[2] = norm0[2];
			verBot[0] = ver1[0]; verBot[1] = ver1[1]; verBot[2] = ver1[2];
			normBot[0] = norm1[0]; normBot[1] = norm1[1]; normBot[2] = norm1[2];
		}
		else {
			// verMid is ver1 and verBot is ver0
			verMid[0] = ver1[0]; verMid[1] = ver1[1]; verMid[2] = ver1[2];
			normMid[0] = norm1[0]; normMid[1] = norm1[1]; normMid[2] = norm1[2];
			verBot[0] = ver0[0]; verBot[1] = ver0[1]; verBot[2] = ver0[2];
			normBot[0] = norm0[0]; normBot[1] = norm0[1]; normBot[2] = norm0[2];
		}
	}
}

/*
Description:
This funciton is used to get the top vertex;
Input:
@ void parameter: void;
Output:
@ float* returnValue: the top vertex;
*/
float* VertexSorter::getVerTop() {
	return this->verTop;
}

/*
Description:
This funciton is used to get the middle vertex;
Input:
@ void parameter: void;
Output:
@ float* returnValue: the middle vertex;
*/
float* VertexSorter::getVerMid() {
	return this->verMid;
}

/*
Description:
This funciton is used to get the bottom vertex;
Input:
@ void parameter: void;
Output:
@ float* returnValue: the bottom vertex;
*/
float* VertexSorter::getVerBot() {
	return this->verBot;
}

/*
Description:
This funciton is used to get the top vertex's normal;
Input:
@ void parameter: void;
Output:
@ float* returnValue: the top vertex's normal;
*/
float* VertexSorter::getNormTop() {
	return this->normTop;
}

/*
Description:
This funciton is used to get the middle vertex's normal;
Input:
@ void parameter: void;
Output:
@ float* returnValue: the middle vertex's normal;
*/
float* VertexSorter::getNormMid() {
	return this->normMid;
}

/*
Description:
This funciton is used to get the bottom vertex's normal;
Input:
@ void parameter: void;
Output:
@ float* returnValue: the bottom vertex's normal;
*/
float* VertexSorter::getNormBot() {
	return this->normBot;
}
