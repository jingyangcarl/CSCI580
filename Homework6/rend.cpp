/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"

#include	<sstream>
#include	<string>
#include	"rendVertexSorter.h"
#include	"rendDigitalDifferentialAnalyzer.h"
#include	"rendMatrix.h"
#include	"rendColorGenerator.h"

#define PI (float) 3.14159265358979323846

/*
Description:
This function is used to generate a rotation matrix around x axis with a given angle;
Input:
@ float degree: an rotation angle around x axis;
@ GzMatrix mat: an empty matrix;
Output:
@ GzMatrix mat: a rotation matrix;
@ int returnValue: status;
*/
int GzRender::GzRotXMat(float degree, GzMatrix mat)
{
/* HW 3.1
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
*/
	Matrix::generateMatrixRotation(1.0f, 0.0f, 0.0f, degree).toGzMatrix(mat);
	return GZ_SUCCESS;
}

/*
Description:
This function is used to generate a rotation matrix around y axis with a given angle;
Input:
@ float degree: an rotation angle around y axis;
@ GzMatrix mat: an empty matrix;
Output:
@ GzMatrix mat: a rotation matrix;
@ int returnValue: status;
*/
int GzRender::GzRotYMat(float degree, GzMatrix mat)
{
/* HW 3.2
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
*/
	Matrix::generateMatrixRotation(0.0f, 1.0f, 0.0f, degree).toGzMatrix(mat);
	return GZ_SUCCESS;
}

/*
Description:
This function is used to generate a rotation matrix around z axis with a given angle;
Input:
@ float degree: an rotation angle around z axis;
@ GzMatrix mat: an empty matrix;
Output:
@ GzMatrix mat: a rotation matrix;
@ int returnValue: status;
*/
int GzRender::GzRotZMat(float degree, GzMatrix mat)
{
/* HW 3.3
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
*/
	Matrix::generateMatrixRotation(0.0f, 0.0f, 1.0f, degree).toGzMatrix(mat);
	return GZ_SUCCESS;
}

/*
Description:
This function is used to generate a translation matrix with a given translation vector;
Input:
@ GzCoord translate: an translation vector;
@ GzMatrix mat: an empty matrix;
Output:
@ GzMatrix mat: a translation matrix;
@ int returnValue: status;
*/
int GzRender::GzTrxMat(GzCoord translate, GzMatrix mat)
{
/* HW 3.4
// Create translation matrix
// Pass back the matrix using mat value
*/
	Matrix::generateMatrixTranslation(translate[0], translate[1], translate[2]).toGzMatrix(mat);
	return GZ_SUCCESS;
}

/*
Description:
This function is used to generate a scale matrix with a given scale vector;
Input:
@ GzCoord scale: an scale vector;
@ GzMatrix mat: an empty matrix;
Output:
@ GzMatrix mat: a scale matrix;
@ int returnValue: status;
*/
int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat)
{
/* HW 3.5
// Create scaling matrix
// Pass back the matrix using mat value
*/
	Matrix::generateMatrixScale(scale[0], scale[1], scale[2]).toGzMatrix(mat);
	return GZ_SUCCESS;
}

/*
Description:
This function is a constructor. Initialization includes resolution, framebuffer, pixelbuffer, default camera and projection stack;
Input:
@ int xRes: x resolution;
@ int yRes: y resolution;
Output:
@ GzRender returnValue: a GzRender
*/
GzRender::GzRender(int xRes, int yRes)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- set display resolution
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- allocate memory for pixel buffer
 */
	this->xres = xRes;
	this->yres = yRes;
	this->framebuffer = new char[3 * sizeof(char) * xRes * yRes];
	this->pixelbuffer = new GzPixel[xRes * yRes];
	for (int i = 0; i < 6; i++) {
		this->pixelBuffers[i] = new GzPixel[xRes * yRes];
	}

/* HW 3.6
- setup Xsp and anything only done once 
- init default camera 
*/ 
// set up default camera
	this->m_camera.lookat[0] = 0.0f;
	this->m_camera.lookat[1] = 0.0f;
	this->m_camera.lookat[2] = 0.0f;
	this->m_camera.position[0] = DEFAULT_IM_X;
	this->m_camera.position[1] = DEFAULT_IM_Y;
	this->m_camera.position[2] = DEFAULT_IM_Z;
	this->m_camera.worldup[0] = 0.0f;
	this->m_camera.worldup[1] = 1.0f;
	this->m_camera.worldup[2] = 0.0f;
	this->m_camera.FOV = DEFAULT_FOV;

	// set up stack
	this->matlevel = -1;

	// set up numlights
	this->numlights = 0;
}

/*
Description:
This function is a destructor;
Input:
@ void parameter: void;
*/
GzRender::~GzRender()
{
/* HW1.2 clean up, free buffer memory */
	delete[] this->framebuffer;
	delete[] this->pixelbuffer;
}

