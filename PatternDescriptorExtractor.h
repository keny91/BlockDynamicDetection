#pragma once

#include "VFunctions.h"
#include <cmath>

using namespace cv::xfeatures2d;
using namespace std;

class PatternDescriptorExtractor
{
public:
	PatternDescriptorExtractor(Mat theObject, Mat theScene, int minHessian = 700);
	PatternDescriptorExtractor();
	~PatternDescriptorExtractor();

	double max_dist, min_dist, max_physical_distance;


protected:
	Mat Scene, Object;
	Mat img_keypoints_object, img_keypoints_scene;
	Mat descriptors_object, descriptors_scene;
	int HessianTh;

	// Surf descriptor extractor
	Ptr<cv::xfeatures2d::SurfFeatureDetector> detector; // Detector
	Ptr<cv::xfeatures2d::SurfFeatureDetector> extractor; // Extractor
	vector<KeyPoint> keypoints_object, keypoints_scene;  // keypoints

	FlannBasedMatcher matcher;
	vector< DMatch > matches;
	 
	vector< DMatch > good_matches;  // just the selected objects


	void FindDescriptors();
	void InitDetectors(int minHessian);
	void GetMatches();
	void DetermineGoodMatches();
	void DetermineHomeografyOfSet();
	void DetermineCornersOfSet(vector<DMatch> SetOfMatches, Mat Homeografy);

};

