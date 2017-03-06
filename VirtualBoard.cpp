#include "VirtualBoard.h"



VirtualBoard::VirtualBoard(int x, int y)
{
	/*
	VerticalElements = NULL;
	HorizontalElements = NULL;
	BridgeElements = NULL;
	*/

	cols = x;
	rows = y;


	// Initialize the board
	NodeList = new _BoardNode*[y];
	for (int i = 0; i < y; ++i)
		NodeList[i] = new _BoardNode[x];


}


VirtualBoard::~VirtualBoard()
{
}



void VirtualBoard::FindConnectedElements(int minSize, void* TypeOfElementsArray, Mat ColorSegmentedImage) {

	

	// Find the amount of elements present
	Mat labeledImage = Mat(ColorSegmentedImage.size(), CV_8UC1, Scalar::all(0));
	int NumberOfElements = connectedComponents(ColorSegmentedImage, labeledImage,8);

	vector<Vec3i> colors(NumberOfElements);

	// Create colors for representation in debugging process
	colors[0] = Vec3i(0, 0, 0);  //background
	for (int label = 1; label < NumberOfElements; ++label) {  // the label 0 is the bg.
		colors[label] = Vec3b((rand() & 255), (rand() & 255), (rand() & 255));
	}
	
	//
	Mat dst(ColorSegmentedImage.size(), CV_8UC3);
	for (int r = 0; r < dst.rows; ++r) {
		for (int c = 0; c < dst.cols; ++c) {
			int label = labeledImage.at<int>(r, c);
			Vec3b &pixel = dst.at<Vec3b>(r, c);
			pixel = colors[label];
		}
	}



	// Determine the final number of Elements to create (after recount)
	int NumElements = NumberOfElements - 1;


	// Debug 
	imshow("Connected Components", dst);


	// Determine what kind of element are we storing 
	Block* theProv = (Block*)TypeOfElementsArray;

		// Vertical block
		if (theProv->typeId == (int)VerticalBlockID) {
			_VerticalBlock thePTR = *((VerticalBlockPtr)TypeOfElementsArray);
			VerticalElements = new _VerticalBlock[NumElements];
			cout << "A VerticalBlock with size: " << NumElements << endl;
		}
		// bridge block
		else if (theProv->typeId == (int)BridgeBlockID) {
			_Bridge thePTR = *((BridgePtr)TypeOfElementsArray);
			BridgeElements = new _Bridge[NumElements];
			cout << "A Bridge with size: " << NumElements << endl;

		}
		// Horizontal block
		else if (theProv->typeId == (int)HorizontalBlockID) {
			_HorizontalBlock thePTR = *((HorizontalBlockPtr)TypeOfElementsArray);
			HorizontalElements = new _HorizontalBlock[NumElements];
			cout << "A HorizontalBlock with size: " << NumElements << endl;
		}
		else {
			cout << "Block ID not detected, UNKNOWN BLOCK" << endl;
			//void* thePTR;
			return;
		}

}



