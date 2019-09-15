#include "stdafx.h"
#include "rendVertexSorter.h"

VertexSorter::VertexSorter() {
}

VertexSorter::VertexSorter(GzCoord& ver0, GzCoord& ver1, GzCoord& ver2) {
	this->ver0[0] = ver0[0]; this->ver0[1] = ver0[1]; this->ver0[2] = ver0[2];
	this->ver1[0] = ver1[0]; this->ver1[1] = ver1[1]; this->ver1[2] = ver1[2];
	this->ver2[0] = ver2[0]; this->ver2[1] = ver2[1]; this->ver2[2] = ver2[2];
	this->verTop[0] = 0.0; this->verTop[1] = 0.0f; this->verTop[2] = 0.0;
	this->verBot[0] = 0.0; this->verBot[1] = 0.0f; this->verBot[2] = 0.0;
	this->verMid[0] = 0.0; this->verMid[1] = 0.0f; this->verMid[2] = 0.0;
}

void VertexSorter::Sort() {

	if (ver0[1] > ver1[1] && ver0[1] > ver2[1]) {
		// verTop is ver0
		verTop[0] = ver0[0]; verTop[1] = ver0[1]; verTop[2] = ver0[2];
		if (ver1[1] > ver2[1]) {
			// verMid is ver1 and verBot is ver2
			verMid[0] = ver1[0]; verMid[1] = ver1[1]; verMid[2] = ver1[2];
			verBot[0] = ver2[0]; verBot[1] = ver2[1]; verBot[2] = ver2[2];
		}
		else {
			// verMid is ver2 and verBot is ver1
			verMid[0] = ver2[0]; verMid[1] = ver2[1]; verMid[2] = ver2[2];
			verBot[0] = ver1[0]; verBot[1] = ver1[1]; verBot[2] = ver1[2];
		}
	}
	else if (ver1[1] > ver0[1] && ver1[1] > ver2[1]) {
		// verTop is ver1
		verTop[0] = ver1[0]; verTop[1] = ver1[1]; verTop[2] = ver1[2];
		if (ver0[1] > ver2[1]) {
			// verMid is ver0 and verBot is ver2
			verMid[0] = ver0[0]; verMid[1] = ver0[1]; verMid[2] = ver0[2];
			verBot[0] = ver2[0]; verBot[1] = ver2[1]; verBot[2] = ver2[2];
		}
		else {
			// verMid is ver2 and verBot is ver0
			verMid[0] = ver2[0]; verMid[1] = ver2[1]; verMid[2] = ver2[2];
			verBot[0] = ver0[0]; verBot[1] = ver0[1]; verBot[2] = ver0[2];
		}
	}
	else if (ver2[1] > ver0[1] && ver2[1] > ver1[1]) {
		// verTop is 2
		verTop[0] = ver2[0]; verTop[1] = ver2[1]; verTop[2] = ver2[2];
		if (ver0[1] > ver1[1]) {
			// verMid is ver0 and verBot is ver1
			verMid[0] = ver0[0]; verMid[1] = ver0[1]; verMid[2] = ver0[2];
			verBot[0] = ver1[0]; verBot[1] = ver1[1]; verBot[2] = ver1[2];
		}
		else {
			// verMid is ver1 and verBot is ver0
			verMid[0] = ver1[0]; verMid[1] = ver1[1]; verMid[2] = ver1[2];
			verBot[0] = ver0[0]; verBot[1] = ver0[1]; verBot[2] = ver0[2];
		}
	}
}

float* VertexSorter::getVerTop() {
	return this->verTop;
}

float* VertexSorter::getVerMid() {
	return this->verMid;
}

float* VertexSorter::getVerBot() {
	return this->verBot;
}
