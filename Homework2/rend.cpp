#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"
#include	"rendVertexSorter.h"
//#include	"rendDigitalDifferentialAnalyzer.h"

/***********************************************/
/* HW1 methods: copy here the methods from HW1 */
#include <string>
#include <sstream>

GzRender::GzRender(int xRes, int yRes) {
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

GzRender::~GzRender() {
/* HW1.2 clean up, free buffer memory */
	delete[] this->framebuffer;
	delete[] this->pixelbuffer;
}

int GzRender::GzDefault() {
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


int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z) {
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


int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z) {
/* HW1.5 retrieve a pixel information from the pixel buffer */
	if (i >= 0 && i < xres && j >= 0 && j < yres) {
		*r = pixelbuffer[ARRAY(i, j)].red;
		*g = pixelbuffer[ARRAY(i, j)].green;
		*b = pixelbuffer[ARRAY(i, j)].blue;
		*a = pixelbuffer[ARRAY(i, j)].alpha;
		*z = pixelbuffer[ARRAY(i, j)].z;
	}
	else {

	}
	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile) {
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

int GzRender::GzFlushDisplay2FrameBuffer() {
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

int GzRender::GzPutAttribute(int numAttributes, GzToken	*nameList, GzPointer *valueList) {
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

int GzRender::GzPutTriangle(int	numParts, GzToken *nameList, GzPointer *valueList) {
/* numParts - how many names and values */
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

		// setup edge DDAs for top-mid, mid-bot, top-bot
		typedef struct DigitalDifferentialAnalyzer {
			GzCoord start;
			GzCoord end;
			GzCoord current;
			float slopeX;
			float slopeZ;

			DigitalDifferentialAnalyzer() {
				this->start[0] = 0.0f; this->start[1] = 0.0f; this->start[2] = 0.0f;
				this->end[0] = 0.0f; this->end[1] = 0.0f; this->end[2] = 0.0f;
				this->current[0] = start[0]; this->current[1] = start[1]; this->current[2] = start[2];
				this->slopeX = 0.0f;
				this->slopeZ = 0.0f;
			}

			DigitalDifferentialAnalyzer(GzCoord &start, GzCoord &end, bool initToScanLine) {
				this->start[0] = start[0]; this->start[1] = start[1]; this->start[2] = start[2];
				this->end[0] = end[0]; this->end[1] = end[1]; this->end[2] = end[2];
				this->current[0] = start[0]; this->current[1] = start[1]; this->current[2] = start[2];
				this->slopeX = (end[0] - start[0]) / (end[1] - start[1]);
				this->slopeZ = (end[2] - start[2]) / (end[1] - start[1]);
				if (initToScanLine) {
					// move current points to nearest pixel scan line
					MoveY(floor(start[1]) - start[1]);
				}
			}

			/*
			Description:
			This function is used to move current point, defined as a member variable, along the edge from the start point to the end point by deltaY;
			Input:
			@ float deltaY: a moving distance along y axis;
			Output:
			@ void returnValue: void;
			*/
			void MoveY(float deltaY) {
				this->current[0] += slopeX * deltaY;
				this->current[1] += deltaY;
				this->current[2] += slopeZ * deltaY;
			}


		} DDA;

		// find L/R relationship to determine clockwise edges
		// clockwise edges could be either top-bot-mid or top-mid-bot
		DDA ddaTopBot(verTop, verBot, false);
		ddaTopBot.MoveY(verMid[1] - verTop[1]);

		auto Render = [this](DDA& shortEdge, DDA& longEdge, bool isShortEdgeOnRight) mutable {
			// from the start line to the end line (along y)
			for (int j = shortEdge.current[1]; j >= ceil(shortEdge.end[1]); j--) {
				if (j < 0 || j > this->yres) continue;
				// from the start pixel to the end pixel (along x)
				if (isShortEdgeOnRight) {

				}
				else {

				}
			}
		};

		if (ddaTopBot.current[0] < verMid[0]) {
			// vermid is on the right

			// initialize DDAs for top-bot edge and top-mid edge
			DDA ddaTopBot(verTop, verBot, true);
			DDA ddaTopMid(verTop, verMid, true);
			DDA ddaMidBot(verMid, verBot, true);

			// from the start line to the end line (along y)
			for (int j = ddaTopMid.current[1]; j >= ceil(ddaTopMid.end[1]); j--) {

				if (j < 0 || j > yres) continue;

				// from the start pixel to the end pixel (along x)
				for (int i = floor(ddaTopMid.current[0]); i >= ddaTopBot.current[0]; i--) {
					float z = (ddaTopMid.current[2] - ddaTopBot.current[2]) / (ddaTopMid.current[0] - ddaTopBot.current[0]) * (i - ddaTopMid.current[0]) + ddaTopMid.current[2];
					GzPut(i, j, flatcolor[0], flatcolor[1], flatcolor[2], 0, z);
				}

				// move the current points to the next pixel line (scan line by scan line)
				ddaTopMid.MoveY(-1);
				ddaTopBot.MoveY(-1);
			}

			// from the start line to the end line (along y)
			for (int j = ddaMidBot.current[1]; j >= ceil(ddaMidBot.end[1]); j--) {

				if (j < 0 || j > yres) continue;

				// from the start pixel to the end pixel (along x)
				for (int i = floor(ddaMidBot.current[0]); i >= ddaTopBot.current[0]; i--) {
					float z = (ddaMidBot.current[2] - ddaTopBot.current[2]) / (ddaMidBot.current[0] - ddaTopBot.current[0]) * (i - ddaMidBot.current[0]) + ddaMidBot.current[2];
					GzPut(i, j, flatcolor[0], flatcolor[1], flatcolor[2], 0, z);
				}

				// move the current points to the next pixel line (scan line by scan line)
				ddaMidBot.MoveY(-1);
				ddaTopBot.MoveY(-1);
			}

		}
		else if (ddaTopBot.current[0] > verMid[0]) {
			// vermid is on the left

			// initialize DDAs for top-bot edge and top-mid edge
			DDA ddaTopBot(verTop, verBot, true);
			DDA ddaTopMid(verTop, verMid, true);
			DDA ddaMidBot(verMid, verBot, true);

			// from the start line to the end line (along y)
			for (int j = ddaTopMid.current[1]; j >= ceil(ddaTopMid.end[1]); j--) {

				if (j < 0 || j > yres) continue;

				// from the start pixel to the end pixel (along x)
				for (int i = ceil(ddaTopMid.current[0]); i <= ddaTopBot.current[0]; i++) {
					float z = (ddaTopMid.current[2] - ddaTopBot.current[2]) / (ddaTopMid.current[0] - ddaTopBot.current[0]) * (i - ddaTopMid.current[0]) + ddaTopMid.current[2];
					GzPut(i, j, flatcolor[0], flatcolor[1], flatcolor[2], 0, z);
				}

				// move the current points to the next pixel line (scan line by scan line)
				ddaTopMid.MoveY(-1);
				ddaTopBot.MoveY(-1);
			}

			// from the start line to the end line (along y)
			for (int j = ddaMidBot.current[1]; j >= ceil(ddaMidBot.end[1]); j--) {

				if (j < 0 || j > yres) continue;

				// from the start pixel to the end pixel (along x)
				for (int i = ceil(ddaMidBot.current[0]); i <= ddaTopBot.current[0]; i++) {
					float z = (ddaMidBot.current[2] - ddaTopBot.current[2]) / (ddaMidBot.current[0] - ddaTopBot.current[0]) * (i - ddaMidBot.current[0]) + ddaMidBot.current[2];
					GzPut(i, j, flatcolor[0], flatcolor[1], flatcolor[2], 0, z);
				}

				// move the current points to the next pixel line (scan line by scan line)
				ddaMidBot.MoveY(-1);
				ddaTopBot.MoveY(-1);
			}
			
		}
		else {
			// vermid is on the line goes through verTop and verDown

		}

		return GZ_SUCCESS;
		break;
	}
}

