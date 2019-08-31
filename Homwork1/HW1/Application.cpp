/**
 * Test application class member functions for homework assignment #1
 * USC csci 580 *
*/

// Application.cpp: implementation of the Application class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CS580HW.h"
#include "Application.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Application::Application()
{
	m_pRender = NULL;		// the display 
	m_pFrameBuffer = NULL;
}

Application::~Application()
{
	if(m_pFrameBuffer != NULL)
		delete m_pFrameBuffer;
}

