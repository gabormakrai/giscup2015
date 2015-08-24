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
#include "../data/SimplifiedRoadStore.h"
#include "../data/PolygonStore.h"
#include "../sp/AStarForwardBinaryHeap.h"
#include "../sp/AStarBackwardBinaryHeap.h"
#include "../sp/AStarBidirectionalBinaryHeap.h"

class GISVisualizer {
public:
	void writeGISFiles(const char* nodeFile, const char* roadFile, const char* polygonNodeFile, const char* polygonFile, NodeStore* nodeStore, RoadStore* roadStore, PolygonStore* polygonStore, int* bannedNodes);
	void writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarForwardBinaryHeap* algo);
	void writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarBackwardBinaryHeap* algo);
	void writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarBidirectionalBinaryHeap* algo);
	void writeSimplifiedRoads(const char* fileName, NodeStore* nodeStore, SimplifiedRoadStore* simplifiedRoadStore);
};


#endif /* GISVISUALIZER_H_ */
