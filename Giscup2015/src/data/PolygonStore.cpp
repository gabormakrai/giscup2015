/*
 * PolygonStore.cpp
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#include "PolygonStore.h"

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

void PolygonStore::doCalculation(int* bannedNodes, NodeStore* nodeStore) {

}


