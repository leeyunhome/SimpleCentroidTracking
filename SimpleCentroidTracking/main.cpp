#include <iostream>
//#include "centroidtracker.h"
#include "centroidtracker_c.h"
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <typeindex>

using namespace cv;
using namespace std;

//void calcCentroid(int, int, int, int, int* a, int* b);

int main()
{
	printf("SimpleCentroidTracking");

	// cpp class implementation
	//auto centroidTracker = new CentroidTracker(20);

	// c structure implementation
	ObjectTracker ot;

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
		auto inputBlob = dnn::blobFromImage(cameraFrame, 1.0, Size(400, 300), Scalar(104.0, 177.0, 123.0));

		net.setInput(inputBlob);
		auto detection = net.forward("detection_out");
		Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

		vector<vector<int>> boxes;

		float confidenceThreshold = 0.2;
		for (int i = 0; i < detectionMat.rows; i++)
		{
			float confidence = detectionMat.at<float>(i, 2);

			if (confidence > confidenceThreshold)
			{
				int xLeftTop = static_cast<int>(detectionMat.at<float>(i, 3) * cameraFrame.cols);
				int yLeftTop = static_cast<int>(detectionMat.at<float>(i, 4) * cameraFrame.rows);
				int xRightBottom = static_cast<int>(detectionMat.at<float>(i, 5) * cameraFrame.cols);
				int yRightBottom = static_cast<int>(detectionMat.at<float>(i, 6) * cameraFrame.rows);

				int centroid_x = 0;
				int centroid_y = 0;

				//calcCentroid(xLeftTop, yLeftTop, xRightBottom, yRightBottom, &centroid_x, &centroid_y);

				Rect object((int)xLeftTop, (int)yLeftTop, (int)(xRightBottom - xLeftTop),
					(int)(yRightBottom - yLeftTop));

				//drawMarker(cameraFrame, Point(centroid_x, centroid_y), Scalar(255, 0, 0), MARKER_SQUARE);
				rectangle(cameraFrame, object, Scalar(255, 255, 0), 2);

				boxes.insert(boxes.end(), { xLeftTop, yLeftTop, xRightBottom, yRightBottom });
			}
		}

		//std::cout << typeid(boxes).name() << endl;
		
		for (auto b : boxes)
		{
			int cX = int((b[0] + b[2]) * 0.5);
			int cY = int((b[1] + b[3]) * 0.5);
			ot.objects->x1 = cX;
			//inputCentroids.push_back(make_pair(cX, cY));
		}

		printf("ot.objects->x1 : %f\n", ot.objects->x1);

		//ot.objects->x1 = boxes.;
		
		/*auto objects = centroidTracker->update(boxes);

		if (!objects.empty())
		{
			for (auto obj : objects)
			{
				circle(cameraFrame, Point(obj.second.first, obj.second.second), 4, Scalar(255, 0, 0), -1);
				string ID = std::to_string(obj.first);
				cv::putText(cameraFrame, ID, Point(obj.second.first - 10, obj.second.second - 10),
					FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 255, 0), 2);
			}
		}*/

		imshow("Detection", cameraFrame);

		char c = (char)waitKey(15);
		if (c == 27)
			break;
	}

	return 0;
}

//void calcCentroid(int xLeftTop, int yLeftTop, int xRightBottom, int yRightBottom, int* a, int* b)
//{
//	*a = xLeftTop + (xRightBottom - xLeftTop) * 0.5;
//	*b = yLeftTop + (yRightBottom - yLeftTop) * 0.5;
//
//	return;
//}

