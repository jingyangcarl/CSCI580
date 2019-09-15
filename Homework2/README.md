Homework 2
==========

## Author
> Student Name: Jing Yang
>
> Student ID: 1692196781
>
> Student Email: jyang010@usc.edu

## Solution Results:
![Solution Results](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%202/output.gif)

## Solution Introduction:
This solution is to render a 2D teapot using Scan Line Algorithm, the algorithm can be found in Onenote/Course/USC[CSCI580]/Class3 - HiddenSurfaces & Culling Algorithm. Scan Line Algorithm consists of two main procesure, vertex sorting and Digital Differential Analyzing, which are implemented in "rendVertexSorter.h" and "rendDigitalDifferentialAnalyzer.h".

## Solution Environment:
* Windows 10
* Visual Studio 2019

## Solution Documentation:
> Header Fiels
>
>> Application.h
>>
>> Application2.h
>>
>> CS580HW.h
>>
>> CS580HWDoc.h
>>
>> CS580HWView.h
>> 
>> gz.h
>>
>> Mainfrm.h
>>
>> rend.h
>>
>>> GzRender::GzRender(int xRs, int yRes): This function a contructor, which is used to create object with correct buffer sizes;
>>>
>>> GzRender::~GzRender(): This function is a destructor, which is used to free memory;
>>>
>>> int GzRender::GzDefault(): This function is used to set pixel buffer to some default values to start a new frame;
>>>
>>> int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity, b, GzIntensity a, GzDepth z): This function is used to put a pixel value with its rgba values at its location (i, j);
>>>
>>> int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z): This function is used to get rgb values of a pixel at its location (i, j);
>>>
>>> int GzRender::GzFlushDisplay2File(FILE *outfile): This function is used to write pixel buffer to a .ppm file;
>>>
>>> int GzRender::GzFlushDisplay2FrameBuffer(): This function is used to write pixel buffer to framebuffer;
>>>
>>> int GzRender::GzPutAttribute(int numAttributes, GzToken *nameList, GzPointer *valueList): This function is used to set renderer attribute states, color in this case;
>>>
>>> int GzRender::GzPutTriangle(int numParts, GzToken *nameList, GzPointer *valueList): This function is used to pass in a triangle description with tokens and values, do rasterization using scanline framework;
>>
>> rendDigitalDifferentialAnalyzer.h
>>
>>> float* DigitalDifferentialAnalyzer::MoveY(float deltaY): This function is used to move current point, defined as a member variable, along the edge from the start point to the end point by deltaY;
>>>
>>> float* DigitalDifferentialAnalyzer::MoveDownward(): This function is used to move the current point downward for one pixel, which calls DigitalDifferentialAnalyzer::MoveY(float);
>>>
>>> float* DigitalDifferentialAnalyzer::MoveToNearestPixelLocation(): This function is used to move the current point to its nearest (downward) pixel location;
>>>
>>> void DigitalDifferentialAnalyzer::MoveReset(): This function is used to move the current point back to the start point;
>>>
>>> float* DigitalDifferentialAnalyzer::getStart(): This function is used to return the start point;
>>>
>>> float* DigitalDifferentialAnalyzer::getEnd(): This function is used to return the end point;
>>>
>>> float* DigitalDifferentialAnalyzer::getCurrent(): This function is used to return the current point;
>>>
>>> float DigitalDifferentialAnalyzer::getSlopeX(): This function is used to return a slope of deltaX/deltaY;
>>>
>>> float DigitalDifferentialAnalyzer::getSlopeZ(): This function is used to return a slope of deltaZ/deltaY;
>>
>> rendVertexSorter.h
>>
>>> void VertexSorter::Sort(): This function is used to sort ver0, ver1, ver2 and save the sorted value to verTop, verMid, and verBot;
>>>
>>> float* VertexSorter::getVerTop(): This funciton is used to get the top vertex;
>>>
>>> float* VertexSorter::getVerMid(): This funciton is used to get the middle vertex;
>>>
>>> float* VertexSorter::getVerBot(): This funciton is used to get the bottom vertex;
>>
>> Resource.h
>>
>> StdAfx.h
>
> Source Files
>
>> Application.cpp
>>
>> Application2.cpp
>>
>> CS580HW.cpp
>>
>> CS580HWDoc.cpp
>>
>> CS580HWView.cpp
>>
>> MainFrm.cpp
>>
>> rend.cpp: implements rend.h;
>>
>> rendDigitalDifferentialAnalyzer.cpp: implements rendDigitalDifferentialAnalyzer;
>>
>> rendVertexSorter.cpp: implements rendVertexSorter.h;
>>
>> StdAfx.cpp
>>
>> StdAfx.cpp
>

## Solution Hierarchy:
```
./Homework2
│  Application.cpp
│  Application.h
│  Application2.cpp
│  Application2.h
│  Assignment2.doc
│  CS580HW.cpp
│  CS580HW.h
│  CS580HW.rc
│  CS580HW2.dsp
│  CS580HW2.dsw
│  CS580HW2.sln
│  CS580HW2.vcxproj
│  CS580HW2.vcxproj.filters
│  CS580HW2.vcxproj.user
│  CS580HWDoc.cpp
│  CS580HWDoc.h
│  CS580HWView.cpp
│  CS580HWView.h
│  gz.h
│  MainFrm.cpp
│  MainFrm.h
│  POT4.PPM
│  pot4.screen.asc
│  rend.cpp
│  rend.h
│  rendDigitalDifferentialAnalyzer.cpp
│  rendDigitalDifferentialAnalyzer.h
│  rendVertexSorter.cpp
│  rendVertexSorter.h
│  resource.h
│  StdAfx.cpp
│  StdAfx.h
│
└─res
        CS580HW.ico
        CS580HW.rc2
        CS580HWDoc.ico
        Toolbar.bmp

```