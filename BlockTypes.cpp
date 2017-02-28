
#include "VFunctions.h"

struct blockType {
public:  // change later to protected
	int typeId;
	int squareSize;
	Vec2i * listOfCoordinates;
	Vec3b color;

	void SetCoordinates(Vec2i * NewCoors) {

	}

};



/* At this current time, we have 3 different types of blocks */

struct Bridge : Block {
	Bridge() {
		typeId = 3;
		squareSize = 5;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 5
	}

};


struct HorizontalBlock : Block {
	HorizontalBlock() {
		typeId = 2;
		squareSize = 3;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 3
	}

};

struct VerticalBlock : Block {
	VerticalBlock() {
		typeId = 1;
		squareSize = 1;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 3
	}

};