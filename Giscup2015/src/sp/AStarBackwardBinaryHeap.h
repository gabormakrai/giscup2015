/*
 * AStarBinaryHeap.h
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
 */

#ifndef ASTARBACKWARDBINARYHEAP_H_
#define ASTARBACKWARDBINARYHEAP_H_

//#define _DEBUG_
//#define _HEAPANALYSIS_
//#define _HEAPSTATISTICS_

#include "ShortestPathAlgorithm.h"
#include "../datastructure/BinaryHeap.h"
#include "../data/NeighbourDataBase.h"

class AStarBackwardBinaryHeap : public ShortestPathAlgorithm {
public:
	int from;
	int to;
	int result;

	int* closed;
	BinaryHeap<double>* heap;
	int* next;
	double* gScore;

	NodeStore* nodeStore;
	NeighbourDataBase* neighbourDataBase;

	AStarBackwardBinaryHeap(NeighbourDataBase* neighbourDataBase, NodeStore* nodeStore, RoadStore* roadStore, int* heapLookupTable, int* heapNodeArray, double* heapValueArray);
	~AStarBackwardBinaryHeap();
	void shortestPath(int fromId, int toId);
};


#endif /* ASTARBACKWARDBINARYHEAP_H_ */
