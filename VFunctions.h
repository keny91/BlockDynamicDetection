#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "./opencv2/calib3d.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
//#include "opencv2/gpu/gpu.hpp"


#include <iostream>


using namespace cv;
using namespace std;

class CVFunctions
{
public:
	CVFunctions();
	~CVFunctions();

	static Mat GetEdges(Mat src_gray);
	static void MorphologyOpenMat(Mat* image, Mat *OutputImage, int maskSize = 5);
	static void MorphologyCloseMat(Mat* image, Mat *OutputImage, int maskSize = 5);
	static Vec3i GetPixelInfo(Mat TargetImage, int x, int y, bool displayConsoleInfo = false);
	static void CropImage(Mat image, Mat* Outputimage, Rect internalFrame);
	static Rect DetermineCenteredRectangle(Mat theimage, int x, int y);
	static Rect CreateStandardCenteredSquare(Mat theimage, float VerticalScreenPercent);
};

