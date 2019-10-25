Homework 5
==========

## Author
> Student Name: Jing Yang
>
> Student ID: 1692196781
>
> Student Email: jyang010@usc.edu

## Solution Results:
| Shading Mode |  Gouraud  |  Phong  |
| :---: | :-: | :-: |
|  !Perspective Correction | ![GouraudTexture](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%205/outputGouraudTexture.gif) | ![PhongTexture](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%205/outputPhongTexture.gif) |
|  Perspective Correction  | ![GouraudTexturePerspective](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%205/outputGouraudTexturePerspective.gif) | ![PhongPerspective](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%205/outputPhongTexturePerspective.gif) |
|  Procedural | ![GouraudProcedural](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%205/outputGouraudProcedural.gif) | ![PhongProcedural](https://github.com/jingyangcarl/Resources/blob/master/CSCI580/Homework%205/outputPhongProcedural.gif) |


## Solution Introduction:
This solution is to render a 2D teapot using Gouraud shading, and Phong shading based on color equation with texture. Perspective correction is necessary.

## Solution Environment:
* Windows 10
* Visual Studio 2019

## Solution Documentation:
> Source Files
>
>> Application.cpp
>>
>> Application5.cpp
>>
>> CS580HW.cpp
>>
>> CS580HWDoc.cpp
>>
>> CS580HWView.cpp
>>
>> MainFrm.cpp
>>
>> rend.cpp
>>>
>>> int GzRender::GzRotXMat(float degree, GzMatrix mat): This function is used to generate a rotation matrix around x axis with a given angle;
>>>
>>> int GzRender::GzRotYMat(float degree, GzMatrix mat): This function is used to generate a rotation matrix around y axis with a given angle;
>>>
>>> int GzRender::GzRotZMat(float degree, GzMatrix mat): This function is used to generate a rotation matrix around z axis with a given angle;
>>>
>>> int GzRender::GzTrxMat(GzCoord translate, GzMatrix mat): This function is used to generate a translation matrix with a given translation vector;
>>>
>>> int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat): This function is used to generate a scale matrix with a given scale vector;
>>>
>>> GzRender::GzRender(int xRes, int yRes): This function is a constructor. Initialization includes resolution, framebuffer, pixelbuffer, default camera and projection stack;
>>>
>>> GzRender::~GzRender(): This function is a destructor;
>>> 
>>> int GzRender::GzDefault(): This function is used to setup default pixel values;
>>>
>>> int GzRender::GzBeginRender(): This function is used to prepare projections used for transform model coordinations to world coordinations, camera coordinations, perspective coordinations, and screen coordinations;
>>>
>>> int GzRender::GzPutCamera(GzCamera camera): This function is used to initialize camera including transformation matrix from world space to camera space, and from camera space to perspective space, current camera location, current look at position, up vector, and horizontal field of view;
>>>
>>> int GzRender::GzPushMatrix(GzMatrix matrix, bool pushToXnorm): This function is used to push a matrix to transformation matrix Ximage stack, where the pushed matrix should be the multiplication of top matrix and the current matrix;
>>>
>>> int GzRender::GzPopMatrix(): This function is used to pop a matrix from the transformation matrix stack;
>>>
>>> int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z): This function is used to pug a pixel to pixel buffer;
>>>
>>> int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z): This function is used to get a pixel value from pixel buffer;
>>>
>>> int GzRender::GzFlushDisplay2File(FILE* outfile): This function is used to output the current pixelbuffer to a ppm file;
>>>
>>> int GzRender::GzFlushDisplay2FrameBuffer(): This function is used to push the pixel buffer to frame buffer for display;
>>>
>>> int GzRender::GzPutAttribute(int numAttributes, GzToken *nameList, GzPointer *valueList): This function is used to set renderer attributes;
>>>
>>> int GzRender::GzPutTriangle(int numParts, GzToken *nameList, GzPointer *valueList): This function is used to render triangles to pixel buffer, a scan line algorithm is implemented for trangle rasterization;
>>
>> RotateDlg.cpp
>>
>> ScaleDlg.cpp
>>
>> StdAfx.cpp
>>
>> tex_fun.cpp
>>
>> TranslateDlg.cpp
>>
>> rendColorGenerator.cpp
>>>
>>> ColorGenerator::ColorGenerator(const int numLights, GzLight* lights, const GzLight& ambientLight, const GzColor& Ka, const GzColor& Kd, const GzColor& Ks, const float spec, const GzCoord& currentNorm): This function is a constructor;
>>>
>>> void ColorGenerator::Generate(): This function is used to generate color based on color equation including specular color, diffuse color, and ambient color;
>>>
>>> void ColorGenerator::setCurrentNorm(const GzCoord& normal): This function is used to set current normal vector;
>>>
>>> void ColorGenerator::ToGzColor(GzColor& outputColor): This function is used to copy data entries to a GzColor;
>>>
>>> void ColorGenerator::setKa(const GzColor& Ka): This function is used to set Ka for color generator;
>>> 
>>> void ColorGenerator::setKd(const GzColor& Kd): This function is used to set Kd for color generator;
>>>
>>> void ColorGenerator::setKs(const GzColor& Ks): This function is used to set Ks for color generator;
>>>
>>> void ColorGenerator::setSpec(const float spec): This function is used to set spec for color generator;
>>>
>>> void ColorGenerator::setK(const GzColor& Ka, const GzColor& Kd, const GzColor& Ks): This function is used to set Ka, Kd, Ks for color generator;
>>
>> rendDigitalDifferentialAnalyzer.cpp
>>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(): This function is a constructor;
>>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const bool initToScanLine): This function is a constructor;
>>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const bool initToScanLine): This function is a constructor;
>>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const GzColor& startColor, const GzColor& endColor, const bool initToScanLine): This function is a constructor;
>>>
>>> DigitalDifferentialAnalyzer::DigitalDifferentialAnalyzer(const GzCoord& startVer, const GzCoord& endVer, const GzCoord& startNorm, const GzCoord& endNorm, const GzColor& startColor, const GzColor& endColor, const GzTextureIndex& startUV, const GzTextureIndex& endUV, const bool initToScanLine): This function is a constructor;
>>>
>>> float* DigitalDifferentialAnalyzer::MoveY(const float deltaY): This function is used to move current point, defined as a member variable, along the edge from the start point to the end point by deltaY;
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
>>>
>>> float* DigitalDifferentialAnalyzer::getStartUV(): This function is used to return the uv coordinates of the start point;
>>>
>>> float* DigitalDifferentialAnalyzer::getEndUV(): This function is used to return the uv coordinates of the end point;
>>>
>>> float* DigitalDifferentialAnalyzer::getCurrentUV(): This function is used to return the uv coordinates of the current point;
>>
>> rendMatrix.cpp
>>>
>>> Matrix::Matrix(): This function is a constructor;
>>>
>>> Matrix::Matrix(int row, int col, float value): This function is a constructor;
>>>
>>> Matrix::Matrix(GzMatrix matrix): This function is a constructor;
>>>
>>> Matrix::Matrix(const GzCoord& vector): This function is a constructor;
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
>>> void Matrix::toGzCoord(GzCoord vector, bool normalize): This function is used to copy data entries to a GzCoord, if the matrix size is less than GzCoord (1 by 3) return nothing;
>>>
>>> void Matrix::toGzColor(GzColor color): This function is used to copy data entries to a GzColor, if the matrix size is less than GzCoord (1 by 3) return nothing;
>>>
>>> float Matrix::toFloat(): This function is used to return the very first entry;
>>>
>>> Matrix& Matrix::generateMatrixRotation(const float u, const float v, const float w, const float degree): This static function is used to generate a rotation matrix around a given rotation central vector and rotation angle, the result will saved in the result matrix;
>>>
>>> Matrix& Matrix::generateMatrixTranslation(const float tx, const float ty, const float tz): This static function is used to generate a translation matrix, the result will be saved in the result matrix;
>>>
>>> Matrix& Matrix::generateMatrixScale(const float sx, const float sy, const float sz): This static function is used to generate a scale matrix, the result will be saved in the result matrix;
>>>
>>> Matrix& Matrix::generateIdentity(int row): This function is used to generate a square identity matrix;
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
>>> Matrix& Matrix::ParallelProduct(const Matrix& operand): This function is used to implement .* operator in Matlab;
>>> 
>>> Matrix& Matrix::normalize(): This function is used to normalize the Matrix;
>>>
>>> Matrix& Matrix::transpose(): This function is used to transpose the Matrix;
>>
>> rendVertexSorter.cpp
>>>
>>> VertexSorter::VertexSorter(): This function is a constructor;
>>>
>>> VertexSorter::VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2): This function is a constructor;
>>>
>>> VertexSorter::VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2, const GzCoord& norm0, const GzCoord& norm1, const GzCoord& norm2): This function is a constructor;
>>>
>>> VertexSorter::VertexSorter(const GzCoord& ver0, const GzCoord& ver1, const GzCoord& ver2, const GzCoord& norm0, const GzCoord& norm1, const GzCoord& norm2, const GzTextureIndex& uv0, const GzTextureIndex& uv1, const GzTextureIndex& uv2): This function is a constructor;
>>>
>>> void VertexSorter::Sort(): This function is used to sort ver0, ver1, ver2 and save the sorted value to verTop, verMid, and verBot. The normals go with vertices;
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
>>>
>>> float* VertexSorter::getUVTop(): This function is used to get the top vertex's uv value;
>>>
>>> float* VertexSorter::getUVMid(): This function is used to get the middle vertex's uv value;
>>>
>>> float* VertexSorter::getUVBot(): This function is used to get the bottom vertex's uv value;
>>
> Header Files
>
>> Application.h
>>
>> Application5.h
>>
>> CS580HW.h
>>
>> CS580HWDoc.h
>>
>> CS580HWView.h
>>
>> gz.h
>>
>> MainFrm.h
>> 
>> rend.h
>>
>> Resource.h
>>
>> RotateDlg.h
>>
>> ScaleDlg.h
>>
>> StdAfx.h
>>
>> TranslateDlg.h
>>
>> rendColorGenerator.h
>>
>> rendDigitalDifferentialAnalyzer.h
>>
>> rendMatrix.h
>>
>> rendVertexSorter.h
>

## Solution Hierarchy:
```
./Homework5
│  Application.cpp
│  Application.h
│  Application5.cpp
│  Application5.h
│  Assignment5.doc
│  CS580HW.cpp
│  CS580HW.h
│  CS580HW.rc
│  CS580HW5.dsp
│  CS580HW5.dsw
│  CS580HW5.sln
│  CS580HW5.vcxproj
│  CS580HW5.vcxproj.filters
│  CS580HW5.vcxproj.user
│  CS580HWDoc.cpp
│  CS580HWDoc.h
│  CS580HWView.cpp
│  CS580HWView.h
│  Gz.h
│  MainFrm.cpp
│  MainFrm.h
│  ppot.asc
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
│  texture
│  tex_fun.cpp
│  TranslateDlg.cpp
│  TranslateDlg.h
│
└─res
        CS580HW.ico
        CS580HW.rc2
        CS580HWDoc.ico
        icon1.ico
        Toolbar.bmp
```