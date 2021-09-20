#include <iostream>
//#include "centroidtracker.h"
//#include "centroidtracker_c.h"
#include "centroidtracker_c2.h"
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <typeindex>

using namespace cv;
using namespace std;

//void calcCentroid(int, int, int, int, int* a, int* b);

int main()
{
	printf("SimpleCentroidTracking\n");

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

		// 바운딩 박스를 하나씩 꺼내서 중심(centroid) 계산
		/*
		for (auto b : boxes)
		{
			int cX = int((b[0] + b[2]) * 0.5);
			int cY = int((b[1] + b[3]) * 0.5);
			ot.objects->cX = cX;
			ot.objects->cY = cY;
			//inputCentroids.push_back(make_pair(cX, cY));
		}

		printf("ot.objects->cX : %f, ot.objects->cY : %f\n", ot.objects->cX, ot.objects->cY);

		circle(cameraFrame, Point(ot.objects->cX, ot.objects->cY), 4, Scalar(255, 0, 0), -1);
		*/

		fprintf(stderr, "%s=%d\n", __FUNCTION__, __LINE__);

		ObjectTracker ot[5];

		update2(boxes, ot);

		fprintf(stderr, "%s=%d\n", __FUNCTION__, __LINE__);

		if (!ot->objects.empty())
		{
			for (auto obj : ot->objects)
			{
				circle(cameraFrame, Point(obj.second.first, obj.second.second), 4, Scalar(255, 0, 0), -1);
				string ID = std::to_string(obj.first);
				cv::putText(cameraFrame, ID, Point(obj.second.first - 10, obj.second.second - 10),
					FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 255, 0), 2);
			}
		}
		/*{
			vector<int> objectIDs;
			vector<pair<int, int>> objectCentroids;
			for (auto object : ot.objects)
			{
				objectIDs.push_back(object.first);
				objectCentroids.push_back(make_pair(object.second.first, object.second.second));
				const int max_string = 50;
				char ID[max_string];
				circle(cameraFrame, Point(object.second.first, object.second.second), 4, Scalar(255, 0, 0), -1);
				sprintf(ID, "ID: %d", object.first);
				std::cout << "ID : " << ID << std::endl;
				cv::putText(cameraFrame, ID, Point(object.second.first - 10, object.second.second - 10),
					FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 255, 0), 2);
			}
		}*/
		

		//string ID = std::to_string(obj.first);
		//cv::putText(cameraFrame, ID, Point(obj.second.first - 10, obj.second.second - 10),
		//	FONT_HERSHEY_COMPLEX, 0.5, Scalar(0, 255, 0), 2);

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

