#include "centroidtracker_c.h"
#include <math.h>

double calcDistance(ObjectTracker* ot)
{
	double x = ot->objects->x1 - ot->objects->x2;
	double y = ot->objects->y1 - ot->objects->y2;
	double dist = sqrt((x * x) + (y * y));

	return dist;
}

