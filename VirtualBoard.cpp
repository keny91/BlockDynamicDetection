#include "VirtualBoard.h"



void BoardNode::InitNode(int x, int y, int xDim, int yDim, Size t) {
	xPos = x;
	yPos = y;


	constrainsStart[0] =(t.width / xDim)*x;
	constrainsStart[1] = (t.height / yDim)*y;

	constrainsEnd[0] = (t.width / xDim)*x + (t.width / xDim);
	constrainsEnd[1] = (t.height / yDim)*y + (t.height / yDim);

	totalSurface = (t.width / xDim) * (t.height / yDim);

}

/// <summary>
/// Constructor that specifies the source image, and the number of horizontal and vertical divisions for the board.
/// </summary>
/// <param name="minSize">Minimum size of the element to be considered as an object</param>
VirtualBoard::VirtualBoard(Mat sampleImage, int x, int y)
{
	/*
	VerticalElements = NULL;
	HorizontalElements = NULL;
	BridgeElements = NULL;
	*/

	cols = x;
	rows = y;
	pixelPerCol = (int)sampleImage.cols / x;
	pixelPerRow = (int)sampleImage.rows / y;

	// Initialize the board
	NodeList = new _BoardNode*[y];
	for (int i = 0; i < y; ++i) {
		NodeList[i] = new _BoardNode[x];
		for (int j = 0; j < x; j++)
			NodeList[i][j].InitNode(j, i, x, y, sampleImage.size());   // MAY BE WRONG
	}
		



}


VirtualBoard::~VirtualBoard()
{
}


/// <summary>
/// Determine the number of objects and their type of element we are classifying
/// </summary>
/// <param name="minSize">Minimum size of the element to be considered as an object</param>
/// <param name="TypeOfElementsArray">Specification of the type of block</param>
/// <param name="ColorSegmentedImage">Image filtered by a certain criteria already, is a binary source.</param>
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


/// <summary>
/// Determine the surface populated in a particular node.
/// </summary>
/// <param name="_BoardNode theNode">Node Under Examination</param>
void VirtualBoard::SetNodeOccupiedSurface(_BoardNode theNode) {
	theNode.FilledSurface = 0;
	int pixelAtCol;
	for (int i = theNode.constrainsStart[0]; i < cols; i++) {
		for (int j = theNode.constrainsStart[1]; j < theNode.constrainsEnd[1]; j++) {
			if (ImageTaken.at<int>(i, j) == OccupiedValue)
				theNode.FilledSurface++;
		}
	}

}

