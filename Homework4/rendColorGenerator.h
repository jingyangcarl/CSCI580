#pragma once
#include "Gz.h"

class ColorGenerator {
public:
	ColorGenerator(int numLights, GzLight* lights, GzLight ambientLight, float Ka, float Kd, float Ks, float spec, GzCoord currentNorm);

	void Generate();
	void setCurrentNorm(GzCoord normal);
	void ToGzColor(GzColor outputColor);

private:

	int numLights;
	GzLight* lights;
	GzLight ambientLight;
	float Ka;
	float Kd;
	float Ks;
	float spec;

	GzCoord currentNorm;

	GzColor outputColor;
};