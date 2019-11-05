#pragma once
#include "Gz.h"

class ColorGenerator {
public:
	ColorGenerator(const int numLights, GzLight* lights, const GzLight& ambientLight, const GzColor& Ka, const GzColor& Kd, const GzColor& Ks, const float spec, const GzCoord& currentNorm);

	void Generate();
	void setCurrentNorm(const GzCoord& normal);
	void ToGzColor(GzColor& outputColor);

	void setKa(const GzColor& Ka);
	void setKd(const GzColor& Kd);
	void setKs(const GzColor& Ks);
	void setSpec(const float spec);
	void setK(const GzColor& Ka, const GzColor& Kd, const GzColor& Ks);

private:
	int numLights;
	GzLight* lights;
	GzLight ambientLight;
	GzColor Ka;
	GzColor Kd;
	GzColor Ks;
	float spec;
	GzCoord currentNorm;
	GzColor outputColor;
};