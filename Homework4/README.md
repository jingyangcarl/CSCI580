Homework 3
==========

## Author
> Student Name: Jing Yang
>
> Student ID: 1692196781
>
> Student Email: jyang010@usc.edu

## Solution Results:
| Shading Mode |  Flat  |  Gouraud  |  Phong  |
| :---: | :-: | :-: | :-: |
|  Cam1  | ![FlatCam1](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%204/outputFlatShadingCam1.gif) | ![GouraudCam1](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%204/outputGouraudShadingCam1.gif) | ![PhongCam1](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%204/outputPhongShadingCam1.gif) |
|  Cam2  | ![FlatCam2](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%204/outputFlatShadingCam2.gif) | ![GouraudCam2](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%204/outputGouraudShadingCam2.gif) | ![PhongCam2](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%204/outputPhongShadingCam2.gif) |


## Solution Introduction:
This solution is to render a 2D teapot using Flat shading, Gouraud shading, and Phong shading based on color equation. The light estimation is performed in the image space.

## Solution Environment:
* Windows 10
* Visual Studio 2019

## Solution Documentation:
> Header Fiels
>
>> Application.h
>>
>> Application3.h
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
>> rend.h: GzRender class is used to render graphics;
>>
>> rendColorGenerator.h: ColorGenerator class is used to generate color based on given lights, normal, and other coefficients;
>>
>> rendDigitalDifferentialAnalyzer.h: DigitalDifferentialAnalyzer class is used to perform scan line rasterization;
>>
>> rendMatrix.h: Matrix class is used to perform matrix calculation and generate transformation matrix;
>> 
>> rendVertexSorter.h: VertexSorter class is used to sort vertices;
>>
>> Resource.h
>>
>> StdAfx.h
>
> Source Files
>
>> Application.cpp
>>
>> Application3.cpp
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
>> rendColorGenerator.cpp: implements rendColorGenerator.h;
>>
>>> 
>>
>> rendDigitalDifferentialAnalyzer.cpp: implements rendDigitalDifferentialAnalyzer.h;
>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(): This function is a constructor;
>>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& start, const GzCoord& end, const bool initToScanLine): This function is a constructor;
>>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const bool initToScanLine): This function is a constructor;
>>> 
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const GzColor& startColor, const GzColor& endColor, const bool initToScanLine): This function is a constructor;
>>>
>>> float* DigitalDifferentialAnalyzer::MoveY(float deltaY): This function is used to move current point, defined as a member variable, along the edge from the start point to the end point by deltaY;
>>>
>>> float* DigitalDifferentialAnalyzer::MoveDownward(): This function is used to move the current point downward for one pixel, which calls DigitalDifferentialAnalyzer::MoveY(float);
>>>
>>> float* DigitalDifferentialAnalyzer::MoveToNearestPixelLocation(): This function is used to move the current point to its nearest (downward) pixel location;
>>>
>>> void DigitalDifferentialAnalyzer::MoveReset(): This function is used to move the current point back to the start point;
>>>
>>> float* DigitalDifferentialAnalyzer::getStartVer(): This function is used to return the start point;
>>>
>>> float* DigitalDifferentialAnalyzer::getEndVer(): This function is used to return the end point;
>>>
>>> float* DigitalDifferentialAnalyzer::getCurrentVer(): This function is used to return the current point;
>>>
>>> float* DigitalDifferentialAnalyzer::getStartNorm(): This function is used to return the normal of the start point;
>>>
>>> float* DigitalDifferentialAnalyzer::getEndNorm(): This function is used to return the normal of the end point;
>>>
>>> float* DigitalDifferentialAnalyzer::getCurrentNorm(): This function is used to return the normal of the current point;
>>>
>>> float* DigitalDifferentialAnalyzer::getStartColor(): This function is used to return the color of the start point;
>>>
>>> float* DigitalDifferentialAnalyzer::getEndColor(): This function is used to return the color of the end point;
>>>
>>> float* DigitalDifferentialAnalyzer::getCurrentColor(): This function is used to return the color of the current point;
>>
>> rendMatrix.cpp implements rendMatrix.h;
>>
>>> Matrix::Matrix(): This function is a constructor;
>>> 
>>> Matrix::Matrix(int row, int col, float value): This function is a constructor;
>>> 
>>> Matrix::Matrix(GzMatrix matrix): This function is a constructor;
>>> 
>>> Matrix::Matrix(GzCoord vector): This function is a constructor;
>>> 
>>> Matrix::Matrix(GzCoord vector, float fourth): This function is a constructor;
>>> 
>>> void Matrix::InitEntries(int row, int col, float value): This function is used to initialize all entries to a given value;
>>> 
>>> float** Matrix::getData() const: This function is used to visit matrix entires;
>>> 
>>> float Matrix::getData(const int row, const int col) const: This function is used to visit matrix entry at given location;
>>> 
>>> void Matrix::toGzMatrix(GzMatrix matrix): This function is used to copy data entries to a GzMatrix, if the matrix size is less than GzMatrix (4 by 4) return nothing;
>>> 
>>> void Matrix::toGzCoord(GzCoord vector): This function is used to copy data entries to a GzCoord, if the matrix size is less than GzCoord (1 by 3) return nothing;
>>> 
>>> float Matrix::toFloat(): This function is used to return the very first entry;
>>> 
>>> Matrix& Matrix::generateMatrixRotation(const float u, const float v, const float w, const float degree): This static function is used to generate a rotation matrix around a given rotation central vector and rotation angle, the result will saved in the result matrix;
>>> 
>>> Matrix& Matrix::generateMatrixTranslation(const float tx, const float ty, const float tz): This static function is used to generate a translation matrix, the result will be saved in the result matrix;
>>> 
>>> Matrix& Matrix::generateMatrixScale(const float sx, const float sy, const float sz): This static function is used to generate a scale matrix, the result will be saved in the result matrix;
>>> 
>>> Matrix& Matrix::operator+(const Matrix& operand): This function is a overload of operator+ with a Matrix;
>>> 
>>> Matrix& Matrix::operator+=(const Matrix& operand): This function is a overload of operator+= with a Matrix;
>>>
>>> Matrix& Matrix::operator+(const float operand): This function is a overload of operator+ with a float number;
>>> 
>>> Matrix& Matrix::operator-(): This function is a overload of unary operator-;
>>> 
>>> Matrix& Matrix::operator-(const Matrix& operand): This function is a overload of operator- with a Matrix;
>>> 
>>> Matrix& Matrix::operator-(const float operand): This function is a overload of operator- with a float number;
>>> 
>>> Matrix& Matrix::operator*(const Matrix& operand): This function is a overload of operator* with a Matrix;
>>>
>>> Matrix& Matrix::operator*=(const Matrix& operand): This function is a overload of operator*= with a Matrix;
>>> 
>>> Matrix& Matrix::operator*(const float operand): This function is a overload of operator* with a float number;
>>>
>>> Matrix& Matrix::operator*=(const float operand): This function is a overload of operator*= with a float number;
>>> 
>>> Matrix& Matrix::operator/=(const float operand): This function is a overload of operator/= with a float number;
>>> 
>>> Matrix& Matrix::CrossProduct(const Matrix& operand): This function is used to calculate the cross product with another Matrix;
>>> 
>>> Matrix& Matrix::normalize(): This function is used to normalize the Matrix;
>>> 
>>> Matrix& Matrix::transpose(): This function is used to transpose the Matrix;
>>
>> rendVertexSorter.cpp: implements rendVertexSorter.h;
>>
>>> VertexSorter::VertexSorter(): This function is a constructor;
>>> 
>>> VertexSorter::VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2): This function is a constructor;
>>>
>>> VertexSorter::VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2, const GzCoord& norm0, const GzCoord& norm1, const GzCoord& norm2): This function is a constructor;
>>> 
>>> void VertexSorter::Sort(): This function is used to sort ver0, ver1, ver2 and save the sorted value to verTop, verMid, and verBot;
>>>
>>> float* VertexSorter::getVerTop(): This funciton is used to get the top vertex;
>>>
>>> float* VertexSorter::getVerMid(): This funciton is used to get the middle vertex;
>>> 
>>> float* VertexSorter::getVerBot(): This funciton is used to get the bottom vertex;
>>> 
>>> float* VertexSorter::getNormTop(): This funciton is used to get the top vertex's normal;
>>> 
>>> float* VertexSorter::getNormMid(): This funciton is used to get the middle vertex's normal;
>>> 
>>> float* VertexSorter::getNormBot(): This funciton is used to get the bottom vertex's normal;
>>
>> StdAfx.cpp
>>
>> StdAfx.cpp
>

