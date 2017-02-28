
#include "VFunctions.h"
#include "ColorTracking.h"

void CallBackFunc(int event, int x, int y, int flags, void* userdata);


int * state = new int();
int clickedX = 0;
int clickedY = 0;

Bridge* bridgeElements;
HorizontalBlock * horizontalElements;
VerticalBlock * verticalElements;


int main() {
	Mat image;          //Create Matrix to store image
	Mat capture, dst, postMorhp;
	VideoCapture cap;          //initialize capture
	cap.open(1);
	char* windowName = "window";
	char* captureName = "capture";
	cap >> image;
	cout << "Cam Resolution: " << image.size() << endl;
	cout << "Image Type: " << image.type() << endl;  // type 16 -> CV_8U (uchar 0~255) + C3 (3 CHANNELS)

	// Color Segmentated
	Mat RedFiltImg = Mat::zeros(image.size(), CV_8UC3);
	Mat BlueFiltImg = Mat::zeros(image.size(), CV_8UC3);
	Mat GreenFiltImg = Mat::zeros(image.size(), CV_8UC3);



	namedWindow(windowName, 1);          //create window to show image
	while (1) {
		
		*state = 0;
		cap >> image;          //copy webcam stream to image
		

		imshow(windowName, image);          //print image to screen
		waitKey(33);          //delay 33ms
		setMouseCallback(windowName, CallBackFunc, NULL);



		/*
		In the above application, I have considered that the red object has HUE, SATURATION and VALUE in between 170-180, 160-255, 60-255 respectively. Here the HUE is unique for that specific color distribution of that object. But SATURATION and VALUE may be vary according to the lighting condition of that environment.
		Hue values of basic colors
		Orange  0-22
		Yellow 22- 38
		Green 38-75
		Blue 75-130
		Violet 130-160
		Red 160-179
		*/

		// Red elements filtering
		int iLowHR = 170;
		int iHighHR = 179;

		// Blue elements filtering
		int iLowHB = 75;
		int iHighHB = 130;

		// Green/yellow elements filtering
		int iLowHG = 20;
		int iHighHG = 75;

		/*
		int iLowH = 0;
		int iHighH = 255;
		*/

		int iLowS = 119;  // original 150
		int iHighS = 255;

		int iLowV = 60;
		int iHighV = 255;







		if (*state == 1) {

			capture = image;

			Mat imgHSV, theFilteredImage, croppedImage;
			cvtColor(capture, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV


			/// Create a matrix of the same type and size as src (for dst)
			dst.create(capture.size(), capture.type());

			dst = CVFunctions::GetEdges(capture);

			// Vec3i a = CVFunctions::GetPixelInfo(image,  clickedX, clickedY, true);
			//cout << "Cam Resolution: " << dst.size() << endl;
			namedWindow(captureName, 1);

			
			cvtColor(image, imgHSV, COLOR_BGR2HSV);
			Vec3i colorValue = CVFunctions::GetPixelInfo(imgHSV, clickedX, clickedY, true);
			ColorTracking::GetColorFilteredImage(colorValue, &imgHSV, &theFilteredImage);
			imshow(captureName, theFilteredImage);

			//morphological opening (removes small objects from the foreground)
			
			CVFunctions::MorphologyCloseMat(&theFilteredImage, &postMorhp,10);
			CVFunctions::MorphologyOpenMat(&theFilteredImage, &theFilteredImage, 10);

			// Experiment with
			Rect intFrame = CVFunctions::CreateStandardCenteredSquare(image, 0.75);
			CVFunctions::CropImage(image, &croppedImage, intFrame);



			namedWindow("PostMorphologys", 1);
			cout << "New image size: " <<croppedImage.size() << endl;
			imshow("PostMorphologys", theFilteredImage);
		}
	}




	return 0;
}




void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		clickedX = x;
		clickedY = y;
		*state = 1;
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		//cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		//cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		//cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
	}
}


