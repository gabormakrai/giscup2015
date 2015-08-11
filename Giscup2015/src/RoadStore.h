/*
 * RoadStore.h
 *
 *  Created on: 10 Aug 2015
 *      Author: makrai
 */

#ifndef ROADSTORE_H_
#define ROADSTORE_H_

class RoadStore {
public:
	int* edgeId;
	int* startNode;
	int* endNode;
	double* length;
	double* speedLimit;
	int storeSize;
	int size;
	RoadStore(int initialStoreSize);
	void addRoad(int edgeId, int startNode, int endNode, double length, double speedLimit);
	void dispose();
};


#endif /* ROADSTORE_H_ */
