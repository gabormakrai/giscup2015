/*
 * AStarBidirectionalBinaryHeap.h
 *
 *  Created on: 18 Aug 2015
 *  Author: Gabor Makrai
 */

#ifndef ASTARBIDIRECTIONALBINARYHEAP_H_
#define ASTARBIDIRECTIONALBINARYHEAP_H_

// _DEBUG_ for debugging the sp algorithm
//#define _DEBUG_
// _HEAPANALYSIS_ for watching what the algorithm does
//#define _HEAPANALYSIS_
// _HEAPSTATISTICS_ for collecting statistics during a shortest path search
//#define _HEAPSTATISTICS_

#include "../ShortestPathAlgorithm.h"
#include "../../datastructure/BinaryHeap.h"
#include "../../data/NeighbourDataBase.h"
#include "AStarBidirectionalShortestPath.h"

/**
 *
 * Class implements the bidirectional A* shortest path algorithm
 *
 */
class AStarBidirectionalBinaryHeap : public ShortestPathAlgorithm {
public:
	int from;
	int to;
	int result;
	int meetingNode;

	int* closed;
	BinaryHeap<double>* forwardHeap;
	BinaryHeap<double>* backwardHeap;

	int* next;
	int* nextRoad;
	int* previous;
	int* previousRoad;

	double* forwardGScore;
	double* backwardGScore;

	NodeStore* nodeStore;
	NeighbourDataBase* forwardNeighbour;
	NeighbourDataBase* backwardNeighbour;

	AStarBidirectionalBinaryHeap(NeighbourDataBase* forwardNeighbour, NeighbourDataBase* backwardNeighbour, NodeStore* nodeStore, RoadStore* roadStore, int* heapLookupTable1, int* heapNodeArray1, double* heapValueArray1, int* heapLookupTable2, int* heapNodeArray2, double* heapValueArray2);
	~AStarBidirectionalBinaryHeap();
	void shortestPath(int fromId, int toId, int mode);
	void reconstructPath(AStarBidirectionalShortestPath* path);

};


#endif /* ASTARBIDIRECTIONALBINARYHEAP_H_ */
