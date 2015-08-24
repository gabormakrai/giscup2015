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
//#define _HEAPSTATISTICS_

#include "AStarForwardShortestPath.h"
#include "ShortestPathAlgorithm.h"
#include "../datastructure/BinaryHeap.h"
#include "../data/NeighbourDataBase.h"

class AStarForwardBinaryHeap : public ShortestPathAlgorithm {
public:
	int from;
	int to;
	int result;

	int* closed;
	BinaryHeap<double>* heap;
	int* previous;
	int* previousRoad;
	double* gScore;

	NodeStore* nodeStore;
	NeighbourDataBase* neighbourDataBase;

	AStarForwardBinaryHeap(NeighbourDataBase* neighbourDataBase, NodeStore* nodeStore, RoadStore* roadStore, int* heapLookupTable, int* heapNodeArray, double* heapValueArray);
	~AStarForwardBinaryHeap();
	void shortestPath(int fromId, int toId, int mode);
	void reconstructPath(AStarForwardShortestPath* path);
};


#endif /* ASTARFORWARDBINARYHEAP_H_ */
