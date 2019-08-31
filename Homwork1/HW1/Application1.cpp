/**
 * Test application class member functions for homework assignment #1
 * USC csci 580 *
*/

// Application1.cpp: implementation of the Application1 class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CS580HW.h"
#include "Application1.h"

#include <stdio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/* CS580 HW : I/O file definition */
#define INFILE1  "rects"
#define OUTFILE1 "output.ppm"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Application1::Application1()
{
	m_nWidth = 512;		// frame buffer and display width
	m_nHeight = 512;    // frame buffer and display height
	
	m_pRender = new GzRender(m_nWidth, m_nHeight);
}

Application1::~Application1()
{
	delete m_pRender;
}

/*
	- CS580 HW
	- This is the routine to call your functions
	- Check the code and modify it if needed.
*/

int Application1::Render() 
{
	int		i, j; 
	int		xRes, yRes;	/* display parameters */ 
	int		status; 
 	 
	status = 0; 
 
	/* 
	 * initialize the display and the renderer 
	 */ 

	status |= m_pRender->GzDefault();  /* init for new frame */
 
	if (status) exit(GZ_FAILURE); 
 
	// I/O File open

	FILE *infile;
	if( (infile = fopen( INFILE1 , "r" )) == NULL )
	{
         AfxMessageBox(_T( "The input file was not opened\n") );
		 return GZ_FAILURE;
	}

	FILE *outfile;
	if( (outfile = fopen( OUTFILE1 , "wb" )) == NULL )
	{
		AfxMessageBox(_T("The output file was not opened\n"));
		 return GZ_FAILURE;
	}
	
	int	ulx, uly, lrx, lry, r, g, b;
	while( fscanf(infile, "%d %d %d %d %d %d %d", 
			&ulx, &uly, &lrx, &lry, &r, &g, &b) == 7) { 
		for (j = uly; j <= lry; j++) {
		  for (i = ulx; i <= lrx; i++) {
		    m_pRender->GzPut(i, j, r, g, b, 1, 0);
		  }
		}
	} 
	
	m_pRender->GzFlushDisplay2File(outfile); 	/* write out or update display to file*/
	m_pRender->GzFlushDisplay2FrameBuffer();	// write out or update display to frame buffer
 
	/* 
	 * Clean up and exit 
	 */ 


	if( fclose( infile ) )
		AfxMessageBox(_T("The input file was not closed\n"));

	if( fclose( outfile ) )
		AfxMessageBox(_T("The output file was not closed\n"));
 
	

	if (status) 
		return(GZ_FAILURE); 
	else 
		return(GZ_SUCCESS); 

}
