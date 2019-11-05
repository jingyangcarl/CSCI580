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
@ const GzColor& Ka: ambient factor;
@ const GzColor& Kd: diffuse factor;
@ const GzColor& Ks: specular factor;
@ const float spec: specular exponent;
@ const GzCoord& currentNorm: the current normal vector;
Output:
@ ColorGenerator returnValue: a ColorGenerator;
*/
ColorGenerator::ColorGenerator(const int numLights, GzLight* lights, const GzLight& ambientLight, const GzColor& Ka, const GzColor& Kd, const GzColor& Ks, const float spec, const GzCoord& currentNorm) {
	this->numLights = numLights;
	this->lights = lights;
	this->ambientLight = ambientLight;
	this->Ka[0] = Ka[0]; this->Ka[1] = Ka[1]; this->Ka[2] = Ka[2];
	this->Kd[0] = Kd[0]; this->Kd[1] = Kd[1]; this->Kd[2] = Kd[2];
	this->Ks[0] = Ks[0]; this->Ks[1] = Ks[1]; this->Ks[2] = Ks[2];
	this->spec = spec;
	Matrix(currentNorm).normalize().toGzColor(this->currentNorm);
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
	GzCoord eye = { 0.0f, 0.0f, -1.0f };
	GzCoord reflection = { 0.0f, 0.0f, 0.0f };
	GzColor specularColor = { 0.0f, 0.0f, 0.0f };
	GzColor diffuseColor = { 0.0f, 0.0f, 0.0f };
	GzColor ambientColor = { 0.0f, 0.0f, 0.0f };
	Matrix specularVector(1, 3);
	Matrix diffuseVector(1, 3);
	Matrix ambientVector(1, 3);

	// specular color
	for (int i = 0; i < this->numLights; i++) {

		float nDotL = (Matrix(currentNorm) * Matrix(lights[i].direction).transpose()).toFloat();
		(Matrix(currentNorm) * (nDotL * 2) - Matrix(lights[i].direction)).normalize().toGzCoord(reflection);
		float rDotE = (Matrix(reflection) * Matrix(eye).transpose()).toFloat();

		specularVector += Matrix(lights[i].color) * pow(rDotE, this->spec);
	}
	(specularVector.ParallelProduct(Ks)).toGzColor(specularColor);
	specularColor[0] = specularColor[0] < 0 ? 0 : specularColor[0] > 1 ? 1 : specularColor[0];
	specularColor[1] = specularColor[1] < 0 ? 0 : specularColor[1] > 1 ? 1 : specularColor[1];
	specularColor[2] = specularColor[2] < 0 ? 0 : specularColor[2] > 1 ? 1 : specularColor[2];

	// diffuse color
	for (int i = 0; i < this->numLights; i++) {

		float nDotL = (Matrix(currentNorm) * Matrix(lights[i].direction).transpose()).toFloat();
		float nDotE = (Matrix(currentNorm) * Matrix(eye).transpose()).toFloat();

		if (nDotL > 0 && nDotE > 0) {
			diffuseVector += Matrix(lights[i].color) * nDotL;
		}
		else if (nDotL < 0 && nDotE < 0) {
			diffuseVector += Matrix(lights[i].color) * -nDotL;
		}
	}
	(diffuseVector.ParallelProduct(Kd)).toGzColor(diffuseColor);

	// ambient color
	ambientVector = Matrix(this->ambientLight.color);
	(ambientVector.ParallelProduct(Ka)).toGzColor(ambientColor);

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

/*
Description:
This function is used to set Ka for color generator;
Input:
@ const GzColor& Ka: ambient factor;
Output:
@ void returnValue: void;
*/
void ColorGenerator::setKa(const GzColor& Ka) {
	this->Ka[0] = Ka[0]; this->Ka[1] = Ka[1]; this->Ka[2] = Ka[2];
}

/*
Description:
This function is used to set Kd for color generator;
Input:
@ const GzColor& Kd: diffuse factor;
Output:
@ void returnValue: void;
*/
void ColorGenerator::setKd(const GzColor& Kd) {
	this->Kd[0] = Kd[0]; this->Kd[1] = Kd[1]; this->Kd[2] = Kd[2];
}

/*
Description:
This function is used to set Ks for color generator;
Input:
@ const GzColor& Ks: specular factor;
Output:
@ void returnValue: void;
*/
void ColorGenerator::setKs(const GzColor& Ks) {
	this->Ks[0] = Ks[0]; this->Ks[1] = Ks[1]; this->Ks[2] = Ks[2];
}

/*
Description:
This function is used to set spec for color generator;
Input:
@ const float Ka: specular exponent;
Output:
@ void returnValue: void;
*/
void ColorGenerator::setSpec(const float spec) {
	this->spec = spec;
}

/*
Description:
This function is used to set Ka, Kd, Ks for color generator;
Input:
@ const float Ka: specular factor;
@ const float Kd: diffuse factor;
@ const float Ks: specular factor;
Output:
@ void returnValue: void;
*/
void ColorGenerator::setK(const GzColor& Ka, const GzColor& Kd, const GzColor& Ks) {
	this->Ka[0] = Ka[0]; this->Ka[1] = Ka[1]; this->Ka[2] = Ka[2];
	this->Kd[0] = Kd[0]; this->Kd[1] = Kd[1]; this->Kd[2] = Kd[2];
	this->Ks[0] = Ks[0]; this->Ks[1] = Ks[1]; this->Ks[2] = Ks[2];
}
