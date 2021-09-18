#pragma once

#include <stdio.h>
#include <stdlib.h>
#define MAX_OBJECT 50
// 구조체 패딩 고려
typedef struct _object
{
	double x1;
	double y1;
	double x2;
	double y2;
} Object;

typedef struct _object_tracker
{
	Object* objects;
	int maxDisappeared;
	int nextObjectID;
	

} ObjectTracker;

double calcDistance(ObjectTracker* ot);
