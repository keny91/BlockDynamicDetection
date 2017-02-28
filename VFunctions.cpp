#include "VFunctions.h"





CVFunctions::CVFunctions()
{

}


CVFunctions::~CVFunctions()
{
}


 Mat CVFunctions::GetEdges(Mat src) {



	/// Reduce noise with a kernel 3x3
	int edgeThresh = 1;
	int lowThreshold= 30;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;
	Mat detected_edges, dst;
	Mat src_gray;



	/// Convert the image to grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, detected_edges, Size(3, 3));

	/// Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);

	src.copyTo(dst, detected_edges); // Copy
	return dst;

}






 // morphological opening (removes small objects from the foreground)
void CVFunctions::MorphologyOpenMat(Mat* image, Mat *OutputImage,int maskSize) {
	erode(*image, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	dilate(*OutputImage, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));

 }



// morphological closing (removes small holes from the foreground)
void CVFunctions::MorphologyCloseMat(Mat* image, Mat *OutputImage, int maskSize) {
	dilate(*image, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	erode(*OutputImage, *OutputImage, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
 }


// 
Vec3i CVFunctions::GetPixelInfo(Mat TargetImage, int x, int y ,bool displayConsoleInfo) {

	cout << "clicked on: " << x << "," << y << endl;
	cv::Vec3i pixel = TargetImage.at<cv::Vec3b>(y, x); // read pixel (x,y)
	if (displayConsoleInfo) {
		cout << "Pixel Value: " << pixel[0] << "," << pixel[1] << "," << pixel[2] << endl;
	}

	return pixel;
}

//
void CVFunctions::CropImage(Mat theimage, Mat* theOutput ,Rect internalFrame) {
	*theOutput = theimage(internalFrame);

}
// 

Rect CVFunctions::DetermineCenteredRectangle(Mat theimage, int x, int y) {
	
	Size s = theimage.size();
	int Yo = s.height;
	int Xo = s.width;

	int Xdist = (Xo - x) / 2;
	int Ydist = (Yo - y) / 2;
	Rect intFrame(Xdist, Ydist, x, y);
	return intFrame;

}



// This automatically detects the number of pixels that should
Rect CVFunctions::CreateStandardCenteredSquare(Mat theimage, float VerticalScreenPercent) {
	Size s = theimage.size();
	int Yo = s.height;
	float YoF = (float)Yo;
	//int Xo = s.width;
	int y = (int)(VerticalScreenPercent * YoF);
	int x = y;
	Rect estim = DetermineCenteredRectangle(theimage, x, y);

	return estim;

}