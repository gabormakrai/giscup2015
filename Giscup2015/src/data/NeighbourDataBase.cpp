/*
 * NeighbourDataBase.cpp
 *
 *  Created on: 17 Aug 2015
 *      Author: makrai
 */

#include "NeighbourDataBase.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

NeighbourDataBase::NeighbourDataBase(NodeStore* nodeStore, RoadStore* roadStore, int mode) {
	this->count = new int[nodeStore->storeSize];
	this->offset = new int[nodeStore->storeSize];
	this->id = new int[roadStore->storeSize];
	this->distanceWeight = new double[roadStore->storeSize];
	this->timeWeight = new double[roadStore->storeSize];
	this->weight = distanceWeight;
	this->roadId = new int[roadStore->storeSize];

	for (int i = 0; i < nodeStore->size; ++i) {
		this->count[i] = 0;
		this->offset[i] = 0;
	}

	if (mode == NEIGHBOURDATABASE_FORWARD) {

		for (int i = 0; i < roadStore->size; ++i) {
			++this->count[roadStore->startNode[i]];
		}

		for (int i = 1; i < nodeStore->size; ++i) {
			this->offset[i] = this->offset[i-1] + this->count[i-1];
		}

		for (int i = 0; i < nodeStore->size; ++i) {
			this->count[i] = 0;
		}

		for (int i = 0; i < roadStore->size; ++i) {
			int from = roadStore->startNode[i];
			int to = roadStore->endNode[i];
			int id = this->offset[from] + this->count[from];
			++this->count[from];
			this->id[id] = to;
			this->distanceWeight[id] = roadStore->length[i];
			this->timeWeight[id] = roadStore->length[i] / roadStore->speedLimit[i];
			this->roadId[id] = i;
		}

#ifdef _DEBUG_
		for (int i = 0; i < nodeStore->size; ++i) {
			cout << "count["<<i<<"]=" << this->count[i] << ", offset[" << i << "]=" << this->offset[i] << endl;
		}

		for (int i = 0; i < nodeStore->size; ++i) {
			cout << "Node " << i << "(id:" << nodeStore->id[i] << ") has " << this->count[i] << " neighbours..." << endl;
			for (int j = 0; j < this->count[i]; ++j) {
				cout << "\t to " << this->id[this->offset[i] + j] << "(id:" << nodeStore->id[this->id[this->offset[i] + j]] << ") w: " << this->weight[this->offset[i] + j] << endl;
			}
		}
#endif
	} else {
		for (int i = 0; i < roadStore->size; ++i) {
			++this->count[roadStore->endNode[i]];
		}

		for (int i = 1; i < nodeStore->size; ++i) {
			this->offset[i] = this->offset[i-1] + this->count[i-1];
		}

		for (int i = 0; i < nodeStore->size; ++i) {
			this->count[i] = 0;
		}

		for (int i = 0; i < roadStore->size; ++i) {
			int from = roadStore->startNode[i];
			int to = roadStore->endNode[i];
			int id = this->offset[to] + this->count[to];
			++this->count[to];
			this->id[id] = from;
			this->distanceWeight[id] = roadStore->length[i];
			this->timeWeight[id] = roadStore->length[i] / roadStore->speedLimit[i];
			this->roadId[id] = i;
		}

#ifdef _DEBUG_
		for (int i = 0; i < nodeStore->size; ++i) {
			cout << "count["<<i<<"]=" << this->count[i] << ", offset[" << i << "]=" << this->offset[i] << endl;
		}

		for (int i = 0; i < nodeStore->size; ++i) {
			cout << "Node " << i << "(id:" << nodeStore->id[i] << ") has " << this->count[i] << " neighbours..." << endl;
			for (int j = 0; j < this->count[i]; ++j) {
				cout << "\t to " << this->id[this->offset[i] + j] << "(id:" << nodeStore->id[this->id[this->offset[i] + j]] << ") w: " << this->weight[this->offset[i] + j] << endl;
			}
		}
#endif

	}
}

NeighbourDataBase::~NeighbourDataBase() {
	delete [] count;
	delete [] offset;
	delete [] id;
	delete [] distanceWeight;
	delete [] timeWeight;
	delete [] roadId;
}

void NeighbourDataBase::setWeight(int mode) {
	if (mode == 0) { // weight = distance
		weight = distanceWeight;
	} else { // weight = time
		weight = timeWeight;
	}
}
