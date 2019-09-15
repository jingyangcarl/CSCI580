Homework 1
==========

## Author
> Student Name: Jing Yang
>
> Student ID: 1692196781
>
> Student Email: jyang010@usc.edu

## Solution Results:
![Solution Results](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%201/output.gif)

## Solution Introduction:
This solution is to render a 2D image consists of several rectangulars with different properties. The pixel buffer and frame buffer are introduced in the solution, which are used to render the image.

## Solution Environment:
* Windows 10
* Visual Studio 2019

## Solution Documentation:
> Header Fiels
>
>> Application.h
>>
>> Application1.h
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
>>> GzRender(int xRs, int yRes): This function a contructor, which is used to create object with correct buffer sizes;
>>>
>>> ~GzRender(): This function is a destructor, which is used to free memory;
>>>
>>> int GzDefault(): This function is used to set pixel buffer to some default values to start a new frame;
>>>
>>> int GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity, b, GzIntensity a, GzDepth z): This function is used to put a pixel value with its rgba values at its location (i, j);
>>>
>>> int GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z): This function is used to get rgb values of a pixel at its location (i, j);
>>>
>>> int GzFlushDisplay2File(FILE *outfile): This function is used to write pixel buffer to a .ppm file;
>>>
>>> int Gz FlushDisplay2FrameBuffer(): This function is used to write pixel buffer to framebuffer;
>>
>> Resource.h
>>
>> StdAfx.h
>
> Source Files
>
>> Application.cpp
>>
>> Application1.cpp
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
>> StdAfx.cpp
>>
>> StdAfx.cpp
>

## Solution Hierarchy:
```
./Homework1
│  Application.cpp
│  Application.h
│  Application1.cpp
│  Application1.h
│  Assignment1.doc
│  CS580HW.cpp
│  CS580HW.h
│  CS580HW.rc
│  CS580HW1.dsp
│  CS580HW1.dsw
│  CS580HW1.sln
│  CS580HW1.vcxproj
│  CS580HW1.vcxproj.filters
│  CS580HW1.vcxproj.user
│  CS580HWDoc.cpp
│  CS580HWDoc.h
│  CS580HWView.cpp
│  CS580HWView.h
│  gz.h
│  MainFrm.cpp
│  MainFrm.h
│  README.md
│  rects
│  rend.cpp
│  rend.h
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