/*
Description:
This function is used to setup default pixel values;
Input:
@ void parameter: void;
Output:
@ int returnValue: status;
*/
int GzRender::GzDefault()
{
/* HW1.3 set pixel buffer to some default values - start a new frame */
	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			pixelbuffer[ARRAY(i, j)].red = 4095;
			pixelbuffer[ARRAY(i, j)].green = 4095;
			pixelbuffer[ARRAY(i, j)].blue = 4095;
			pixelbuffer[ARRAY(i, j)].alpha = 1;
			pixelbuffer[ARRAY(i, j)].z = MAXINT32;
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int x = 0; x < xres; x++) {
			for (int y = 0; y < yres; y++) {
				pixelBuffers[i][ARRAY(x, y)].red = 4095;
				pixelBuffers[i][ARRAY(x, y)].green = 4095;
				pixelBuffers[i][ARRAY(x, y)].blue = 4095;
				pixelBuffers[i][ARRAY(x, y)].alpha = 1;
				pixelBuffers[i][ARRAY(x, y)].z = MAXINT32;
			}
		}
	}

	return GZ_SUCCESS;
}

/*
Description:
This function is used to prepare projections used for transform model coordinations to world coordinations, camera coordinations, perspective coordinations, and screen coordinations;
Input:
@ void parameter: void;
Output:
@ int returnValue: status;
*/
int GzRender::GzBeginRender()
{
/* HW 3.7 
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 

// set up default frame buffer;
	GzDefault();

	// compute Xsp
	Xsp[0][0] = xres / 2;	Xsp[0][1] = 0.0f;		Xsp[0][2] = 0.0f;	Xsp[0][3] = xres / 2;
	Xsp[1][0] = 0.0f;		Xsp[1][1] = -yres / 2;	Xsp[1][2] = 0.0f;	Xsp[1][3] = yres / 2;
	Xsp[2][0] = 0.0f;		Xsp[2][1] = 0.0f;		Xsp[2][2] = MAXINT;	Xsp[2][3] = 0.0f;
	Xsp[3][0] = 0.0f;		Xsp[3][1] = 0.0f;		Xsp[3][2] = 0.0f;	Xsp[3][3] = 1.0f;
	GzPushMatrix(Xsp);

	// compute Xpi
	m_camera.Xpi[0][0] = 1.0f;	m_camera.Xpi[0][1] = 0.0f;	m_camera.Xpi[0][2] = 0.0f;										m_camera.Xpi[0][3] = 0.0f;
	m_camera.Xpi[1][0] = 0.0f;	m_camera.Xpi[1][1] = 1.0f;	m_camera.Xpi[1][2] = 0.0f;										m_camera.Xpi[1][3] = 0.0f;
	m_camera.Xpi[2][0] = 0.0f;	m_camera.Xpi[2][1] = 0.0f;	m_camera.Xpi[2][2] = tan((m_camera.FOV / 2.0f) * PI / 180.0f);	m_camera.Xpi[2][3] = 0.0f;
	m_camera.Xpi[3][0] = 0.0f;	m_camera.Xpi[3][1] = 0.0f;	m_camera.Xpi[3][2] = tan((m_camera.FOV / 2.0f) * PI / 180.0f);	m_camera.Xpi[3][3] = 1.0f;
	GzPushMatrix(m_camera.Xpi);

	// compute Xiw;
	GzCoord xVec, yVec, zVec;
	// zVec = (m_camera.lookat - m_camera.position) / norm(m_camera.lookat - m_camera.position);
	Matrix zMatrix = (Matrix(m_camera.lookat) - Matrix(m_camera.position)).normalize();
	zMatrix.toGzCoord(zVec);
	// yVec = (m_camera.worldup - (m_camera.worldup * zVec) * zVec) / norm(m_camera.worldup - (m_camera.worldup * zVec) * zVec);
	Matrix temp = Matrix(m_camera.worldup) * zMatrix.transpose();
	Matrix temp2 = (Matrix(zVec) * (Matrix(m_camera.worldup) * zMatrix.transpose()).toFloat());
	Matrix temp3 = Matrix(m_camera.worldup) - (Matrix(zVec) * (Matrix(m_camera.worldup) * zMatrix.transpose()).toFloat());
	Matrix yMatrix = (Matrix(m_camera.worldup) - (Matrix(zVec) * (Matrix(m_camera.worldup) * zMatrix.transpose()).toFloat())).normalize();
	yMatrix.toGzCoord(yVec);
	// xVec = yVec x zVec;
	Matrix xMatrix(yMatrix.CrossProduct(Matrix(zVec)));
	xMatrix.toGzCoord(xVec);

	// prepare Xiw
	m_camera.Xiw[0][0] = xVec[0];	m_camera.Xiw[0][1] = xVec[1];	m_camera.Xiw[0][2] = xVec[2];	m_camera.Xiw[0][3] = -(Matrix(xVec) * Matrix(m_camera.position).transpose()).toFloat();
	m_camera.Xiw[1][0] = yVec[0];	m_camera.Xiw[1][1] = yVec[1];	m_camera.Xiw[1][2] = yVec[2];	m_camera.Xiw[1][3] = -(Matrix(yVec) * Matrix(m_camera.position).transpose()).toFloat();
	m_camera.Xiw[2][0] = zVec[0];	m_camera.Xiw[2][1] = zVec[1];	m_camera.Xiw[2][2] = zVec[2];	m_camera.Xiw[2][3] = -(Matrix(zVec) * Matrix(m_camera.position).transpose()).toFloat();
	m_camera.Xiw[3][0] = 0.0f;		m_camera.Xiw[3][1] = 0.0f;		m_camera.Xiw[3][2] = 0.0f;		m_camera.Xiw[3][3] = 1.0;
	GzPushMatrix(m_camera.Xiw, true);

	return GZ_SUCCESS;
}

/*
Description:
This function is used to initialize camera including transformation matrix from world space to camera space, and from camera space to perspective space, current camera location, current look at position, up vector, and horizontal field of view;
Input:
@ GzCamera camera: a given camera parameters;
Output:
@ int returnValue: status;
*/
int GzRender::GzPutCamera(GzCamera camera)
{
/* HW 3.8 
/*- overwrite renderer camera structure with new camera definition
*/
	m_camera = camera;
	return GZ_SUCCESS;	
}

/*
Description:
This function is used to push a matrix to transformation matrix Ximage stack, where the pushed matrix should be the multiplication of top matrix and the current matrix;
Input:
@ GzMatrix matrix: a matrix to be pushed into the stack;
@ bool pushToXnorm: push the matrix to Xnorm or not, if it's a false, push an identity to makesure the two stack using the same matlevel;
Outpu:
@ int returnValue: status;
*/
int GzRender::GzPushMatrix(GzMatrix	matrix, bool pushToXnorm)
{
/* HW 3.9 
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	if (matlevel >= MATLEVELS) return GZ_FAILURE;

	if (matlevel == -1) {
		Matrix value(matrix);
		matlevel++;
		// push to Ximage
		value.toGzMatrix(Ximage[matlevel]);
		// push to Xnorm
		if (pushToXnorm) value.toGzMatrix(Xnorm[matlevel]);
		else Matrix::generateIdentity(4).toGzMatrix(Xnorm[matlevel]);
	}
	else if (matlevel >= 0) {
		Matrix valueXimage = Matrix(Ximage[matlevel]) * Matrix(matrix);
		Matrix valueXnorm = Matrix(Xnorm[matlevel]) * Matrix(matrix);
		Matrix value(Xnorm[matlevel]);
		matlevel++;
		// push to Ximage
		valueXimage.toGzMatrix(Ximage[matlevel]);
		// push to Xnorm
		if (pushToXnorm) {
			GzMatrix result;
			valueXnorm.toGzMatrix(result);
			result[0][3] = 0.0;
			result[1][3] = 0.0;
			result[2][3] = 0.0;
			for (int i = 0; i < 3; i++) {
				float dividor(0);
				for (int j = 0; j < 3; j++) {
					dividor += result[i][j] * result[i][j];
				}
				dividor = sqrt(dividor);
				for (int j = 0; j < 3; j++) {
					result[i][j] /= dividor;
				}
			}
			//valueXnorm.toGzMatrix(Xnorm[matlevel]);
			Matrix(result).toGzMatrix(Xnorm[matlevel]);
		}
		else value.toGzMatrix(Xnorm[matlevel]);
	}
	else {
		return GZ_FAILURE;
	}
	return GZ_SUCCESS;
}

/*
Description:
This function is used to pop a matrix from the transformation matrix stack;
Input:
@ void parameter: void;
Output:
@ int returnValue: status;
*/
int GzRender::GzPopMatrix()
{
/* HW 3.10
- pop a matrix off the Ximage stack
- check for stack underflow
*/
	if (matlevel < 0) return GZ_SUCCESS;
	else {
		matlevel--;
	}
	return GZ_SUCCESS;
}

/*
Description:
This function is used to pug a pixel to pixel buffer;
Input:
@ int i: x position;
@ int j: y position;
@ GzIntensity r: red value;
@ GzIntensity g: green value;
@ GzIntensity b: blue value;
@ GzIntensity a: alpha value;
@ GzDepth z: depth value;
Output:
@ int returnValue: status;
*/
int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.4 write pixel values into the buffer */
	if (i >= 0 && i < xres && j >= 0 && j < yres) {
		if (z <= pixelbuffer[ARRAY(i, j)].z) {
			pixelbuffer[ARRAY(i, j)].red = r < 4095 ? r : 4095;
			pixelbuffer[ARRAY(i, j)].green = g < 4095 ? g : 4095;
			pixelbuffer[ARRAY(i, j)].blue = b < 4095 ? b : 4095;
			pixelbuffer[ARRAY(i, j)].alpha = a;
			pixelbuffer[ARRAY(i, j)].z = z;
		}
	}
	else {
		GZ_FAILURE;
	}
	return GZ_SUCCESS;
}

int GzRender::GzPut(int i, int j, int bufferIndex, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z) {
	if (bufferIndex < 0 || bufferIndex > 6) return GZ_FAILURE;

	if (i >= 0 && i < xres && j >= 0 && j < yres) {
		if (z <= pixelBuffers[bufferIndex][ARRAY(i, j)].z) {
			pixelBuffers[bufferIndex][ARRAY(i, j)].red = r < 4095 ? r : 4095;
			pixelBuffers[bufferIndex][ARRAY(i, j)].green = g < 4095 ? g : 4095;
			pixelBuffers[bufferIndex][ARRAY(i, j)].blue = b < 4095 ? b : 4095;
			pixelBuffers[bufferIndex][ARRAY(i, j)].alpha = a;
			pixelBuffers[bufferIndex][ARRAY(i, j)].z = z;
		}
	}
	else {
		GZ_FAILURE;
	}
	return GZ_SUCCESS;
}

/*
Description:
This function is used to get a pixel value from pixel buffer;
Input:
@ int i: x position;
@ int j: y position;
@ GzIntensity r: an empty red value;
@ GzIntensity g: an empty green value;
@ GzIntensity b: an empty blue value;
@ GzIntensity a: an empty alpha value;
@ GzDepth z: an empty depth value;
Output:
@ GzIntensity r: a red value;
@ GzIntensity g: a green value;
@ GzIntensity b: a blue value;
@ GzIntensity a: an alpha value;
@ GzDepth z: an empty depth value;
@ int returnValue: status;
*/
int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.5 retrieve a pixel information from the pixel buffer */
	if (i >= 0 && i < xres && j >= 0 && j < yres) {
		*r = pixelbuffer[ARRAY(i, j)].red;
		*g = pixelbuffer[ARRAY(i, j)].green;
		*b = pixelbuffer[ARRAY(i, j)].blue;
		*a = pixelbuffer[ARRAY(i, j)].alpha;
		*z = pixelbuffer[ARRAY(i, j)].z;
	}
	else {
		GZ_FAILURE;
	}
	return GZ_SUCCESS;
}

