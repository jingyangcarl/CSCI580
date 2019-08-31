#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"
/*   CS580 HW   */
#include    "stdafx.h"  
#include	"Gz.h"


GzRender::GzRender(int xRes, int yRes)
{
/* HW1.1 create a framebuffer for MS Windows display:
 -- set display resolution
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- allocate memory for pixel buffer
 */
	this->xres = xRes;
	this->yres = yRes;
	this->framebuffer = new char[3 * sizeof(byte) * xRes * yRes];
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
			pixelbuffer[i * xres + j].red = 255;
			pixelbuffer[i * xres + j].green = 255;
			pixelbuffer[i * xres + j].blue = 255;
			pixelbuffer[i * xres + j].alpha = 255;
			pixelbuffer[i * xres + j].z = 0;
		}
	}
	return GZ_SUCCESS;
}


int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* HW1.4 write pixel values into the buffer */
	pixelbuffer[i * xres + j].red = r;
	pixelbuffer[i * xres + j].green = g;
	pixelbuffer[i * xres + j].blue = b;
	pixelbuffer[i * xres + j].alpha = a;
	pixelbuffer[i * xres + j].z = z;
	return GZ_SUCCESS;
}


int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
/* HW1.5 retrieve a pixel information from the pixel buffer */
	*r = pixelbuffer[i * xres + j].red;
	*g = pixelbuffer[i * xres + j].green;
	*b = pixelbuffer[i * xres + j].blue;
	*a = pixelbuffer[i * xres + j].alpha;
	*z = pixelbuffer[i * xres + j].z;
	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile)
{
/* HW1.6 write image to ppm file -- "P6 %d %d 255\r" */
	return GZ_SUCCESS;
}

int GzRender::GzFlushDisplay2FrameBuffer()
{
/* HW1.7 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/

	return GZ_SUCCESS;
}