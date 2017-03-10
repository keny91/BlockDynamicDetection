#include "PatternDescriptorExtractor.h"



PatternDescriptorExtractor::PatternDescriptorExtractor()
{
}


PatternDescriptorExtractor::PatternDescriptorExtractor(Mat theObject, Mat theScene, int minHessian) {
	InitDetectors(minHessian);
	Scene = theScene;
	Object = theObject;
}


void PatternDescriptorExtractor::InitDetectors(int minHessian) {
	HessianTh = minHessian;

	detector = SurfFeatureDetector::create(minHessian);
	extractor = SurfFeatureDetector::create(minHessian);
}

PatternDescriptorExtractor::~PatternDescriptorExtractor()
{

}



void PatternDescriptorExtractor::FindDescriptors() {


	if (detector == NULL && extractor == NULL) {
		cout << "ERROR: Detector and/or extractor not initialized." << endl;
	}
	else {
		// Get the keypoints in both images
		detector->detect(Object, keypoints_object);
		detector->detect(Scene, keypoints_scene);

		// Get the descriptors in both images
		extractor->compute(Object, keypoints_object, descriptors_object);
		extractor->compute(Scene, keypoints_scene, descriptors_scene);

		double dist;
		double Physicaldist = 0;

		for (int i = 0; i < descriptors_object.rows; i++)
		{
			double x = keypoints_object[i].pt.x;
			double y = keypoints_object[i].pt.y;
			Physicaldist = sqrt(pow((x - keypoints_object[0].pt.x),2) - pow((y - keypoints_object[0].pt.y),2)); // sqrt(dx^2 +dy^2)
			
			// Determine what is the maximum distance from the different keypoints inside the object
			if (Physicaldist > max_physical_distance)
				max_physical_distance = Physicaldist;
			
			dist = matches[i].distance;
			if (dist < min_dist)
				min_dist = dist;
			if (dist > max_dist)
				max_dist = dist;
		}
	
	}


}

void PatternDescriptorExtractor::GetMatches() {

	matcher.match(descriptors_object, descriptors_scene, matches);

}


void PatternDescriptorExtractor::DetermineGoodMatches() {

	for (int i = 0; i < descriptors_object.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

}