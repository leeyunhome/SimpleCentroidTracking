#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define MAX_OBJECT 50

using namespace std;

// TODO : 구조체 사이즈에 영향을 미치는 패딩 고려
typedef struct _object
{
	double x1;
	double y1;
	double x2;
	double y2;

	// centroid x coord, centroid y coord
	double cX;
	double cY;
} Object;

typedef struct _object_tracker
{
	Object objects[MAX_OBJECT];
	int maxDisappeared;
	int nextObjectID;
	std::map<int, int> disappeard;

	// ...
} ObjectTracker;

// ObjectTracker 연산
double calcDistance(ObjectTracker* ot);

//std::vector<std::pair<int, std::pair<int, int>>> CentroidTracker::update(vector<vector<int>> boxes)
void update(vector<vector<int>> boxes, ObjectTracker *ot);
