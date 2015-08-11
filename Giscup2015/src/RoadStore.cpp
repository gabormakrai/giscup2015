/*
 * RoadStore.cpp
 *
 *  Created on: 10 Aug 2015
 *      Author: makrai
 */

#include "RoadStore.h"

RoadStore::RoadStore(int initialStoreSize) {
	edgeId = new int[initialStoreSize];
	startNode = new int[initialStoreSize];
	endNode = new int[initialStoreSize];
	length = new double[initialStoreSize];
	speedLimit = new double[initialStoreSize];
	size = 0;
	storeSize = initialStoreSize;
}

void RoadStore::dispose() {
	delete [] edgeId;
	delete [] startNode;
	delete [] endNode;
	delete [] length;
	delete [] speedLimit;
}

void RoadStore::addRoad(int edgeId, int startNode, int endNode, double length, double speedLimit) {
	if (size == storeSize) {
		int newSize = size * 2;
		int* newEdgeId = new int[newSize];
		int* newStartNode = new int[newSize];
		int* newEndNode = new int[newSize];
		double* newLength = new double[newSize];
		double* newSpeedLimit = new double[newSize];

		for (int i = 0; i < size; ++i) {
			newEdgeId[i] = this->edgeId[i];
			newStartNode[i] = this->startNode[i];
			newEndNode[i] = this->endNode[i];
			newLength[i] = this->length[i];
			newSpeedLimit[i] = this->speedLimit[i];
		}

		delete [] this->edgeId;
		delete [] this->startNode;
		delete [] this->endNode;
		delete [] this->length;
		delete [] this->speedLimit;

		this->edgeId = newEdgeId;
		this->startNode = newStartNode;
		this->endNode = newEndNode;
		this->length = newLength;
		this->speedLimit = newSpeedLimit;

		storeSize = newSize;
	}

	this->edgeId[size] = edgeId;
	this->startNode[size] = startNode;
	this->endNode[size] = endNode;
	this->length[size] = length;
	this->speedLimit[size] = speedLimit;

	++size;
}
