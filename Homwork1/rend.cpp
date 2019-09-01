#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"
/*   CS580 HW   */
#include    "stdafx.h"  
#include	"Gz.h"

#include <string>
#include <iostream>
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
	delete this->framebuffer;
	delete this->pixelbuffer;
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
	} else {

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
	} else {

	}
	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile)
{
/* HW1.6 write image to ppm file -- "P6 %d %d 255\r" */
	std::stringstream ss;
	ss << "P6 " << std::to_string(xres) << " " << std::to_string(yres) << " 255\r";
	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			ss << char(pixelbuffer[i * xres + j].red >> 4);
			ss << char(pixelbuffer[i * xres + j].green >> 4);
			ss << char(pixelbuffer[i * xres + j].blue >> 4);
		}
	}
	fwrite(ss.str().data(), ss.str().size(), 1, outfile);
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