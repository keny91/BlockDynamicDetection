
#include "VFunctions.h"

struct blockType {
protected:
	virtual bool VerifyValidLocations();


public:  // change later to protected
	int typeId;
	int squareSize;
	Vec2i * listOfCoordinates;
	Vec3b color;

	void SetCoordinates(Vec2i * NewCoors) {
		for (int i = 0; i < squareSize; i++)
			listOfCoordinates[i] = NewCoors[i];  // Maybe need decomposition
	}

	void setColor(Vec3i thecolor) {
		color = thecolor; // again might need some ref
	}

	

};



/* At this current time, we have 3 different types of blocks */

struct Bridge : Block {
	Bridge() {
		typeId = 3;
		squareSize = 5;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 5
		
	}

	// Verifiy that the obtained locations are valid
	bool VerifyValidLocations() {

		return false;
	}

};


struct HorizontalBlock : Block {
	HorizontalBlock() {
		typeId = 2;
		squareSize = 3;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 3
	}


	// Verifiy that the obtained locations are valid
	bool VerifyValidLocations() {

		return false;
	}
};

struct VerticalBlock : Block {
	VerticalBlock() {
		typeId = 1;
		squareSize = 1;
		listOfCoordinates = new Vec2i[squareSize];  // supposed to be an array of 3
	}


	// Verifiy that the obtained locations are valid
	bool VerifyValidLocations() {

		return false;
	}
};