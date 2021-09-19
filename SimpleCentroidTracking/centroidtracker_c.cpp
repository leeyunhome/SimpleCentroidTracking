#include "centroidtracker_c.h"
#include <math.h>

double calcDistance(ObjectTracker* ot)
{
	double x = ot->objects->x1 - ot->objects->x2;
	double y = ot->objects->y1 - ot->objects->y2;
	double dist = sqrt((x * x) + (y * y));

	return dist;
}

void update(vector<vector<int>> boxes, ObjectTracker* ot)
{
	/*if (boxes.empty())
	{
		auto it = this->disappeard.begin();
		while (it != this->disappeard.end())
		{
			it->second++;
			if (it->second > this->maxDisappeared)
			{
				this->objects.erase(remove_if(this->objects.begin(), this->objects.end(), [it](auto& elem)
					{
						return elem.first == it->first;
					}), this->objects.end());

				this->path_keeper.erase(it->first);

				it = this->disappeard.erase(it);
			}
			else
			{
				++it;
			}
		}

		return this->objects;
	}*/
}

void register_Object(ObjectTracker* ot, int cX, int cY, int nextObjectID)
{
	ot->nextObjectID = nextObjectID;

}