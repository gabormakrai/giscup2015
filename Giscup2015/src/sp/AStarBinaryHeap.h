/*
 * AStarBinaryHeap.h
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
 */

#ifndef ASTARBINARYHEAP_H_
#define ASTARBINARYHEAP_H_

//#define _DEBUG_

#include "ShortestPathAlgorithm.h"
#include "../datastructure/BinaryHeap.h"
#include "../data/NeighbourDataBase.h"

class AStarBinaryHeap : public ShortestPathAlgorithm {
public:
	int* closed;
	BinaryHeap<double>* heap;
	int* previous;
	double* gScore;

	NodeStore* nodeStore;
	NeighbourDataBase* neighbourDataBase;

	AStarBinaryHeap(NeighbourDataBase* neighbourDataBase, NodeStore* nodeStore, RoadStore* roadStore);
	~AStarBinaryHeap();
	void shortestPath(int fromId, int toId);
};


#endif /* ASTARBINARYHEAP_H_ */
