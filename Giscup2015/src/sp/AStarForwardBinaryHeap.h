/*
 * AStarBinaryHeap.h
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
 */

#ifndef ASTARFORWARDBINARYHEAP_H_
#define ASTARFORWARDBINARYHEAP_H_

//#define _DEBUG_
//#define _HEAPANALYSIS_

#include "ShortestPathAlgorithm.h"
#include "../datastructure/BinaryHeap.h"
#include "../data/NeighbourDataBase.h"

class AStarForwardBinaryHeap : public ShortestPathAlgorithm {
public:
	int* closed;
	BinaryHeap<double>* heap;
	int* previous;
	double* gScore;

	NodeStore* nodeStore;
	NeighbourDataBase* neighbourDataBase;

	AStarForwardBinaryHeap(NeighbourDataBase* neighbourDataBase, NodeStore* nodeStore, RoadStore* roadStore);
	~AStarForwardBinaryHeap();
	int shortestPath(int fromId, int toId);
};


#endif /* ASTARFORWARDBINARYHEAP_H_ */