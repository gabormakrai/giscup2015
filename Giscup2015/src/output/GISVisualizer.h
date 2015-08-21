/*
 * GISVisualizer.h
 *
 *  Created on: 20 Aug 2015
 *      Author: makrai
 */

#ifndef GISVISUALIZER_H_
#define GISVISUALIZER_H_

#define NOISE_LEVEL 0.0

#include "../data/NodeStore.h"
#include "../data/RoadStore.h"
#include "../sp/AStarForwardBinaryHeap.h"
#include "../sp/AStarBackwardBinaryHeap.h"
#include "../sp/AStarBidirectionalBinaryHeap.h"

class GISVisualizer {
public:
	void writeGISFiles(const char* nodeFile, const char* roadFile, NodeStore* nodeStore, RoadStore* roadStore);
	void writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarForwardBinaryHeap* algo);
	void writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarBackwardBinaryHeap* algo);
	void writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarBidirectionalBinaryHeap* algo);
};


#endif /* GISVISUALIZER_H_ */