/*
Description:
This function is used to output the current pixelbuffer to a ppm file;
Input:
@ FILE* outfile: a outfile name;
Output:
@ int returnValue: status;
*/
int GzRender::GzFlushDisplay2File(FILE* outfile)
{
/* HW1.6 write image to ppm file -- "P6 %d %d 255\r" */
	std::stringstream ss;
	ss << "P6 " << std::to_string(xres) << " " << std::to_string(yres) << " 255\r";

	for (int j = 0; j < yres; j++) {
		for (int i = 0; i < xres; i++) {
			ss << char(pixelbuffer[ARRAY(i, j)].red >> 4);
			ss << char(pixelbuffer[ARRAY(i, j)].green >> 4);
			ss << char(pixelbuffer[ARRAY(i, j)].blue >> 4);
		}
	}

	// write to file
	size_t count = 1;
	if (fwrite(ss.str().data(), ss.str().size(), count, outfile) == count) {
		return GZ_FAILURE;
	}
	return GZ_SUCCESS;
}

/*
Description:
This function is used to push the pixel buffer to frame buffer for display;
Input:
@ void parameter: void;
Output:
@ int returnValue: status;
*/
int GzRender::GzFlushDisplay2FrameBuffer()
{
/* HW1.7 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/
	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			framebuffer[3 * ARRAY(i, j) + 0] = char(pixelbuffer[j * xres + i].blue >> 4);
			framebuffer[3 * ARRAY(i, j) + 1] = char(pixelbuffer[j * xres + i].green >> 4);
			framebuffer[3 * ARRAY(i, j) + 2] = char(pixelbuffer[j * xres + i].red >> 4);
		}
	}
	return GZ_SUCCESS;
}


/***********************************************/
/* HW2 methods: implement from here */

/*
Description:
This function is used to set renderer attributes;
Input:
@ void numberAttributes: the number of attributes;
@ GzToken *nameList: a token list, where the token indicates the rendering classification;
@ GzPointer *valueList: the value for attributes;
Output:
@ int returnValue: status;
*/
int GzRender::GzPutAttribute(int numAttributes, GzToken	*nameList, GzPointer *valueList) 
{
/* HW 2.1
-- Set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
-- In later homeworks set shaders, interpolaters, texture maps, and lights
*/

/*
- GzPutAttribute() must accept the following tokens/values:

- GZ_RGB_COLOR					GzColor		default flat-shade color
- GZ_INTERPOLATE				int			shader interpolation mode
- GZ_DIRECTIONAL_LIGHT			GzLight
- GZ_AMBIENT_LIGHT            	GzLight		(ignore direction)
- GZ_AMBIENT_COEFFICIENT		GzColor		Ka reflectance
- GZ_DIFFUSE_COEFFICIENT		GzColor		Kd reflectance
- GZ_SPECULAR_COEFFICIENT       GzColor		Ks coef's
- GZ_DISTRIBUTION_COEFFICIENT   float		spec power
*/
// loop through all attributes
	for (int i = 0; i < numAttributes; i++) {
		switch (nameList[i]) {
		case GZ_RGB_COLOR: {

			// get color from value list
			GzColor* color = (GzColor*)(valueList[i]);

			// save flat color;
			this->flatcolor[0] = ctoi((*color)[0]);
			this->flatcolor[1] = ctoi((*color)[1]);
			this->flatcolor[2] = ctoi((*color)[2]);

		} break;
		case GZ_INTERPOLATE: {

			// save interpolation mode
			this->interp_mode = *(int*)(valueList[i]);

		} break;
		case GZ_DIRECTIONAL_LIGHT: {

			// get light from value list
			GzLight* light = (GzLight*)(valueList[i]);

			// save light direction
			this->lights[numlights].direction[0] = light->direction[0];
			this->lights[numlights].direction[1] = light->direction[1];
			this->lights[numlights].direction[2] = light->direction[2];

			// save light color
			this->lights[numlights].color[0] = light->color[0];
			this->lights[numlights].color[1] = light->color[1];
			this->lights[numlights].color[2] = light->color[2];

			// update
			numlights++;

		} break;
		case GZ_AMBIENT_LIGHT: {

			// get light from value list
			GzLight* light = (GzLight*)(valueList[i]);

			// save ambient light direction
			this->ambientlight.direction[0] = light->direction[0];
			this->ambientlight.direction[1] = light->direction[1];
			this->ambientlight.direction[2] = light->direction[2];

			// save ambient light color
			this->ambientlight.color[0] = light->color[0];
			this->ambientlight.color[1] = light->color[1];
			this->ambientlight.color[2] = light->color[2];

		} break;
		case GZ_DIFFUSE_COEFFICIENT: {

			// get coefficients from value list
			GzColor* coef = (GzColor*)(valueList[i]);

			// save diffuse coefficients
			this->Kd[0] = (*coef)[0];
			this->Kd[1] = (*coef)[1];
			this->Kd[2] = (*coef)[2];

		} break;
		case GZ_AMBIENT_COEFFICIENT: {

			// get coefficients from value list
			GzColor* coef = (GzColor*)(valueList[i]);

			// save ambient coefficients
			this->Ka[0] = (*coef)[0];
			this->Ka[1] = (*coef)[1];
			this->Ka[2] = (*coef)[2];

		} break;
		case GZ_SPECULAR_COEFFICIENT: {

			// get coefficients from value list
			GzColor* coef = (GzColor*)(valueList[i]);

			// save sepcular coefficients
			this->Ks[0] = (*coef)[0];
			this->Ks[1] = (*coef)[1];
			this->Ks[2] = (*coef)[2];

		} break;
		case GZ_DISTRIBUTION_COEFFICIENT: {

			// save specular power
			this->spec = *(float*)(valueList[i]);

		} break;
		case GZ_TEXTURE_MAP: {
			this->tex_fun = *(GzTexture)(valueList[i]);
		} break;
		}
	}

	return GZ_SUCCESS;
}

/*
Description:
This function is used to render triangles to pixel buffer, a scan line algorithm is implemented for trangle rasterization;
Input:
@ int numParts: the number of parts;
@ GzToken *nameList: a token list, where the token indicates the rendering classification;
@ GzPointer *valueList: the value for triangles;
Output:
@ int returnValue: status;
*/
int GzRender::GzPutTriangle(int numParts, GzToken *nameList, GzPointer *valueList)
/* numParts - how many names and values */
{
/* HW 2.2
-- Pass in a triangle description with tokens and values corresponding to
      GZ_NULL_TOKEN:		do nothing - no values
      GZ_POSITION:		3 vert positions in model space
-- Return error code
*/
/*
-- Xform positions of verts using matrix on top of stack 
-- Clip - just discard any triangle with any vert(s) behind view plane 
		- optional: test for triangles with all three verts off-screen (trivial frustum cull)
-- invoke triangle rasterizer  
*/

	float AAFilter[6][3]{
		-0.52, 0.38, 0.128,		0.41, 0.56, 0.119,		0.27, 0.08, 0.294,
		-0.17, -0.29, 0.249,	0.58, -0.55, 0.104,		-0.31, -0.71, 0.106
	};

	for (int bufferIndex = 0; bufferIndex < 6; bufferIndex++) {
		// prepare ver0, ver1, and ver2;
		GzCoord* verCoord = (GzCoord*)(valueList[0]);
		GzCoord ver0 = { verCoord[0][0], verCoord[0][1], verCoord[0][2] };
		GzCoord ver1 = { verCoord[1][0], verCoord[1][1], verCoord[1][2] };
		GzCoord ver2 = { verCoord[2][0], verCoord[2][1], verCoord[2][2] };

		// project ver0, ver1 and ver2;
		Matrix projVer0 = Matrix(Ximage[matlevel]) * Matrix(ver0, 1.0f).transpose();
		Matrix projVer1 = Matrix(Ximage[matlevel]) * Matrix(ver1, 1.0f).transpose();
		Matrix projVer2 = Matrix(Ximage[matlevel]) * Matrix(ver2, 1.0f).transpose();
		projVer0 /= projVer0.getData(3, 0);
		projVer1 /= projVer1.getData(3, 0);
		projVer2 /= projVer2.getData(3, 0);
		projVer0.transpose().toGzCoord(ver0);
		projVer1.transpose().toGzCoord(ver1);
		projVer2.transpose().toGzCoord(ver2);

		// prepare norm0, norm1, and norm2;
		GzCoord* normCoord = (GzCoord*)(valueList[1]);
		GzCoord norm0 = { normCoord[0][0], normCoord[0][1], normCoord[0][2] };
		GzCoord norm1 = { normCoord[1][0], normCoord[1][1], normCoord[1][2] };
		GzCoord norm2 = { normCoord[2][0], normCoord[2][1], normCoord[2][2] };

		// project norm0, norm1, and norm2 to model space;
		Matrix projNorm0 = Matrix(Xnorm[matlevel]) * Matrix(norm0, 1.0f).transpose();
		Matrix projNorm1 = Matrix(Xnorm[matlevel]) * Matrix(norm1, 1.0f).transpose();
		Matrix projNorm2 = Matrix(Xnorm[matlevel]) * Matrix(norm2, 1.0f).transpose();
		projNorm0.transpose().toGzCoord(norm0, true);
		projNorm1.transpose().toGzCoord(norm1, true);
		projNorm2.transpose().toGzCoord(norm2, true);

		// prepare uv0, uv1, vu2;
		GzTextureIndex* uvCoord = (GzTextureIndex*)(valueList[2]);
		GzTextureIndex uv0 = { uvCoord[0][0], uvCoord[0][1] };
		GzTextureIndex uv1 = { uvCoord[1][0], uvCoord[1][1] };
		GzTextureIndex uv2 = { uvCoord[2][0], uvCoord[2][1] };

		// vertex sorting
		// sort ver1, ver2, ver3 to a low-to-height Y ordering
		VertexSorter vertexSorter(ver0, ver1, ver2, norm0, norm1, norm2, uv0, uv1, uv2);
		vertexSorter.Sort();
		GzCoord verTop = { vertexSorter.getVerTop()[0] - AAFilter[bufferIndex][0], vertexSorter.getVerTop()[1] - AAFilter[bufferIndex][1], vertexSorter.getVerTop()[2] };
		GzCoord verMid = { vertexSorter.getVerMid()[0] - AAFilter[bufferIndex][0], vertexSorter.getVerMid()[1] - AAFilter[bufferIndex][1], vertexSorter.getVerMid()[2] };
		GzCoord verBot = { vertexSorter.getVerBot()[0] - AAFilter[bufferIndex][0], vertexSorter.getVerBot()[1] - AAFilter[bufferIndex][1], vertexSorter.getVerBot()[2] };
		GzCoord normTop = { vertexSorter.getNormTop()[0], vertexSorter.getNormTop()[1], vertexSorter.getNormTop()[2] };
		GzCoord normMid = { vertexSorter.getNormMid()[0], vertexSorter.getNormMid()[1], vertexSorter.getNormMid()[2] };
		GzCoord normBot = { vertexSorter.getNormBot()[0], vertexSorter.getNormBot()[1], vertexSorter.getNormBot()[2] };
		GzTextureIndex uvTop = { vertexSorter.getUVTop()[0], vertexSorter.getUVTop()[1] };
		GzTextureIndex uvMid = { vertexSorter.getUVMid()[0], vertexSorter.getUVMid()[1] };
		GzTextureIndex uvBot = { vertexSorter.getUVBot()[0], vertexSorter.getUVBot()[1] };

		// generate vertex color for flat shading
		ColorGenerator colorGenerator(numlights, lights, ambientlight, Ka, Kd, Ks, spec, norm0);
		colorGenerator.Generate();
		colorGenerator.ToGzColor(this->flatcolor);

		// read color from uv map
		GzColor colorTop = { 0.0f, 0.0f, 0.0f };
		GzColor colorMid = { 0.0f, 0.0f, 0.0f };
		GzColor colorBot = { 0.0f, 0.0f, 0.0f };

		// generate vertex color for Gouraud shading
		GzColor Kt = { 1.0f, 1.0f, 1.0f };
		colorGenerator.setK(Kt, Kt, Kt);
		colorGenerator.setCurrentNorm(normTop);
		colorGenerator.Generate();
		colorGenerator.ToGzColor(colorTop);
		colorGenerator.setCurrentNorm(normMid);
		colorGenerator.Generate();
		colorGenerator.ToGzColor(colorMid);
		colorGenerator.setCurrentNorm(normBot);
		colorGenerator.Generate();
		colorGenerator.ToGzColor(colorBot);

		// transform uv value from image space to perspective space for phong shading
		/*
		Description:
		This function is used to transform parameter in perspective space to image space;
		Input:
		@ float scaledZ: scaled Z value in perspective space;
		@ float p: parameter p in perspective space;
		Output:
		@ auto returnValue: a parameter in image space;
		*/
		auto image2perspective = [](float scaledZ, float p) mutable {
			float zPrime = scaledZ / (MAXINT - scaledZ);
			return p / (zPrime + 1);
		};
		uvTop[0] = image2perspective(verTop[2], uvTop[0]);
		uvTop[1] = image2perspective(verTop[2], uvTop[1]);
		uvMid[0] = image2perspective(verMid[2], uvMid[0]);
		uvMid[1] = image2perspective(verMid[2], uvMid[1]);
		uvBot[0] = image2perspective(verBot[2], uvBot[0]);
		uvBot[1] = image2perspective(verBot[2], uvBot[1]);

		/*
		Description:
		This function is a lambda function defined to render pixels scan line by scan line from the short edge side to long edge side of a triangle by a top-down order;
		Input:
		@ DDA& shortEdge: the shorter edge of a triangle;
		@ DDA& longEdge: the longest edge of a triangle;
		@ bool isShortEdgeOnRight: if the short edge is on the right of long edge;
		Output:
		@ auto returnValue: an auto returnValue;
		*/
		auto scanLineRender = [this](DDA& shortEdge, DDA& longEdge, int bufferIndex, bool isShortEdgeOnRight) mutable {
			/*
			Description:
			This function is a lambda function defined to calculate color, normal and depth at given location;
			Input:
			@ int i: index i in the rendered image;
			@ int j: index j in the rendered image;
			@ DDA& shortEdge: the shorter edge of a triangle;
			@ DDA& longEdge: the longest edge of a triangle;
			@ int count: the counter used to accelerate
			Output:
			@ auto returnValue: an auto returnValue;
			*/
			auto Render = [this](const float i, const float j, int bufferIndex, DDA& shortEdge, DDA& longEdge) mutable {

				float deltaX = i - shortEdge.getCurrentVer()[0];

				// calculate z
				float slopeZToX = (shortEdge.getCurrentVer()[2] - longEdge.getCurrentVer()[2]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
				GzDepth z = slopeZToX * deltaX + shortEdge.getCurrentVer()[2];

				/*
				Description:
				This function is used to transform scaled parameter in image space back to perspective space;
				Input��
				@ float scaledZ: scaled Z value in perspective space;
				@ float scaledP: scaled parameter in image space;
				Output:
				@ auto returnValue: a parameter in perspective space;
				*/
				auto perspective2image = [](float scaledZ, float scaledP) {
					float zPrime = scaledZ / (MAXINT - scaledZ);
					return scaledP * (zPrime + 1);
				};

				// calculate r, g, b
				if (this->interp_mode == GZ_FLAT) {
					// flat shading

				}
				else if (this->interp_mode == GZ_COLOR) {
					// Gouraud shading
					float slopeRToX = (shortEdge.getCurrentColor()[0] - longEdge.getCurrentColor()[0]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float slopeGToX = (shortEdge.getCurrentColor()[1] - longEdge.getCurrentColor()[1]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float slopeBToX = (shortEdge.getCurrentColor()[2] - longEdge.getCurrentColor()[2]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float r = slopeRToX * deltaX + shortEdge.getCurrentColor()[0];
					float g = slopeGToX * deltaX + shortEdge.getCurrentColor()[1];
					float b = slopeBToX * deltaX + shortEdge.getCurrentColor()[2];

					float slopeUtoX = (shortEdge.getCurrentUV()[0] - longEdge.getCurrentUV()[0]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float slopeVtoX = (shortEdge.getCurrentUV()[1] - longEdge.getCurrentUV()[1]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float currentU = slopeUtoX * deltaX + shortEdge.getCurrentUV()[0];
					float currentV = slopeVtoX * deltaX + shortEdge.getCurrentUV()[1];

					// interpolate uv back to image 
					currentU = perspective2image(z, currentU);
					currentV = perspective2image(z, currentV);
					GzColor K = { 0.0f, 0.0f, 0.0f };
					this->tex_fun(currentU, currentV, K);

					this->flatcolor[0] = r * K[0];
					this->flatcolor[1] = g * K[1];
					this->flatcolor[2] = b * K[2];
				}
				else if (this->interp_mode == GZ_NORMALS) {
					// Phong shading
					float slopeNormXToX = (shortEdge.getCurrentNorm()[0] - longEdge.getCurrentNorm()[0]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float slopeNormYToX = (shortEdge.getCurrentNorm()[1] - longEdge.getCurrentNorm()[1]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float slopeNormZToX = (shortEdge.getCurrentNorm()[2] - longEdge.getCurrentNorm()[2]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float currentNormX = slopeNormXToX * deltaX + shortEdge.getCurrentNorm()[0];
					float currentNormY = slopeNormYToX * deltaX + shortEdge.getCurrentNorm()[1];
					float currentNormZ = slopeNormZToX * deltaX + shortEdge.getCurrentNorm()[2];

					float slopeUtoX = (shortEdge.getCurrentUV()[0] - longEdge.getCurrentUV()[0]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float slopeVtoX = (shortEdge.getCurrentUV()[1] - longEdge.getCurrentUV()[1]) / (shortEdge.getCurrentVer()[0] - longEdge.getCurrentVer()[0]);
					float currentU = slopeUtoX * deltaX + shortEdge.getCurrentUV()[0];
					float currentV = slopeVtoX * deltaX + shortEdge.getCurrentUV()[1];

					// interpolate uv back to image 
					currentU = perspective2image(z, currentU);
					currentV = perspective2image(z, currentV);

					GzCoord currentNormal = { currentNormX, currentNormY, currentNormZ };
					GzColor K = { 0.0f, 0.0f, 0.0f };
					this->tex_fun(currentU, currentV, K);
					ColorGenerator colorGenerator(numlights, lights, ambientlight, K, K, Ks, spec, currentNormal);
					colorGenerator.Generate();
					colorGenerator.ToGzColor(this->flatcolor);
				}

				// clip color
				flatcolor[0] = flatcolor[0] > 1 ? 1 : (flatcolor[0] < 0 ? 0 : flatcolor[0]);
				flatcolor[1] = flatcolor[1] > 1 ? 1 : (flatcolor[1] < 0 ? 0 : flatcolor[1]);
				flatcolor[2] = flatcolor[2] > 1 ? 1 : (flatcolor[2] < 0 ? 0 : flatcolor[2]);

				// project normalized color to 0-4096
				float r = ctoi(flatcolor[0]);
				float g = ctoi(flatcolor[1]);
				float b = ctoi(flatcolor[2]);

				// put pixel
				GzPut(i, j, bufferIndex, r, g, b, 0, z);
			};

			// from the start line to the end line (along y)
			for (int j = shortEdge.getCurrentVer()[1]; j >= ceil(shortEdge.getEndVer()[1]); j--) {
				if (j < 0 || j > this->yres) {
					// skip the line and move current points down to the next pixel line;
					shortEdge.MoveDownward();
					longEdge.MoveDownward();
					continue;
				}
				// from the start pixel to the end pixel (along x)
				if (isShortEdgeOnRight) {
					// short edge is on the right of the long edge
					for (int i = floor(shortEdge.getCurrentVer()[0]); i >= longEdge.getCurrentVer()[0]; i--) {
						Render(i, j, bufferIndex, shortEdge, longEdge);
					}
				}
				else {
					// short edge is on the left of the long edge
					for (int i = ceil(shortEdge.getCurrentVer()[0]); i <= longEdge.getCurrentVer()[0]; i++) {
						Render(i, j, bufferIndex, shortEdge, longEdge);
					}
				}
				// move the current points to the next pixel line (scan line by scan line)
				shortEdge.MoveDownward();
				longEdge.MoveDownward();
			}
			return GZ_SUCCESS;
		};

		// find L/R relationship to determine clockwise edges
		// clockwise edges could be either top-bot-mid or top-mid-bot
		// initialize DDAs for top-bot edge and top-mid edge
		DDA ddaTopBot(verTop, verBot, normTop, normBot, colorTop, colorBot, uvTop, uvBot, false);
		DDA ddaTopMid(verTop, verMid, normTop, normMid, colorTop, colorMid, uvTop, uvMid, true);
		DDA ddaMidBot(verMid, verBot, normMid, normBot, colorMid, colorBot, uvMid, uvBot, true);

		// move current point of the long edge to where the short edge ends to decide whether the short edge is on the right or left;
		float xShortEdge = verMid[0];
		float xLongEdge = ddaTopBot.MoveY(verMid[1] - verTop[1])[0];

		// move current point of the long edge back for rendering
		ddaTopBot.MoveReset();
		ddaTopBot.MoveToNearestPixelLocation();

		// if x < verMid[0], the short edge is on the left, or its on the right;
		scanLineRender(ddaTopMid, ddaTopBot, bufferIndex, xLongEdge < xShortEdge ? true : xLongEdge > xShortEdge ? false : false);
		scanLineRender(ddaMidBot, ddaTopBot, bufferIndex, xLongEdge < xShortEdge ? true : xLongEdge > xShortEdge ? false : false);
	}

	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			float r(0), g(0), b(0), a(0), z(0);
			for (int bufferIndex = 0; bufferIndex < 6; bufferIndex++) {
				r += pixelBuffers[bufferIndex][ARRAY(i, j)].red * AAFilter[bufferIndex][2];
				g += pixelBuffers[bufferIndex][ARRAY(i, j)].green * AAFilter[bufferIndex][2];
				b += pixelBuffers[bufferIndex][ARRAY(i, j)].blue * AAFilter[bufferIndex][2];
				a += pixelBuffers[bufferIndex][ARRAY(i, j)].alpha * AAFilter[bufferIndex][2];
				z += pixelBuffers[bufferIndex][ARRAY(i, j)].z * AAFilter[bufferIndex][2];
			}
			pixelbuffer[ARRAY(i, j)].red = r;
			pixelbuffer[ARRAY(i, j)].green = g;
			pixelbuffer[ARRAY(i, j)].blue = b;
			pixelbuffer[ARRAY(i, j)].alpha = a;
			pixelbuffer[ARRAY(i, j)].z = z;
		}
	}

	return GZ_SUCCESS;
}

