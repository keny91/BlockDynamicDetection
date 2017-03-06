#pragma once



// Values to be modified
#define BridgeColorHue 6
#define VerticalColorHue 110
#define HorizontalColorHue 40

const Vec3i BridgeColor = Vec3i(BridgeColorHue, 150, 150);
const Vec3i VerticalColor = Vec3i(VerticalColorHue, 150, 150);
const Vec3i HorizontalColor = Vec3i(HorizontalColorHue, 150, 150);


// Declaration of Block structs

typedef struct blockType {
protected:
	virtual bool VerifyValidLocations();

	// invarible yet accessible


public:  // change later to protected


	int typeId;
	int squareSize;
	Vec3b color;
	Vec2i * listOfCoordinates; // The locations should be indicated by start(x,y) and end (x,y) 2 vec2i vectors


	void SetCoordinates(Vec2i * NewCoors);
	void setColor(Vec3i thecolor);
} Block;




//typedef struct blockType Block;

typedef struct Bridge : Block {
	Bridge();
	~Bridge();

	// Verify that the obtained locations are valid
	bool VerifyValidLocations();

} _Bridge;


//typedef struct Bridge _Bridge;
typedef struct Bridge* BridgePtr;




typedef struct HorizontalBlock : Block {
	HorizontalBlock();
	~HorizontalBlock();
	// Verify that the obtained locations are valid
	bool VerifyValidLocations();
} _HorizontalBlock;

//typedef struct HorizontalBlock _HorizontalBlock;
typedef struct HorizontalBlock* HorizontalBlockPtr;





typedef struct VerticalBlock : Block {
	VerticalBlock();
	~VerticalBlock();

	// Verify that the obtained locations are valid
	bool VerifyValidLocations();
} _VerticalBlock;
//typedef struct VerticalBlock _VerticalBlock;
typedef struct VerticalBlock* VerticalBlockPtr;


