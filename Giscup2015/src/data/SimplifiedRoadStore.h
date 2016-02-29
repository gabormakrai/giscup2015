/*
 * SimplifiedRoadStore.h
 *
 *  Created on: 23 Aug 2015
 *      Author: Gabor Makrai
 *
 */

#ifndef SIMPLIFIEDROADSTORE_H_
#define SIMPLIFIEDROADSTORE_H_

#include "../data/NodeStore.h"
#include "../data/RoadStore.h"

#define ROADSIMPLIFICATION_NORMAL 0
#define ROADSIMPLIFICATION_SIMPLIFIED 1

//#define _SDEBUG_

/**
 *
 * SimplifiedRoadStore class contains the simplification algorithm in its constructor
 * It converts the Roadstore into a graph (in neighbourhood list form) which then can be used later
 * by the NeighbourDataBase class
 *
 */
class SimplifiedRoadStore {
public:
	int* startNode;
	int* endNode;
	double* length;
	double* time;
	int storeSize;
	int size;

	int* seekOffset;
	int* seekCount;
	int* seek;
	int* seekLength;

	SimplifiedRoadStore(NodeStore* nodeStore, RoadStore* roadStore, int source, int destination, int mode,
		int* startNode, int* endNode, double* length, double* time, int* seekOffset, int* seekCount, int* seek, int* seekLength,
		int* array1, int* array2, int* array3, int* array4, int* array5, int* array6);
	~SimplifiedRoadStore();
};

#endif /* SIMPLIFIEDROADSTORE_H_ */
