/*
 * RoadStore.cpp
 *
 *  Created on: 10 Aug 2015
 *      Author: makrai
 */

#include "RoadStore.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

RoadStore::RoadStore(int initialStoreSize) {
	roadId = new int[initialStoreSize];
	startNode = new int[initialStoreSize];
	endNode = new int[initialStoreSize];
	length = new double[initialStoreSize];
	speedLimit = new double[initialStoreSize];
	positionInFile = new int[initialStoreSize];
	lengthInFile = new int[initialStoreSize];
	size = 0;
	storeSize = initialStoreSize;
}

RoadStore::~RoadStore() {
	delete [] roadId;
	delete [] startNode;
	delete [] endNode;
	delete [] length;
	delete [] speedLimit;
	delete [] positionInFile;
	delete [] lengthInFile;
}

void RoadStore::addRoad(int edgeId, int startNode, int endNode, double length, double speedLimit, int positionInFile, int lengthInFile) {
	if (size == storeSize) {
		int newSize = size * 2;
		int* newEdgeId = new int[newSize];
		int* newStartNode = new int[newSize];
		int* newEndNode = new int[newSize];
		double* newLength = new double[newSize];
		double* newSpeedLimit = new double[newSize];
		int* newPositionInFile = new int[newSize];
		int* newLengthInFile = new int[newSize];

		for (int i = 0; i < size; ++i) {
			newEdgeId[i] = this->roadId[i];
			newStartNode[i] = this->startNode[i];
			newEndNode[i] = this->endNode[i];
			newLength[i] = this->length[i];
			newSpeedLimit[i] = this->speedLimit[i];
			newPositionInFile[i] = this->positionInFile[i];
			newLengthInFile[i] = this->lengthInFile[i];
		}

		delete [] this->roadId;
		delete [] this->startNode;
		delete [] this->endNode;
		delete [] this->length;
		delete [] this->speedLimit;
		delete [] this->positionInFile;
		delete [] this->lengthInFile;

		this->roadId = newEdgeId;
		this->startNode = newStartNode;
		this->endNode = newEndNode;
		this->length = newLength;
		this->speedLimit = newSpeedLimit;
		this->positionInFile = newPositionInFile;
		this->lengthInFile = newLengthInFile;

		storeSize = newSize;
	}

	this->roadId[size] = edgeId;
	this->startNode[size] = startNode;
	this->endNode[size] = endNode;
	this->length[size] = length;
	this->speedLimit[size] = speedLimit;
	this->positionInFile[size] = positionInFile;
	this->lengthInFile[size] = lengthInFile;

	++size;
}

void RoadStore::reassignNodeIds(NodeStore* nodeStore) {
	for (int i = 0; i < this->size; ++i) {

#ifdef _DEBUG_
		cout << "RoadStore: reassignNodeIds: Road(index:" << i << ",id" << this->roadId[i] << ",sNode" << this->startNode[i] << ",eNode:" << this->endNode[i] << ") has new ids: ";
#endif

		int startNodeIndex = nodeStore->getIndex(this->startNode[i]);

#ifdef _DEBUG_
		cout << "sNode(" << startNodeIndex << "),";
#endif

		this->startNode[i] = startNodeIndex;

		int endNodeIndex = nodeStore->getIndex(this->endNode[i]);

#ifdef _DEBUG_
		cout << "eNode(" << endNodeIndex << ")" << endl;
#endif

		this->endNode[i] = endNodeIndex;
#ifdef _DEBUG_
		if (startNodeIndex == -1) {
			cout << "problem...";
		}
		if (endNodeIndex == -1) {
			cout << "problem...";
		}
#endif
	}
}

