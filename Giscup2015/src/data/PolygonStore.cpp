/*
 * PolygonStore.cpp
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#include "PolygonStore.h"

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

void PolygonStore::doCalculation(int* bannedNodes, NodeStore* nodeStore) {

	for (int i = 0; i < nodeStore->size; ++i) {
		bannedNodes[i] = 0;
	}

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
}


