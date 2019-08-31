/*
 * Gz.h - include file for rendering library 

 */

/***********************/
/* universal constants */
#define GZ_SUCCESS      0
#define GZ_FAILURE      1

#define RED     0        /* array indicies for color vector */
#define GREEN   1
#define BLUE    2

#define X       0        /* array indicies for 3D vectors */
#define Y       1
#define Z       2

#define U       0        /* array indicies for texture coords */
#define V       1


/**********************/
/* Boundary constants */
#define	MAXXRES	1024	/* put some bounds on size in case of error */
#define	MAXYRES	1024


/*********************************************/
/* Types and Structures used by the renderer */

typedef void    *GzPointer;
typedef float   GzColor[3];
typedef short   GzIntensity;	/* 0-4095 in lower 12-bits - use for display RGBA */
typedef int	GzDepth;		/* signed int z for clipping */

#ifndef GZ_PIXEL
typedef	struct {
  GzIntensity    red;	
  GzIntensity    green;
  GzIntensity    blue;
  GzIntensity    alpha;
  GzDepth	 z;
} GzPixel;
#define GZ_PIXEL
#endif;





