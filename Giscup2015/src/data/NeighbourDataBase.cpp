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

NeighbourDataBase::NeighbourDataBase(NodeStore* nodeStore, RoadStore* roadStore) {

	this->count = new int[nodeStore->storeSize];
	this->offset = new int[nodeStore->storeSize];
	this->id = new int[roadStore->storeSize];
	this->weight = new double[roadStore->storeSize];

	for (int i = 0; i < nodeStore->size; ++i) {
		this->count[i] = 0;
		this->offset[i] = 0;
	}

	for (int i = 0; i < roadStore->size; ++i) {
		++this->count[roadStore->startNode[i]];
	}

	for (int i = 1; i < roadStore->size; ++i) {
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
		this->weight[id] = roadStore->length[i];
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

void NeighbourDataBase::dispose() {
	delete [] count;
	delete [] offset;
	delete [] id;
	delete [] weight;
}
