#include "centroidtracker_c2.h"
#include <math.h>

//double calcDistance(ObjectTracker* ot)
//{
//	//double x = ot->objects->x1 - ot->objects->x2;
//	//double y = ot->objects->y1 - ot->objects->y2;
//	//double dist = sqrt((x * x) + (y * y));
//
//	//return dist;
//}

void update2(vector<vector<int>> boxes, ObjectTracker* ot)
{
	if (boxes.empty())
	{
		auto it = ot->disappeard.begin();
		while (it != ot->disappeard.end())
		{
			it->second++;
			if (it->second > ot->maxDisappeared)
			{
				ot->objects.erase(remove_if(ot->objects.begin(), ot->objects.end(), [it](auto& elem)
					{
						return elem.first == it->first;
					}), ot->objects.end());

				//ot->path_keeper.erase(it->first);

				it = ot->disappeard.erase(it);
			}
			else
			{
				++it;
			}
		}

		//return this->objects;
	}

	vector<pair<int, int>> inputCentroids;
	ot->nextObjectID = 0;
	int nextObjectId = ot->nextObjectID;

	for (auto b : boxes)
	{
		int cX = int((b[0] + b[2]) * 0.5);
		int cY = int((b[1] + b[3]) * 0.5);
		inputCentroids.push_back(make_pair(cX, cY));
	}
	//if we are currently not tracking any objects take the input centroids and register each of them
	if (ot->objects.empty())
	{
		for (auto i : inputCentroids)
		{
			register_Object2(ot, i.first, i.second, nextObjectId);
		}
	}
	// otherwise, there are currently tracking objects so we need to try to match the
	// input centroids to existing object centroids
	else
	{
		vector<int> objectIDs;
		vector<pair<int, int>> objectCentroids;
		for (auto object : ot->objects)
		{
			objectIDs.push_back(object.first);
			objectCentroids.push_back(make_pair(object.second.first, object.second.second));
		}
	}

	// loading path tracking points
	if (!ot->objects.empty())
	{
		for (auto obj : ot->objects)
		{
			if (ot->path_keeper[obj.first].size() > 30)
			{
				ot->path_keeper[obj.first].erase(ot->path_keeper[obj.first].begin());
			}
			ot->path_keeper[obj.first].push_back(make_pair(obj.second.first, obj.second.second));
		}
	}

	fprintf(stderr, "%s=%d\n", __FUNCTION__, __LINE__);
}

void register_Object2(ObjectTracker* ot, int cX, int cY, int nextObjectID)
{
	fprintf(stderr, "%s=%d\n", __FUNCTION__, __LINE__);
	int object_ID = ot->nextObjectID;
	ot->objects.push_back({ object_ID, {cX, cY} });
	ot->disappeard.insert({ object_ID, 0 });
	ot->nextObjectID += 1;
	fprintf(stderr, "%s=%d\n", __FUNCTION__, __LINE__);
}