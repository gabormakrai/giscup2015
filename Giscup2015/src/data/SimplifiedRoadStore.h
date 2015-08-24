/*
 * SimplifiedRoadStore.h
 *
 *  Created on: 23 Aug 2015
 *      Author: makrai
 */

#ifndef SIMPLIFIEDROADSTORE_H_
#define SIMPLIFIEDROADSTORE_H_

#include "../data/NodeStore.h"
#include "../data/RoadStore.h"

#define ROADSIMPLIFICATION_NORMAL 0
#define ROADSIMPLIFICATION_SIMPLIFIED 1

//#define _SDEBUG_

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

	SimplifiedRoadStore(NodeStore* nodeStore, RoadStore* roadStore, int source, int destination, int mode);
	~SimplifiedRoadStore();
};

#endif /* SIMPLIFIEDROADSTORE_H_ */
