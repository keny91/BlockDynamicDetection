#pragma once
#include "VFunctions.h"
#include <typeinfo>
#include "ColorBlocks.h"

using namespace std;


#define VerticalBlockID 1
#define HorizontalBlockID 2
#define BridgeBlockID 3

//Vec3i BridgeColorHSV;
//Vec3i BridgeColorHSV;





// FILLLLLL THIS DATA
typedef struct BoardNode {
public:
	int totalSurface;
	int FilledSurface;
	bool checked;
	bool NodeAlreadyPresent;
	bool containsStart ;
	bool containsEnd;

} _BoardNode;





class VirtualBoard
{

private:
	int cols;
	int rows;

public:
	_VerticalBlock * VerticalElements;
	_HorizontalBlock * HorizontalElements;
	_Bridge * BridgeElements;
	_BoardNode ** NodeList;



	VirtualBoard(int x = 10, int y = 10);
	~VirtualBoard();

	void FindConnectedElements(int minSize, void* TypeOfElementsArray, Mat ColorSegmentedImage);
	void ClearNodeList();



};