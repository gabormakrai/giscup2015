/*
 * RoadStore.h
 *
 *  Created on: 10 Aug 2015
 *      Author: makrai
 */

#ifndef ROADSTORE_H_
#define ROADSTORE_H_

#include "NodeStore.h"

class RoadStore {
public:
	int* roadId;
	int* startNode;
	int* endNode;
	double* length;
	double* speedLimit;
	int* positionInFile;
	int storeSize;
	int size;
	RoadStore(int initialStoreSize);
	~RoadStore();
	void addRoad(int edgeId, int startNode, int endNode, double length, double speedLimit, int positionInFile);
	void reassignNodeIds(NodeStore* nodeStore);
};


#endif /* ROADSTORE_H_ */
