#pragma once

#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "VFunctions.h"



using namespace cv;
using namespace std;


#define CAMERA_RESOLUTION_X 640
#define CAMERA_RESOLUTION_Y 480
class ColorTracking
{

private:
	//Area Size;
	int iLowArea;
	int iHighArea;
	//Hue;
	int iLowH;
	int iHighH;
	//Saturation
	int iLowS;
	int iHighS;
	//Value
	int iLowV;
	int iHighV;
	//type of joint
	int type;

public: 
	double aArea;
	ColorTracking();
	~ColorTracking();
	int posX, posY;
	int prevPosX, prevPosY;


	Mat theFilteredImage;
	void SetPixelArea(int minH, int maxH);
	void SetHue(int minH, int maxH);
	void SetValue(int minv, int maxv);
	void SetSaturation(int minH, int maxH);
	bool Detected;
	void CreateFilteredImage(Mat HSVImage, bool display = false);
	void UpdatePoint2DUsingMoments(Mat imgline, bool draw);
	static void SetColorRangeHSV(Vec3i pixel, Vec3i*MaxValue, Vec3i* MinValue);
	static void GetColorFilteredImage(Vec3i color, Mat * output, Mat * inputHSV);
};

