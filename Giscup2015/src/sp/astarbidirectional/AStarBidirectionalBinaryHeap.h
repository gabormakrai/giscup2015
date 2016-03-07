/*
 * AStarBinaryHeap.h
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
 */

#ifndef ASTARBIDIRECTIONALBINARYHEAP_H_
#define ASTARBIDIRECTIONALBINARYHEAP_H_

//#define _DEBUG_
//#define _HEAPANALYSIS_
//#define _HEAPSTATISTICS_

#include "../ShortestPathAlgorithm.h"
#include "../../datastructure/BinaryHeap.h"
#include "../../data/NeighbourDataBase.h"
#include "AStarBidirectionalShortestPath.h"

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
