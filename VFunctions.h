#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include ".\opencv2\calib3d.hpp"
#include ".\opencv2\core\core.hpp"
#include <.\opencv2\highgui\highgui.hpp>
#include ".\opencv2\imgproc\imgproc.hpp"
#include ".\opencv2\imgproc.hpp"

#include <iostream>


using namespace cv;
using namespace std;

class CVFunctions
{
public:
	CVFunctions();
	~CVFunctions();

	static Mat GetEdges(Mat src_gray);
	static Mat MorphologyOpenMat(Mat image, int maskSize = 5);
	static Mat MorphologyCloseMat(Mat image, int maskSize = 5);
	static Vec3i GetPixelInfo(Mat TargetImage, int x, int y, bool displayConsoleInfo = false);
	static Mat CreateFilteredImage(Mat Image);
};


// Declaration of Block structs

struct blockType;
typedef struct blockType Block;
struct Bridge;
typedef struct Bridge Bridge;
struct HorizontalBlock;
typedef struct HorizontalBlock HorizontalBlock;
struct VerticalBlock;
typedef struct VerticalBlock VerticalBlock;
