/*
 * AStarBinaryHeap.h
 *
 *  Created on: 18 Aug 2015
 *  Author: Gabor Makrai
 */

#ifndef ASTARBACKWARDBINARYHEAP_H_
#define ASTARBACKWARDBINARYHEAP_H_

// _DEBUG_ for debugging the sp algorithm
//#define _DEBUG_
// _HEAPANALYSIS_ for watching what the algorithm does
//#define _HEAPANALYSIS_
// _HEAPSTATISTICS_ for collecting statistics during a shortest path search
//#define _HEAPSTATISTICS_

#include "../ShortestPathAlgorithm.h"
#include "../../datastructure/BinaryHeap.h"
#include "../../data/NeighbourDataBase.h"
#include "AStarBackwardShortestPath.h"

/**
 *
 * Class contains the code for backward A* Shortest Path algorithm
 *
 */
class AStarBackwardBinaryHeap : public ShortestPathAlgorithm {
public:
	int from;
	int to;
	int result;

	int* closed;
	BinaryHeap<double>* heap;
	int* next;
	int* nextRoad;
	double* gScore;

	NodeStore* nodeStore;
	NeighbourDataBase* neighbourDataBase;

	AStarBackwardBinaryHeap(NeighbourDataBase* neighbourDataBase, NodeStore* nodeStore, RoadStore* roadStore, int* heapLookupTable, int* heapNodeArray, double* heapValueArray);
	~AStarBackwardBinaryHeap();
	void shortestPath(int fromId, int toId, int mode);
	void reconstructPath(AStarBackwardShortestPath* path);
};


#endif /* ASTARBACKWARDBINARYHEAP_H_ */
