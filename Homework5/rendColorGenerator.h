#pragma once
#include "Gz.h"

class ColorGenerator {
public:
	ColorGenerator(const int numLights, GzLight* lights, const GzLight& ambientLight, const float Ka, const float Kd, const float Ks, const float spec, const GzCoord& currentNorm);

	void Generate();
	void setCurrentNorm(const GzCoord& normal);
	void ToGzColor(GzColor& outputColor);

	void setKa(const float Ka);
	void setKd(const float Kd);
	void setKs(const float Ks);
	void setSpec(const float spec);
	void setK(const float Ka, const float Kd, const float Ks);

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