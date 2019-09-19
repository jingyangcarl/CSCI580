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

#define PI (float) 3.14159265358979323846

int GzRender::GzRotXMat(float degree, GzMatrix mat)
{
/* HW 3.1
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
*/
	float radian = degree * PI / 180.0f;
	float rotVector[3] = { 1.0f, 0.0f, 0.0f };
	mat[0][0] = rotVector[0] * rotVector[0] + (1 - rotVector[0] * rotVector[0]) * cos(radian);
	mat[0][1] = rotVector[0] * rotVector[1] * (1 - cos(radian)) - rotVector[2] * sin(radian);
	mat[0][2] = rotVector[0] * rotVector[2] * (1 - cos(radian)) + rotVector[1] * sin(radian);
	mat[0][3] = 0.0f;
	mat[1][0] = rotVector[0] * rotVector[1] * (1 - cos(radian)) + rotVector[2] * sin(radian);
	mat[1][1] = rotVector[1] * rotVector[1] + (1 - rotVector[1] * rotVector[1]) * cos(radian);
	mat[1][2] = rotVector[1] * rotVector[2] * (1 - cos(radian)) - rotVector[0] * sin(radian);
	mat[1][3] = 0.0f;
	mat[2][0] = rotVector[0] * rotVector[2] * (1 - cos(radian)) - rotVector[1] * sin(radian);
	mat[2][1] = rotVector[1] * rotVector[2] * (1 - cos(radian)) + rotVector[0] * sin(radian);
	mat[2][2] = rotVector[2] * rotVector[2] + (1 - rotVector[2] * rotVector[2]) * cos(radian);
	mat[2][3] = 0.0f;
	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
	return GZ_SUCCESS;
}

int GzRender::GzRotYMat(float degree, GzMatrix mat)
{
/* HW 3.2
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
*/
	float radian = degree * PI / 180.0f;
	float rotVector[3] = { 0.0f, 1.0f, 0.0f };
	mat[0][0] = rotVector[0] * rotVector[0] + (1 - rotVector[0] * rotVector[0]) * cos(radian);
	mat[0][1] = rotVector[0] * rotVector[1] * (1 - cos(radian)) - rotVector[2] * sin(radian);
	mat[0][2] = rotVector[0] * rotVector[2] * (1 - cos(radian)) + rotVector[1] * sin(radian);
	mat[0][3] = 0.0f;
	mat[1][0] = rotVector[0] * rotVector[1] * (1 - cos(radian)) + rotVector[2] * sin(radian);
	mat[1][1] = rotVector[1] * rotVector[1] + (1 - rotVector[1] * rotVector[1]) * cos(radian);
	mat[1][2] = rotVector[1] * rotVector[2] * (1 - cos(radian)) - rotVector[0] * sin(radian);
	mat[1][3] = 0.0f;
	mat[2][0] = rotVector[0] * rotVector[2] * (1 - cos(radian)) - rotVector[1] * sin(radian);
	mat[2][1] = rotVector[1] * rotVector[2] * (1 - cos(radian)) + rotVector[0] * sin(radian);
	mat[2][2] = rotVector[2] * rotVector[2] + (1 - rotVector[2] * rotVector[2]) * cos(radian);
	mat[2][3] = 0.0f;
	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
	return GZ_SUCCESS;
}

int GzRender::GzRotZMat(float degree, GzMatrix mat)
{
/* HW 3.3
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
*/
	float radian = degree * PI / 180.0f;
	float rotVector[3] = { 0.0f, 0.0f, 1.0f };
	mat[0][0] = rotVector[0] * rotVector[0] + (1 - rotVector[0] * rotVector[0]) * cos(radian);
	mat[0][1] = rotVector[0] * rotVector[1] * (1 - cos(radian)) - rotVector[2] * sin(radian);
	mat[0][2] = rotVector[0] * rotVector[2] * (1 - cos(radian)) + rotVector[1] * sin(radian);
	mat[0][3] = 0.0f;
	mat[1][0] = rotVector[0] * rotVector[1] * (1 - cos(radian)) + rotVector[2] * sin(radian);
	mat[1][1] = rotVector[1] * rotVector[1] + (1 - rotVector[1] * rotVector[1]) * cos(radian);
	mat[1][2] = rotVector[1] * rotVector[2] * (1 - cos(radian)) - rotVector[0] * sin(radian);
	mat[1][3] = 0.0f;
	mat[2][0] = rotVector[0] * rotVector[2] * (1 - cos(radian)) - rotVector[1] * sin(radian);
	mat[2][1] = rotVector[1] * rotVector[2] * (1 - cos(radian)) + rotVector[0] * sin(radian);
	mat[2][2] = rotVector[2] * rotVector[2] + (1 - rotVector[2] * rotVector[2]) * cos(radian);
	mat[2][3] = 0.0f;
	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
	return GZ_SUCCESS;
}

