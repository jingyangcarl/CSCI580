Homework 3
==========

## Author
> Student Name: Jing Yang
>
> Student ID: 1692196781
>
> Student Email: jyang010@usc.edu

## Solution Results:
![Solution Results](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/output.gif)

### Rotation:
| Angle |  X  |  Y  |  Z  |
| :---: | :-: | :-: | :-: |
|  +30  | ![RotXPos30](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputRotXPos30.gif) | ![RotYPos30](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputRotYPos30.gif) | ![RotZPos30](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputRotZPos30.gif) |
|  -30  | ![RotXNeg30](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputRotXNeg30.gif) | ![RotYNeg30](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputRotYNeg30.gif) | ![RotZNeg30](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputRotZNeg30.gif) |

### Translation:
| Distance |  X  |  Y  |  Z  |
| :------: | :-: | :-: | :-: |
|   +3.0   | ![TransXPos3](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputTransXPos3.gif) | ![TransYPos3](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputTransYPos3.gif) | ![TransZPos3](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputTransZPos3.gif) |
|   -3.0   | ![TransXNeg3](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputTransXNeg3.gif) | ![TransYNeg3](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputTransYNeg3.gif) | ![TransZNeg3](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputTransZNeg3.gif) |

### Scale:
| Factor |  X  |  Y  |  Z  |
| :----: | :-: | :-: | :-: |
|   2.0  | ![ScaleXPos2](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputScaleXPos2.gif) | ![ScaleYPos2](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputScaleYPos2.gif) | ![ScaleYPos2](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputScaleZPos2.gif) |
|   0.5  | ![ScaleXPos0.5](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputScaleXPos0.5.gif) | ![ScaleYPos0.5](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputScaleYPos0.5.gif) | ![ScaleYPos0.5](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%203/outputScaleZPos0.5.gif) |

## Solution Introduction:
This solution is to render a 2D teapot, where the teapot has to be transformed from model space to world space, camera space (image space), perspective space and finally screen space using projection matrix Xmw, Xwi, Xip, Xps. Moreover transformation is also implemented including rotation, translation, and scale. A Matrix class is introduced in the project, which is defined in "rendMatrix.h";

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
>> rendDigitalDifferentialAnalyzer.cpp: implements rendDigitalDifferentialAnalyzer;
>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(): This function is a constructor;
>>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& start, const GzCoord& end, const bool initToScanLine): This function is a constructor;
>>>
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
>>> Matrix& Matrix::operator+(const float operand): This function is a overload of operator+ with a float number;
>>> 
>>> Matrix& Matrix::operator-(const Matrix& operand): This function is a overload of operator- with a Matrix;
>>> 
>>> Matrix& Matrix::operator-(const float operand): This function is a overload of operator- with a float number;
>>> 
>>> Matrix& Matrix::operator*(const Matrix& operand): This function is a overload of operator* with a Matrix;
>>> 
>>> Matrix& Matrix::operator*(const float operand): This function is a overload of operator* with a float number;
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
>>> void VertexSorter::Sort(): This function is used to sort ver0, ver1, ver2 and save the sorted value to verTop, verMid, and verBot;
>>>
>>> float* VertexSorter::getVerTop(): This funciton is used to get the top vertex;
>>>
>>> float* VertexSorter::getVerMid(): This funciton is used to get the middle vertex;
>>>
>>> float* VertexSorter::getVerBot(): This funciton is used to get the bottom vertex;
>>
>> StdAfx.cpp
>>
>> StdAfx.cpp
>

## Solution Hierarchy:
```
./Homework3
©¦  Application.cpp
©¦  Application.h
©¦  Application3.cpp
©¦  Application3.h
©¦  Assignment3.doc
©¦  CS580HW.cpp
©¦  CS580HW.h
©¦  CS580HW.rc
©¦  CS580HW3.dsp
©¦  CS580HW3.dsw
©¦  CS580HW3.sln
©¦  CS580HW3.vcxproj
©¦  CS580HW3.vcxproj.filters
©¦  CS580HW3.vcxproj.user
©¦  CS580HWDoc.cpp
©¦  CS580HWDoc.h
©¦  CS580HWView.cpp
©¦  CS580HWView.h
©¦  gz.h
©¦  MainFrm.cpp
©¦  MainFrm.h
©¦  pot4.asc
©¦  README.md
©¦  rend.cpp
©¦  rend.h
©¦  rendDigitalDifferentialAnalyzer.cpp
©¦  rendDigitalDifferentialAnalyzer.h
©¦  rendMatrix.cpp
©¦  rendMatrix.h
©¦  rendVertexSorter.cpp
©¦  rendVertexSorter.h
©¦  resource.h
©¦  RotateDlg.cpp
©¦  RotateDlg.h
©¦  ScaleDlg.cpp
©¦  ScaleDlg.h
©¦  StdAfx.cpp
©¦  StdAfx.h
©¦  TranslateDlg.cpp
©¦  TranslateDlg.h
©¦  tri.asc
©¦
©¸©¤res
        CS580HW.ico
        CS580HW.rc2
        CS580HWDoc.ico
        icon1.ico
        Toolbar.bmp

```