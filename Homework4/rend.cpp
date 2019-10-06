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
}

/*
Description:
This function is a destructor;
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
	GzPushMatrix(m_camera.Xiw);

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
This function is used to push a matrix to transformation matrix stack, where the pushed matrix should be the multiplication of top matrix and the current matrix;
Input:
@ GzMatrix matrix: a matrix to be pushed into the stack;
Outpu:
@ int returnValue: status;
*/
int GzRender::GzPushMatrix(GzMatrix	matrix)
{
/* HW 3.9 
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	if (matlevel >= MATLEVELS) return GZ_FAILURE;

	if (matlevel == -1) {
		Matrix value(matrix);
		value.toGzMatrix(Ximage[++matlevel]);
	}
	else if (matlevel >= 0) {
		//matrixOperator.Reset();
		Matrix value = Matrix(Ximage[matlevel]) * Matrix(matrix);
		value.toGzMatrix(Ximage[++matlevel]);
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
	GzColor* color = (GzColor*)(valueList[0]);

	switch (nameList[0]) {
	case GZ_RGB_COLOR:

		this->flatcolor[0] = ctoi((*color)[0]);
		this->flatcolor[1] = ctoi((*color)[1]);
		this->flatcolor[2] = ctoi((*color)[2]);

		return GZ_SUCCESS;
		break;
	case GZ_DIRECTIONAL_LIGHT:
		break;
	case GZ_AMBIENT_LIGHT:
		break;
	case GZ_DIFFUSE_COEFFICIENT:
		break;
	case GZ_AMBIENT_COEFFICIENT:
		break;
	case GZ_SPECULAR_COEFFICIENT:
		break;
	case GZ_DISTRIBUTION_COEFFICIENT:
		break;
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
-- Invoke the rastrizer/scanline framework
-- Return error code
*/
// prepare ver0, ver1, and ver2;
	GzCoord* coord = (GzCoord*)(valueList[0]);
	GzCoord ver0 = { coord[0][0], coord[0][1], coord[0][2] };
	GzCoord ver1 = { coord[1][0], coord[1][1], coord[1][2] };
	GzCoord ver2 = { coord[2][0], coord[2][1], coord[2][2] };

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

	switch (nameList[0]) {
	case GZ_NULL_TOKEN:
		break;
	case GZ_POSITION:

		// vertex sorting
		// sort ver1, ver2, ver3 to a low-to-height Y ordering
		VertexSorter vertexSorter(ver0, ver1, ver2);
		vertexSorter.Sort();
		GzColor verTop = { vertexSorter.getVerTop()[0], vertexSorter.getVerTop()[1], vertexSorter.getVerTop()[2] };
		GzCoord verMid = { vertexSorter.getVerMid()[0], vertexSorter.getVerMid()[1], vertexSorter.getVerMid()[2] };
		GzCoord verBot = { vertexSorter.getVerBot()[0], vertexSorter.getVerBot()[1], vertexSorter.getVerBot()[2] };

		/*
		Description:
		This function is a lambda function defined to render pixels scan line by scan line from the short edge side to long edge side of a triangle by a top-down order;
		Input:
		@ DDA& shortEdge: the shorter edge of a triangle;
		@ DDA& longEdge: the longest edge of a triangle;
		@ bool isShortEdgeOnRight: if the short edge is on the right of long edge;
		Output:
		@ auto returnValue: a auto returnValue;
		*/
		auto scanLineRender = [this](DDA& shortEdge, DDA& longEdge, bool isShortEdgeOnRight) mutable {
			// from the start line to the end line (along y)
			for (int j = shortEdge.getCurrent()[1]; j >= ceil(shortEdge.getEnd()[1]); j--) {
				if (j < 0 || j > this->yres) continue;
				// from the start pixel to the end pixel (along x)
				if (isShortEdgeOnRight) {
					// short edge is on the right of the long edge
					for (int i = floor(shortEdge.getCurrent()[0]); i >= longEdge.getCurrent()[0]; i--) {
						float slopeZ = (shortEdge.getCurrent()[2] - longEdge.getCurrent()[2]) / (shortEdge.getCurrent()[0] - longEdge.getCurrent()[0]);
						float deltaX = i - shortEdge.getCurrent()[0];
						GzDepth z = slopeZ * deltaX + shortEdge.getCurrent()[2];
						GzPut(i, j, flatcolor[0], flatcolor[1], flatcolor[2], 0, z);
					}
				}
				else {
					// short edge is on the left of the long edge
					for (int i = ceil(shortEdge.getCurrent()[0]); i <= longEdge.getCurrent()[0]; i++) {
						float slopeZ = (shortEdge.getCurrent()[2] - longEdge.getCurrent()[2]) / (shortEdge.getCurrent()[0] - longEdge.getCurrent()[0]);
						float deltaX = i - shortEdge.getCurrent()[0];
						GzDepth z = slopeZ * deltaX + shortEdge.getCurrent()[2];
						GzPut(i, j, flatcolor[0], flatcolor[1], flatcolor[2], 0, z);
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
		DDA ddaTopBot(verTop, verBot, false);
		DDA ddaTopMid(verTop, verMid, true);
		DDA ddaMidBot(verMid, verBot, true);

		// move current point of the long edge to where the short edge ends to decide whether the short edge is on the right or left;
		float xShortEdge = verMid[0];
		float xLongEdge = ddaTopBot.MoveY(verMid[1] - verTop[1])[0];

		// move current point of the long edge back for rendering
		ddaTopBot.MoveReset();
		ddaTopBot.MoveToNearestPixelLocation();

		// if x < verMid[0], the short edge is on the left, or its on the left;
		scanLineRender(ddaTopMid, ddaTopBot, xLongEdge < xShortEdge ? true : xLongEdge > xShortEdge ? false : false);
		scanLineRender(ddaMidBot, ddaTopBot, xLongEdge < xShortEdge ? true : xLongEdge > xShortEdge ? false : false);

		return GZ_SUCCESS;
		break;
	}
}

