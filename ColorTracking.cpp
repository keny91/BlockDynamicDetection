#include "ColorTracking.h"



ColorTracking::ColorTracking()
{
}


ColorTracking::~ColorTracking()
{
}


// Set Joint Data
void ColorTracking::SetHue(int minH, int maxH) {
	iLowH = minH;
	iHighH = maxH;
}

void ColorTracking::SetValue(int minV, int maxV) {
	iLowV = minV;
	iHighV = maxV;
}

void ColorTracking::SetSaturation(int minS, int maxS) {
	iLowS = minS;
	iHighS = maxS;
}

void ColorTracking::SetPixelArea(int minS, int maxS) {
	iLowArea = minS;
	iHighArea = maxS;
}



/// <summary> Get the color values from a upper and lower threshold given a initial color HSV value.
/// </summary>
void ColorTracking::SetColorRangeHSV(Vec3i value, Vec3i* MaxValue, Vec3i* MinValue) {
	// Pre-set variables
	int MaxHuelimit = 179; // Limit for openCV
	int upperSat = 255;
	int lowerSat = 150;
	int upperValue = 255;
	int lowerValue = 100;
	int range = 5;


	int Hue = value[0];
	int UpperHue = Hue + range;
	int LowerHue = Hue - range;
	if (UpperHue > MaxHuelimit)
		UpperHue = MaxHuelimit;

	if (LowerHue < 0)
		LowerHue = 0;

	MaxValue[0][0] = UpperHue;
	MaxValue[0][1] = upperSat;
	MaxValue[0][2] = upperValue;

	MinValue[0][0] = LowerHue;
	MinValue[0][1] = lowerSat;
	MinValue[0][2] = lowerValue;


	// case that is from  177 to 10 -> 177,178,179,0,1,2,...,10?

}


/* Get the color filtered image by getting the similar color tones. An create a segmentation using those reference tones. */
void ColorTracking::GetColorFilteredImage(Vec3i color, Mat * inputHSV, Mat *  output) {

	Vec3i MaxA = Vec3i();
	Vec3i MinA = Vec3i();
	ColorTracking::SetColorRangeHSV(color, &MaxA, &MinA);

	// Debugging info.
	//cout << "MAX:  " << MaxA[0] << MaxA[1] << MaxA[2] << endl;
	//cout << "MIN:  " << MinA[0] << MinA[1] << MinA[2] << endl;

	inRange(*inputHSV, MinA, MaxA, *output);

}




/// <param> HSVImage an image already converted into the HSV color space
/// </param>
/// <summary> Filter the image
/// </summary>
void ColorTracking::CreateFilteredImage(Mat BinaryImage, bool display) {
	//cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);




	// Keep the largest object
	vector<vector<Point>> contours; // Vector for storing contour
	vector<Vec4i> hierarchy;
	int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;
	Mat dst(BinaryImage.rows, BinaryImage.cols, CV_8UC1, Scalar::all(0));


	findContours(theFilteredImage, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE); // Find the contours in the image



	for (int i = 0; i< contours.size(); i++) // iterate through each contour. 
	{
		double a = contourArea(contours[i], false);  //  Find the area of contour // A contour is a one dimensional array
		if (a>largest_area) {
			largest_area = a;
			largest_contour_index = i;                //Store the index of largest contour
													  //bounding_rect = boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
		}

	}


	Scalar color(255, 255, 255);
	//drawContours(dst, contours, largest_contour_index, color, CV_FILLED, 8, hierarchy); // Draw the largest contour using previously stored index.

																						//rectangle(src, bounding_rect, Scalar(0, 255, 0), 1, 8, 0);
	vector<Point> WhitePixels;
	//findNonZero(dst, WhitePixels);
	//imshow("src", src);
	//cout << "Cloud all white pixels: " << WhitePixels.size() << endl;
	// If sufficiently large-> trigger the action
	if (WhitePixels.size() < 500) {
		
	}


	if (display) {
		char str[10];
		char str2[100];
		char*temp = "largest Contour Joint";
		//strcpy_s(str2, temp);
		//_itoa_s(type, str,100,10);
		//strcat_s(str2, str);
		imshow(temp, dst);
	}


}



void ColorTracking::UpdatePoint2DUsingMoments(Mat imgline, bool draw) {
	Moments oMoments = moments(theFilteredImage);
	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	aArea = oMoments.m00;

	// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
	if (aArea > 100)
	{
		//calculate the position of the ball
		posX = dM10 / aArea;
		posY = dM01 / aArea;

		if (prevPosX >= 0 && prevPosY >= 0 && posX >= 0 && posY >= 0 && draw)
		{
			Mat provisionalImg = Mat::zeros(imgline.size(), CV_8UC3);
			//Draw a red line from the previous point to the current point
			line(provisionalImg, Point(posX, posY), Point(prevPosX, prevPosY), Scalar(0, 0, 255), 2);
			imgline = provisionalImg + imgline;
		}

		//cout << "Old Y:" << prevPosY << "New Y :" << posY << endl;
		//cout << "Old X:" << prevPosX << "New X :" << posX << endl;
		prevPosX = posX;
		prevPosY = posY;


	}
	else
		cout << "Ignored a the new position" << endl;
}



/*
void JointLink::ConnectJoints(Joint* An, Joint* Bn) {

	A = An;
	B = Bn;
	Connected = true;
	color = Scalar(140, 300, 140);
}


void JointLink::DrawLink(Mat imgLine) {


	Point origin = Point(A->posX, A->posY);
	Point destiny = Point(B->posX, B->posY);
	line(imgLine, origin, destiny, color, 2);
}

void BodyCapture::setMainDepth(float B) {
	mainDepth = B;
}
*/
