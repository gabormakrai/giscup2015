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
#include "../sp/AStarBinaryHeap.h"

class GISVisualizer {
public:
	void writeGISFiles(const char* nodeFile, const char* roadFile, NodeStore* nodeStore, RoadStore* roadStore);
	void writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarBinaryHeap* algo, int from, int to);
};


#endif /* GISVISUALIZER_H_ */
