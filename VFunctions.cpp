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
Mat CVFunctions::MorphologyOpenMat(Mat image, int maskSize) {
	erode(image, image, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	dilate(image, image, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	return image;
 }



// morphological closing (removes small holes from the foreground)
Mat CVFunctions::MorphologyCloseMat(Mat image , int maskSize) {
	dilate(image, image, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	erode(image, image, getStructuringElement(MORPH_ELLIPSE, Size(maskSize, maskSize)));
	return image;
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
Mat CVFunctions::CreateFilteredImage(Mat Image) {

}

// 