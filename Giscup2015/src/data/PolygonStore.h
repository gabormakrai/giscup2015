/*
 * PolygonStore.h
 *
 *  Created on: 22 Aug 2015
 *      Author: Gabor Makrai
 */

#ifndef POLYGONSTORE_H_
#define POLYGONSTORE_H_

//#define _DEBUG_

#define POLYGON_SEQUENTIAL 0
#define POLYGON_SORT 1

#include "NodeStore.h"

/**
 *
 * Simple storage class for storing polygons.
 * As the competition focuses only on convex polygons, after parsing each polygon, a simple polygon triangulation process is executed to store only
 * triangles.
 * Also the class can find the nodes/verticies which are covered by the polygons(/triangles) so it can create a ban list.
 *
 */

class PolygonStore {
public:
	double* ax;
	double* ay;
	double* bx;
	double* by;
	double* cx;
	double* cy;
	int size;
	int storeSize;
	PolygonStore(int initialStoreSize);
	~PolygonStore();
	void addPolygon(double ax, double ay, double bx, double by, double cx, double cy);
	void doCalculation(int* bannedNodes, NodeStore* nodeStore, int mode);
};


#endif /* POLYGONSTORE_H_ */
