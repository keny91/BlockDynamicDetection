#pragma once
#include "VFunctions.h"
#include <typeinfo>
#include "ColorBlocks.h"


#define OccupiedValue 1
#define NonOccupiedValue 0

using namespace std;


#define VerticalBlockID 1
#define HorizontalBlockID 2
#define BridgeBlockID 3

//Vec3i BridgeColorHSV;
//Vec3i BridgeColorHSV;





// FILLLLLL THIS DATA
typedef struct BoardNode {
public:
	int xPos;
	int yPos;
	int totalSurface;
	int FilledSurface;
	bool checked;
	bool NodeAlreadyPresent;
	Vec2i constrainsStart;
	Vec2i constrainsEnd;

	void InitNode(int x, int y, int xDim, int yDim, Size t);

} _BoardNode;





class VirtualBoard
{

private:
	int cols;
	int rows;
	int pixelPerRow;
	int pixelPerCol;
	Mat ImageTaken;

public:
	_VerticalBlock * VerticalElements;
	_HorizontalBlock * HorizontalElements;
	_Bridge * BridgeElements;
	_BoardNode ** NodeList;

	bool isOcuppied;
	int surface; //
	int occupiedSurface;  // num of pixels occupied


	VirtualBoard(Mat sampleImage, int x = 10, int y = 10);
	~VirtualBoard();

	void FindConnectedElements(int minSize, void* TypeOfElementsArray, Mat ColorSegmentedImage);
	void ClearNodeList();
	void SetNodeOccupiedSurface(_BoardNode theNode);


};