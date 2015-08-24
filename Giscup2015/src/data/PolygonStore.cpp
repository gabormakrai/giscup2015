/*
 * PolygonStore.cpp
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#include "PolygonStore.h"

#include <algorithm>

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

PolygonStore::PolygonStore(int initialStoreSize) {
	size = 0;
	storeSize = initialStoreSize;
	ax = new double[storeSize];
	ay = new double[storeSize];
	bx = new double[storeSize];
	by = new double[storeSize];
	cx = new double[storeSize];
	cy = new double[storeSize];
}


PolygonStore::~PolygonStore() {
	delete [] ax;
	delete [] ay;
	delete [] bx;
	delete [] by;
	delete [] cx;
	delete [] cy;
}

void PolygonStore::addPolygon(double ax, double ay, double bx, double by, double cx, double cy) {
	if (size == storeSize) {
		int newSize = size * 2;
		double* newAX = new double[newSize];
		double* newAY = new double[newSize];
		double* newBX = new double[newSize];
		double* newBY = new double[newSize];
		double* newCX = new double[newSize];
		double* newCY = new double[newSize];

		for (int i = 0; i < size; ++i) {
			newAX[i] = this->ax[i];
			newAY[i] = this->ay[i];
			newBX[i] = this->bx[i];
			newBY[i] = this->by[i];
			newCX[i] = this->cx[i];
			newCY[i] = this->cy[i];
		}

		delete [] this->ax;
		delete [] this->ay;
		delete [] this->bx;
		delete [] this->by;
		delete [] this->cx;
		delete [] this->cy;

		this->ax = newAX;
		this->ay = newAY;
		this->bx = newBX;
		this->by = newBY;
		this->cx = newCX;
		this->cy = newCY;

		storeSize = newSize;
	}

	this->ax[size] = ax;
	this->ay[size] = ay;
	this->bx[size] = bx;
	this->by[size] = by;
	this->cx[size] = cx;
	this->cy[size] = cy;

	++size;
}

inline bool Sign(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y) {
	return ((p1x - p3x) * (p2y - p3y) - (p2x - p3x) * (p1y - p3y)) < 0.0;
}

inline int PointInTriangle(double x, double y, double ax, double ay, double bx, double by, double cx, double cy) {

	bool b1 = Sign(x, y, ax, ay, bx, by);
	bool b2 = Sign(x, y, bx, by, cx, cy);

	if (b1 != b2 ) {
		return 0;
	}

	bool b3 = Sign(x, y, cx, cy, ax, ay);

	if (b2 != b3) {
		return 0;
	}

	return 1;
}


void swap(double* x, int j, int i, int* nodeX) {
	// swap x
    double temp = x[j];
    x[j] = x[i];
    x[i] = temp;
    // swap nodeX
    int temp0 = nodeX[j];
    nodeX[j] = nodeX[i];
    nodeX[i] = temp0;
}

int partition(double* x, int pivot, int left, int right, int* nodeX) {
    swap(x, pivot, left, nodeX);
    pivot = left;
    int i = left + 1;
    for (int j = left + 1; j <= right; j++) {
        if (x[j] < x[pivot]) {
            swap(x, j, i, nodeX);
            i++;
        }
    }
    swap(x, pivot, i - 1, nodeX);
    return i - 1;
}

int choosePivot(double* x, int left, int right) {
	int aIndex = left;
	int bIndex = (left + right) / 2;
	int cIndex = right;

    double a = x[aIndex];
    double b = x[bIndex];
    double c = x[cIndex];
    int largeIndex, smallIndex;
    if (a > b) {
        largeIndex = aIndex;
        smallIndex = bIndex;
    }
    else {
        largeIndex = bIndex;
        smallIndex = aIndex;
    }
    if (c > x[largeIndex]) {
        return largeIndex;
    }
    else {
        if (c < x[smallIndex]) {
            return smallIndex;
        }
        else {
            return cIndex;
        }
    }
}

void quickSort(double* x, int left, int right, int* nodeX) {
    if (left >= right) {
        return;
    }
    int pivot = choosePivot(x, left, right);
    pivot = partition(x, pivot, left, right, nodeX);
    quickSort(x, left, pivot - 1, nodeX);
    quickSort(x, pivot + 1, right, nodeX);
}


int binarySearch(double* x, int first, int last, double element) {
	if (first > last) {
		return last;
	}

	int index;

	int mid = (first + last) / 2;

	if (element == x[mid]) {
		index = mid;
	} else {
		if (element < x[mid]) {
			index = binarySearch(x, first, mid - 1, element);
		} else {
			index = binarySearch(x, mid + 1, last, element);
		}
	}

	return index;
}

void filter(int nodeStoreSize, double* x, int* nodeX, double minX, double maxX, int* nodeCandidates) {
	int minIndex = binarySearch(x, 0, nodeStoreSize - 1, minX);
	if (minIndex != 0) {
		--minIndex;
	}
	int maxIndex = binarySearch(x, 0, nodeStoreSize - 1, maxX);
	for (int i = minIndex; i <= maxIndex; ++i) {
		++nodeCandidates[nodeX[i]];
	}
}

void PolygonStore::doCalculation(int* bannedNodes, NodeStore* nodeStore, int mode) {

	for (int i = 0; i < nodeStore->size; ++i) {
		bannedNodes[i] = 0;
	}

	if (mode == POLYGON_SEQUENTIAL) {

		for (int p = 0; p < size; ++p) {
			double pax = ax[p];
			double pay = ay[p];
			double pbx = bx[p];
			double pby = by[p];
			double pcx = cx[p];
			double pcy = cy[p];

			for (int i = 0; i < nodeStore->size; ++i) {

				if (bannedNodes[i] == 1) {
					continue;
				}

				double x = nodeStore->x[i];
				double y = nodeStore->y[i];

				int banned = PointInTriangle(x, y, pax, pay, pbx, pby, pcx, pcy);
	#ifdef _DEBUG_
				if (banned == 1) {
					cout << "found banned node: " << nodeStore->id[i] << endl;
				}
	#endif
				bannedNodes[i] = banned;
			}
		}
	} else {

		// sort by x
		double* x = new double[nodeStore->storeSize];
		int* nodeX = new int[nodeStore->storeSize];
		for (int i = 0; i < nodeStore->size; ++i) {
			x[i] = nodeStore->x[i];
			nodeX[i] = i;
		}
		quickSort(x, 0, nodeStore->size - 1, nodeX);

		// sort by y
		double* y = new double[nodeStore->storeSize];
		int* nodeY = new int[nodeStore->storeSize];
		for (int i = 0; i < nodeStore->size; ++i) {
			y[i] = nodeStore->y[i];
			nodeY[i] = i;
		}
		quickSort(y, 0, nodeStore->size - 1, nodeY);

//#ifdef _DEBUG_
//		for (int i = 0; i < nodeStore->size; ++i) {
//			cout << "x: " << x[i] << ", nodeX: " << nodeX[i] << endl;
//		}
//#endif

		int* nodeCandidates = new int[nodeStore->storeSize];

		for (int p = 0; p < size; ++p) {

			for (int i = 0; i < nodeStore->size; ++i) {
				nodeCandidates[i] = 0;
			}

			double pax = ax[p];
			double pay = ay[p];
			double pbx = bx[p];
			double pby = by[p];
			double pcx = cx[p];
			double pcy = cy[p];

			double minX = std::min(std::min(pax, pbx), pcx);
			double minY = std::min(std::min(pay, pby), pcy);
			double maxX = std::max(std::max(pax, pbx), pcx);
			double maxY = std::max(std::max(pay, pby), pcy);

			filter(nodeStore->size, x, nodeX, minX, maxX, nodeCandidates);
			filter(nodeStore->size, y, nodeY, minY, maxY, nodeCandidates);

			for (int i = 0; i < nodeStore->size; ++i) {
				if (bannedNodes[i] == 1) {
					continue;
				}

				if (nodeCandidates[i] == 0) {
					continue;
				}

				double x = nodeStore->x[i];
				double y = nodeStore->y[i];

				int banned = PointInTriangle(x, y, pax, pay, pbx, pby, pcx, pcy);
	#ifdef _DEBUG_
				if (banned == 1) {
					cout << "found banned node: " << nodeStore->id[i] << endl;
				}
	#endif
				bannedNodes[i] = banned;

			}
		}

	}
}


