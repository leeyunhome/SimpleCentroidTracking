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
	// explicit �� ���Ϲ�� ��Ƽ�������� ���Ƿ� ����ȯ���ִ� ���� ������
	// TODO : �� �� Ű���带 ������� ���ذ� �ʿ���
	explicit CentroidTracker(int maxDisappeared);

	void register_Object(int cX, int cY);
	// update�� �� (id, (centroid x, centroid y))�� ���� ������Ʈ ��ü�� ����
	// ������ ������ ǥ���ϸ�
	// (int, (int, int)) update(int boxes[][]);
	// c++������ �Լ��� ���ϰ��� �������� �� �� ����
	std::vector<std::pair<int, std::pair<int, int>>> update(std::vector<std::vector<int>> boxes);

	// ������Ʈ�� ��� �� �� �𸣴ϱ� ��Ÿ�ӿ� �����ϵ��� 
	// �޸� �����Ҵ� (c ������ malloc, c++������ std::vector)�� �̿��ؼ� ������Ʈ �� ǥ��
	// ������Ʈ�� ID�� centroid(�ٿ���ڽ��� �߽���)�� ������ �ֵ��� ǥ��
	std::vector<std::pair<int, std::pair<int, int>>> objects;

	std::map<int, std::vector<std::pair<int, int>>> path_keeper;
private:
	int maxDisappeared;

	// ������Ʈ�� ���� ������ ���ؾ��ϴϱ� 
	// Ʈ��Ŀ ��ü�� ���� ������Ʈ�� ���̵� ����� ������ �־����
	int nextObjectID;

	// �� �������� �Ÿ�(��Ŭ���� �Ÿ�)�� ���ϴ� �Լ�
	static double calcDistance(double x1, double y1, double x2, double y2);

	// ����� ������Ʈ�� ������ ������ �־���ϴϱ�? disappeard�� ����� ����
	// std::map�� Ű, �� ���·� �����͸� ������ �� �ִ� �ڷᱸ��
	std::map<int, int> disappeard;
};
#endif // __CENTROIDTRACKER_H__