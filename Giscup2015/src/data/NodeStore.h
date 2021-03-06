/*
 * NodeStore.h
 *
 *  Created on: 11 Aug 2015
 *      Author: Gabor Makrai
 */

#ifndef NODESTORE_H_
#define NODESTORE_H_

//#define _DEBUG_

#include <stdlib.h>

/**
 *
 * Nodestore class for storing, sorting nodes and for calculating distance between them
 *
 */
class NodeStore {
public:
	double* x;
	double* y;
	int* id;
	int size;
	int storeSize;
	NodeStore(int initialStoreSize);
	~NodeStore();
	void addNode(int id, double x, double y);
	void sort();
	int getIndex(int id);
	double (*distanceFunction)(double, double);
	double distance(int i1, int i2);
	void setDistanceFunction(int mode);
};

#endif /* NODESTORE_H_ */
