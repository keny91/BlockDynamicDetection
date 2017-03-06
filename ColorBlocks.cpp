
#include "VirtualBoard.h"




void blockType::SetCoordinates(Vec2i * NewCoors) {
	for (int i = 0; i < squareSize; i++)
		listOfCoordinates[i] = NewCoors[i];  // Maybe need decomposition
}

void blockType::setColor(Vec3i thecolor) {
	color = thecolor; // again might need some ref
}



/* 
At this current time, we have 3 different types of blocks:

		-> Horizontal
		-> Vertical
		-> Bridge

*/

bool blockType::VerifyValidLocations() {

	
	return false;
}


/*  Bridge  */

Bridge::Bridge() {
		typeId = 3;
		squareSize = 5;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 5
		color = BridgeColor;
	}

Bridge::~Bridge(){}

	// Verify that the obtained locations are valid
bool Bridge::VerifyValidLocations() {

		return false;
	}


/*  HorizontalBlock  */

HorizontalBlock::HorizontalBlock() {
		typeId = 2;
		squareSize = 3;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 3
		color = HorizontalColor;
	}
HorizontalBlock::~HorizontalBlock() {}

	// Verify that the obtained locations are valid
	bool HorizontalBlock::VerifyValidLocations() {

		return false;
	}




/*  VerticalBlock  */

	VerticalBlock::VerticalBlock() {
		typeId = 1;
		squareSize = 1;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 1
		color = VerticalColor;
	}
	VerticalBlock::~VerticalBlock() {}

	// Verify that the obtained locations are valid
	bool VerticalBlock::VerifyValidLocations() {

		return false;
	}
