/*
 * AStarForwardBinaryHeap.h
 *
 *  Created on: 18 Aug 2015
 *  Author: Gabor Makrai
 */

#ifndef ASTARFORWARDBINARYHEAP_H_
#define ASTARFORWARDBINARYHEAP_H_

// _DEBUG_ for debugging the sp algorithm
//#define _DEBUG_
// _HEAPANALYSIS_ for watching what the algorithm does
//#define _HEAPANALYSIS_
// _HEAPSTATISTICS_ for collecting statistics during a shortest path search
//#define _HEAPSTATISTICS_

#include "AStarForwardShortestPath.h"
#include "../ShortestPathAlgorithm.h"
#include "../../datastructure/Heap.h"
#include "../../data/NeighbourDataBase.h"

/**
 *
 * Class implements the traditional A* shortest path algorithm
 *
 */
class AStarForwardBinaryHeap : public ShortestPathAlgorithm {
public:
	int from;
	int to;
	int result;

	int* closed;

	Heap<double>* heap;

	int* previous;
	int* previousRoad;
	double* gScore;

	NodeStore* nodeStore;
	NeighbourDataBase* neighbourDataBase;

	AStarForwardBinaryHeap(NeighbourDataBase* neighbourDataBase, NodeStore* nodeStore, RoadStore* roadStore, Heap<double>* heap);
	~AStarForwardBinaryHeap();
	void shortestPath(int fromId, int toId, int mode);
	void reconstructPath(AStarForwardShortestPath* path);
};


#endif /* ASTARFORWARDBINARYHEAP_H_ */
