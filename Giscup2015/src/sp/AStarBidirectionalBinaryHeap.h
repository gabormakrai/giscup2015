/*
 * AStarBinaryHeap.h
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
 */

#ifndef ASTARBIDIRECTIONALBINARYHEAP_H_
#define ASTARBIDIRECTIONALBINARYHEAP_H_

#define _DEBUG_
//#define _HEAPANALYSIS_

#include "ShortestPathAlgorithm.h"
#include "../datastructure/BinaryHeap.h"
#include "../data/NeighbourDataBase.h"

class AStarBidirectionalBinaryHeap : public ShortestPathAlgorithm {
public:
	int from;
	int to;
	int result;

	int* closed;
	BinaryHeap<double>* forwardHeap;
	BinaryHeap<double>* backwardHeap;
	int* next;
	int* previous;
	double* forwardGScore;
	double* backwardGScore;

	NodeStore* nodeStore;
	NeighbourDataBase* forwardNeighbour;
	NeighbourDataBase* backwardNeighbour;

	AStarBidirectionalBinaryHeap(NeighbourDataBase* forwardNeighbour, NeighbourDataBase* backwardNeighbour, NodeStore* nodeStore, RoadStore* roadStore);
	~AStarBidirectionalBinaryHeap();
	void shortestPath(int fromId, int toId);
};


#endif /* ASTARBIDIRECTIONALBINARYHEAP_H_ */
