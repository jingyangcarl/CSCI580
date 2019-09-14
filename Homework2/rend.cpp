#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"

/***********************************************/
/* HW1 methods: copy here the methods from HW1 */
#include <string>
#include <sstream>

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
			pixelbuffer[j * xres + i].red = 4095;
			pixelbuffer[j * xres + i].green = 4095;
			pixelbuffer[j * xres + i].blue = 4095;
			pixelbuffer[j * xres + i].alpha = 1;
			pixelbuffer[j * xres + i].z = 0;
		}
	}
	return GZ_SUCCESS;
}


int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.4 write pixel values into the buffer */
	if (i >= 0 && i < xres && j >= 0 && j < yres) {
		pixelbuffer[j * xres + i].red = r < 4095 ? r : 4095;
		pixelbuffer[j * xres + i].green = g < 4095 ? g : 4095;
		pixelbuffer[j * xres + i].blue = b < 4095 ? b : 4095;
		pixelbuffer[j * xres + i].alpha = a;
		pixelbuffer[j * xres + i].z = z;
	}
	else {

	}
	return GZ_SUCCESS;
}


int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.5 retrieve a pixel information from the pixel buffer */
	if (i >= 0 && i < xres && j >= 0 && j < yres) {
		*r = pixelbuffer[j * xres + i].red;
		*g = pixelbuffer[j * xres + i].green;
		*b = pixelbuffer[j * xres + i].blue;
		*a = pixelbuffer[j * xres + i].alpha;
		*z = pixelbuffer[j * xres + i].z;
	}
	else {

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
			ss << char(pixelbuffer[j * xres + i].red >> 4);
			ss << char(pixelbuffer[j * xres + i].green >> 4);
			ss << char(pixelbuffer[j * xres + i].blue >> 4);
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
			framebuffer[3 * (j * xres + i) + 0] = char(pixelbuffer[j * xres + i].blue >> 4);
			framebuffer[3 * (j * xres + i) + 1] = char(pixelbuffer[j * xres + i].green >> 4);
			framebuffer[3 * (j * xres + i) + 2] = char(pixelbuffer[j * xres + i].red >> 4);
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

		this->flatcolor[0] = (*color)[0];
		this->flatcolor[1] = (*color)[1];
		this->flatcolor[2] = (*color)[2];

		return GZ_SUCCESS;
		break;
	default:
		return GZ_FAILURE;
		break;
	}

}

int GzRender::GzPutTriangle(int	numParts, GzToken *nameList, GzPointer *valueList) 
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
		GzCoord verTop = { 0, 0, 0 };
		GzCoord verBot = { 0, 0, 0 };
		GzCoord verMid = { 0, 0, 0 };
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
				verBot[0] = ver2[0]; verBot[1] = ver2[1]; verBot[1] = ver2[1];
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

		// setup edge DDAs for top-mid, mid-bot, top-bot
		typedef struct DigitalDifferentialAnalyzer {
			GzCoord start;
			GzCoord end;
			GzCoord current;
			float slopeX;
			float slopeZ;
			DigitalDifferentialAnalyzer(GzCoord &start, GzCoord &end) {
				this->start[0] = start[0]; this->start[1] = start[1]; this->start[1] = start[1];
				this->end[0] = end[0]; this->end[1] = end[1]; this->end[1] = end[1];
				this->current[0] = start[0]; this->current[1] = start[1]; this->current[1] = start[1];
				this->slopeX = (end[0] - start[0]) / (end[1] - start[1]);
				this->slopeZ = (end[2] - start[2]) / (end[1] - start[1]);
			}
		} DDA;
		DDA ddaTopMid(verTop, verMid);
		DDA ddaMidBot(verMid, verBot);
		DDA ddaTopBot(verTop, verBot);

		// find L/R relationship to determine clockwise edges
		// clockwise edges could be either top-bot-mid or top-mid-bot
		float deltaY = verMid[1] - verTop[1];
		float deltaX = ddaTopBot.slopeX * deltaY;

		if (verTop[0] + deltaX < verMid[0]) {
			// vermid is on the right
		}
		else if (verTop[0] + deltaX > verMid[0]) {
			// vermid is on the left

		}
		else {
			// vermid is on the line goes through verTop and verDown

		}

		return GZ_SUCCESS;
		break;
	}
}