## Solution Hierarchy:
```
./Homework4
│  Application.cpp
│  Application.h
│  Application4.cpp
│  Application4.h
│  Assignment4.doc
│  CS580HW.cpp
│  CS580HW.h
│  CS580HW.rc
│  CS580HW4.dsp
│  CS580HW4.dsw
│  CS580HW4.sln
│  CS580HW4.vcxproj
│  CS580HW4.vcxproj.filters
│  CS580HW4.vcxproj.user
│  CS580HWDoc.cpp
│  CS580HWDoc.h
│  CS580HWView.cpp
│  CS580HWView.h
│  Gz.h
│  MainFrm.cpp
│  MainFrm.h
│  POT4.ASC
│  README.md
│  rend.cpp
│  rend.h
│  rendColorGenerator.cpp
│  rendColorGenerator.h
│  rendDigitalDifferentialAnalyzer.cpp
│  rendDigitalDifferentialAnalyzer.h
│  rendMatrix.cpp
│  rendMatrix.h
│  rendVertexSorter.cpp
│  rendVertexSorter.h
│  resource.h
│  RotateDlg.cpp
│  RotateDlg.h
│  ScaleDlg.cpp
│  ScaleDlg.h
│  StdAfx.cpp
│  StdAfx.h
│  TranslateDlg.cpp
│  TranslateDlg.h
│  tri.asc
│
└─res
        CS580HW.ico
        CS580HW.rc2
        CS580HWDoc.ico
        icon1.ico
        Thumbs.db
        Toolbar.bmp

```