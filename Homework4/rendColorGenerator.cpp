#include "stdafx.h"
#include "rendMatrix.h"
#include "rendColorGenerator.h"

/*
Description:
This function is a constructor;
Input:
@ const int numLights: the number of lights;
@ GzLight* lights: a list of GzLight;
@ const GzLight& ambientLight: ambient light;
@ const float Ka: ambient factor;
@ const float Kd: diffuse factor;
@ const float Ks: specular factor;
@ const float spec: specular exponent;
@ const GzCoord& currentNorm: the current normal vector;
Output:
@ ColorGenerator returnValue: a ColorGenerator;
*/
ColorGenerator::ColorGenerator(const int numLights, GzLight* lights, const GzLight& ambientLight, const float Ka, const float Kd, const float Ks, const float spec, const GzCoord& currentNorm) {
	this->numLights = numLights;
	this->lights = lights;
	this->ambientLight = ambientLight;
	this->Ka = Ka;
	this->Kd = Kd;
	this->Ks = Ks;
	this->spec = spec;
	this->currentNorm[0] = currentNorm[0];
	this->currentNorm[1] = currentNorm[1];
	this->currentNorm[2] = currentNorm[2];
}

/*
Description:
This function is used to generate color based on color equation including specular color, diffuse color, and ambient color;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void ColorGenerator::Generate() {
	GzColor specularColor = { 0.0f, 0.0f, 0.0f };
	GzColor diffuseColor = { 0.0f, 0.0f, 0.0f };
	GzColor ambientColor = { 0.0f, 0.0f, 0.0f };
	GzCoord eye = { 0.0f, 0.0f, -1.0f };
	GzCoord reflection = { 0.0f, 0.0f, 0.0f };

	// specular color
	Matrix specular(1, 3);
	for (int i = 0; i < this->numLights; i++) {
		float nDotL = (Matrix(currentNorm) * Matrix(lights[i].direction).transpose()).toFloat();
		float nDotE = (Matrix(currentNorm) * Matrix(eye).transpose()).toFloat();
		(Matrix(currentNorm) * (nDotL * 2) - Matrix(lights[i].direction)).normalize().toGzCoord(reflection);
		float rDotE = (Matrix(reflection) * Matrix(eye).transpose()).toFloat();

		if (nDotL > 0 && nDotE > 0) {
			specular += Matrix(lights[i].color) * pow(rDotE, this->spec);
		}
		else if (nDotL < 0 && nDotE < 0) {
			// flip normal
			specular += Matrix(lights[i].color) * pow(rDotE, this->spec);
		}
		else {

		}
	}
	//(specular * this->Ks).toGzColor(specularColor);

	// diffuse color
	Matrix diffuse(1, 3);
	for (int i = 0; i < this->numLights; i++) {

		float nDotL = (Matrix(currentNorm) * Matrix(lights[i].direction).transpose()).toFloat();
		float nDotE = (Matrix(currentNorm) * Matrix(eye).transpose()).toFloat();

		if (nDotL > 0 && nDotE > 0) {
			diffuse += Matrix(lights[i].color) * nDotL;
		}
		else if (nDotL < 0 && nDotE < 0) {
			diffuse += Matrix(lights[i].color) * -nDotL;
		}
		else {

		}

	}
	(diffuse * this->Kd).toGzColor(diffuseColor);

	// ambient color
	Matrix ambient(this->ambientLight.color);
	(ambient * this->Ka).toGzColor(ambientColor);

	// Color
	(Matrix(specularColor) + Matrix(diffuseColor) + Matrix(ambientColor)).toGzColor(outputColor);
}

/*
Description:
This function is used to set current normal vector;
Input:
@ const GzCoord& normal: a new normal vector;
Output:
@ void returnValue: void;
*/
void ColorGenerator::setCurrentNorm(const GzCoord& normal) {
	this->currentNorm[0] = normal[0];
	this->currentNorm[1] = normal[1];
	this->currentNorm[2] = normal[2];
}

/*
Description:
This function is used to copy data entries to a GzColor;
Input:
@ GzColor& outputColor: output color;
Output:
@ void returnValue: void;
*/
void ColorGenerator::ToGzColor(GzColor& outputColor) {
	outputColor[0] = this->outputColor[0];
	outputColor[1] = this->outputColor[1];
	outputColor[2] = this->outputColor[2];
}
