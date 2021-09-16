#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	//printf("SimpleCentroidTracking");
	std::cout << "SimpleCentroidTracker" << std::endl;

	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "Cannot open camera";
	}

	String modelTxt = "model/deploy.prototxt";
	String modelBin = "model/res10_300x300_ssd_iter_140000.caffemodel";

	std::cout << "Loading ai model.." << endl;
	auto net = dnn::readNetFromCaffe(modelTxt, modelBin);

	std::cout << "Starting video stream" << std::endl;
	while (cap.isOpened())
	{
		Mat cameraFrame;
		cap.read(cameraFrame);

		resize(cameraFrame, cameraFrame, Size(400, 300));

		imshow("Detection", cameraFrame);
		char c = (char)waitKey(15);
		if (c == 27)
			break;
	}

	return 0;
}


