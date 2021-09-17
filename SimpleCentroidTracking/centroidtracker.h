//#pragma once

#ifndef __CENTROIDTRACKER_H__
#define __CENTROIDTRACKER_H__

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <algorithm>

class CentroidTracker 
{
public:
	// explicit 은 리턴밸류 옵티마이저가 임의로 형변환해주는 것을 막아줌
	// TODO : 왜 이 키워드를 썼는지는 이해가 필요함
	explicit CentroidTracker(int maxDisappeared);

	void register_Object(int cX, int cY);
	// update한 후 (id, (centroid x, centroid y))를 가진 오브젝트 자체를 리턴
	// 다음을 간단히 표현하면
	// (int, (int, int)) update(int boxes[][]);
	// c++에서는 함수의 리턴값이 여러개가 될 수 있음
	std::vector<std::pair<int, std::pair<int, int>>> update(std::vector<std::vector<int>> boxes);

	// 오브젝트는 몇개가 될 지 모르니까 런타임에 결정하도록 
	// 메모리 동적할당 (c 에서는 malloc, c++에서는 std::vector)를 이용해서 오브젝트 를 표현
	// 오브젝트는 ID와 centroid(바운딩박스의 중심점)를 가지고 있도록 표현
	std::vector<std::pair<int, std::pair<int, int>>> objects;

	std::map<int, std::vector<std::pair<int, int>>> path_keeper;
private:
	int maxDisappeared;

	// 오브젝트가 같은 것인지 비교해야하니까 
	// 트래커 자체는 다음 오브젝트의 아이디도 멤버로 가지고 있어야함
	int nextObjectID;

	// 두 점사이의 거리(유클리드 거리)를 구하는 함수
	static double calcDistance(double x1, double y1, double x2, double y2);

	// 사라진 오브젝트의 정보도 가지고 있어야하니까? disappeard도 멤버로 존재
	// std::map은 키, 값 형태로 데이터를 저장할 수 있는 자료구조
	std::map<int, int> disappeard;
};
#endif // __CENTROIDTRACKER_H__