int GzRender::GzTrxMat(GzCoord translate, GzMatrix mat)
{
/* HW 3.4
// Create translation matrix
// Pass back the matrix using mat value
*/
	mat[0][0] = 1.0f;
	mat[0][1] = 0.0f;
	mat[0][2] = 0.0f;
	mat[0][3] = translate[0];
	mat[1][0] = 0.0f;
	mat[1][1] = 1.0f;
	mat[1][2] = 0.0f;
	mat[1][3] = translate[1];
	mat[2][0] = 0.0f;
	mat[2][1] = 0.0f;
	mat[2][2] = 1.0f;
	mat[2][3] = translate[2];
	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
	return GZ_SUCCESS;
}


int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat)
{
/* HW 3.5
// Create scaling matrix
// Pass back the matrix using mat value
*/
	mat[0][0] = scale[0];
	mat[0][1] = 0.0f;
	mat[0][2] = 0.0f;
	mat[0][3] = 0.0f;
	mat[1][0] = 0.0f;
	mat[1][1] = scale[1];
	mat[1][2] = 0.0f;
	mat[1][3] = 0.0f;
	mat[2][0] = 0.0f;
	mat[2][1] = 0.0f;
	mat[2][2] = scale[2];
	mat[2][3] = 0.0f;
	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
	return GZ_SUCCESS;
}


GzRender::GzRender(int xRes, int yRes)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- set display resolution
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- allocate memory for pixel buffer
 */
	//framebuffer = (char*) malloc (3 * sizeof(char) * xRes * yRes);
	this->xres = xRes;
	this->yres = yRes;
	this->framebuffer = new char[3 * sizeof(char) * xRes * yRes];
	this->pixelbuffer = new GzPixel[xRes * yRes];

/* HW 3.6
- setup Xsp and anything only done once 
- init default camera 
*/ 
}

GzRender::~GzRender()
{
/* HW1.2 clean up, free buffer memory */
	delete[] this->framebuffer;
	delete[] this->pixelbuffer;
}

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

int GzRender::GzBeginRender()
{
/* HW 3.7 
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 

	return GZ_SUCCESS;
}

int GzRender::GzPutCamera(GzCamera camera)
{
/* HW 3.8 
/*- overwrite renderer camera structure with new camera definition
*/

	return GZ_SUCCESS;	
}

int GzRender::GzPushMatrix(GzMatrix	matrix)
{
/* HW 3.9 
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	if (matlevel >= MATLEVELS) return GZ_FAILURE;

	if (matlevel == 0) {
		Ximage[matlevel][0][0] = matrix[0][0]
	}

	return GZ_SUCCESS;
}

int GzRender::GzPopMatrix()
{
/* HW 3.10
- pop a matrix off the Ximage stack
- check for stack underflow
*/

	return GZ_SUCCESS;
}

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
	default:
		return GZ_FAILURE;
		break;
	}
}

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
	GzCoord* coord = (GzCoord*)(valueList[0]);
	GzCoord ver0 = { coord[0][0], coord[0][1], coord[0][2] };
	GzCoord ver1 = { coord[1][0], coord[1][1], coord[1][2] };
	GzCoord ver2 = { coord[2][0], coord[2][1], coord[2][2] };


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
		auto Render = [this](DDA& shortEdge, DDA& longEdge, bool isShortEdgeOnRight) mutable {
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
		Render(ddaTopMid, ddaTopBot, xLongEdge < xShortEdge ? true : xLongEdge > xShortEdge ? false : false);
		Render(ddaMidBot, ddaTopBot, xLongEdge < xShortEdge ? true : xLongEdge > xShortEdge ? false : false);

		return GZ_SUCCESS;
		break;
	}
}

