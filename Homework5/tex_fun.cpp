/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"

GzColor	*image=NULL;
int xs, ys;
int reset = 1;

/* Image texture function */
int tex_fun(float u, float v, GzColor color)
{
	unsigned char		pixel[3];
	unsigned char     dummy;
	char  		foo[8];
	int   		i, j;
	FILE* fd;

	if (reset) {          /* open and load texture file */
		fd = fopen("texture", "rb");
		if (fd == NULL) {
			fprintf(stderr, "texture file not found\n");
			exit(-1);
		}
		fscanf(fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
		image = (GzColor*)malloc(sizeof(GzColor) * (xs + 1) * (ys + 1));
		if (image == NULL) {
			fprintf(stderr, "malloc for texture image failed\n");
			exit(-1);
		}

		for (i = 0; i < xs * ys; i++) {	/* create array of GzColor values */
			fread(pixel, sizeof(pixel), 1, fd);
			image[i][RED] = (float)((int)pixel[RED]) * (1.0 / 255.0);
			image[i][GREEN] = (float)((int)pixel[GREEN]) * (1.0 / 255.0);
			image[i][BLUE] = (float)((int)pixel[BLUE]) * (1.0 / 255.0);
		}

		reset = 0;          /* init is done */
		fclose(fd);
	}

	/* bounds-test u,v to make sure nothing will overflow image array bounds */
	/* determine texture cell corner values and perform bilinear interpolation */
	/* set color to interpolated GzColor value and return */

	// bound u, v
	u = u < 0 ? 0 : (u > 1 ? 1 : u);
	v = v < 0 ? 0 : (v > 1 ? 1 : v);

	// bilinear interpolation
	float x = (xs - 1) * u;
	float y = (ys - 1) * v;

	int indexA = int(floor(y) * xs + floor(x));
	int indexB = int(floor(y) * xs + ceil(x));
	int indexC = int(ceil(y) * xs + floor(x));
	int indexD = int(ceil(y) * xs + ceil(x));

	GzColor colorA = { image[indexA][RED], image[indexA][GREEN], image[indexA][BLUE] };
	GzColor colorB = { image[indexB][RED], image[indexB][GREEN], image[indexB][BLUE] };
	GzColor colorC = { image[indexC][RED], image[indexC][GREEN], image[indexC][BLUE] };
	GzColor colorD = { image[indexD][RED], image[indexD][GREEN], image[indexD][BLUE] };

	float s = x - floor(x);
	float t = y - floor(y);
	float r = s * t * colorC[0] + (1 - s) * t * colorD[0] + s * (1 - t) * colorB[0] + (1 - s) * (1 - t) * colorA[0];
	float g = s * t * colorC[1] + (1 - s) * t * colorD[1] + s * (1 - t) * colorB[1] + (1 - s) * (1 - t) * colorA[1];
	float b = s * t * colorC[2] + (1 - s) * t * colorD[2] + s * (1 - t) * colorB[2] + (1 - s) * (1 - t) * colorA[2];

	// assign color
	color[0] = r;
	color[1] = g;
	color[2] = b;

	return GZ_SUCCESS;
}

/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{

	return GZ_SUCCESS;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}

