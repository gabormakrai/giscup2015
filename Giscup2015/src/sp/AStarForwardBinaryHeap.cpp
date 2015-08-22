/*
 * AStarBinaryHeap.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
 */

#include "AStarForwardBinaryHeap.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

#ifdef _HEAPANALYSIS_
#include <iostream>
using namespace std;
#endif

#ifdef _HEAPSTATISTICS_
#include <iostream>
using namespace std;
#endif

#include <limits>

AStarForwardBinaryHeap::AStarForwardBinaryHeap(NeighbourDataBase* neighbourDataBase, NodeStore* nodeStore, RoadStore* roadStore) {

	this->nodeStore = nodeStore;
	this->neighbourDataBase = neighbourDataBase;

	this->closed = new int[nodeStore->storeSize];
	this->previous = new int[nodeStore->storeSize];
	this->previousRoad = new int[nodeStore->storeSize];
	this->gScore = new double[nodeStore->storeSize];
	this->heap = new BinaryHeap<double>(nodeStore->storeSize, 0.0, std::numeric_limits<double>::max());
}

AStarForwardBinaryHeap::~AStarForwardBinaryHeap() {
	delete [] closed;
	delete [] previous;
	delete [] previousRoad;
	delete [] gScore;
	delete heap;
}

void AStarForwardBinaryHeap::shortestPath(int fromId, int toId, int mode) {
	int from = this->nodeStore->getIndex(fromId);
	int to = this->nodeStore->getIndex(toId);

	this->nodeStore->setDistanceFunction(mode);
	this->neighbourDataBase->setWeight(mode);

	this->from = from;
	this->to = to;
	if (from == -1) {
		this->result = SHORTESTPATH_SOURCE_NOT_FOUND;
		return;
	}
	if (to == -1) {
		this->result = SHORTESTPATH_DESTINATION_NOT_FOUND;
		return;
	}

#ifdef _DEBUG_
		cout << "AStar: shortestPath: fromId:" << fromId << ", from:" << from << ", toId:" << toId << ", to: " << to << endl;
#endif

	for (int i = 0; i < nodeStore->size; ++i) {
		gScore[i] = std::numeric_limits<double>::max();
		previous[i] = -1;
		closed[i] = 0;
	}

	gScore[from] = 0.0;
	heap->init(from, nodeStore->distance(from, to));

	int current = -1;

#ifdef _HEAPSTATISTICS_
	int steps = 0;
	int maxHeapSize = 0;
	int avgHeapSize = 0;
#endif

#ifdef _HEAPANALYSIS_
	int heapIteration = 0;
#endif

	while (heap->size != 0) {

		current = heap->extractMin();

#ifdef _HEAPSTATISTICS_
	++steps;
	if (heap->size > maxHeapSize) {
		maxHeapSize = heap->size;
	}
	avgHeapSize += heap->size;
#endif

#ifdef _HEAPANALYSIS_
		cout<<"iteration:"<<(heapIteration++)<<",heapSize:"<<heap->size<<",currentNode:"<<current<<",toNode:"<<to<<endl;
#endif

#ifdef _DEBUG_
		cout << "AStar: current: " << current << endl;
#endif

		if (current == to) {
			break;
		}

		closed[current] = 1;

		for (int i = 0; i < this->neighbourDataBase->count[current]; ++i) {
			int neighbourIndex = this->neighbourDataBase->offset[current] + i;
			int neighbour = this->neighbourDataBase->id[neighbourIndex];
			int roadId = this->neighbourDataBase->roadId[neighbourIndex];

			if (closed[neighbour] == 1) {
				continue;
			}

			double gCandidate = gScore[current] + this->neighbourDataBase->weight[neighbourIndex];
#ifdef _DEBUG_
			cout << "gCandidate: " << gCandidate << endl;
#endif

			if (heap->lookupTable[neighbour] == -1 || gCandidate < gScore[neighbour]) {
				previous[neighbour] = current;
				previousRoad[neighbour] = roadId;
				gScore[neighbour] = gCandidate;
				heap->decreaseKey(neighbour, gCandidate + nodeStore->distance(neighbour, to));
			}
		}
	}

#ifdef _DEBUG_
		for (int i = 0; i < nodeStore->size; ++i) {
			cout << "gScore[" << i << "]: " << gScore[i] << endl;
		}

		for (int i = 0; i < nodeStore->size; ++i) {
			cout << "closed[" << i << "]: " << closed[i] << endl;
		}

		for (int i = 0; i < nodeStore->size; ++i) {
			cout << "previous[" << i << "]: " << previous[i] << endl;
		}
#endif

		if (current == to) {
			result = SHORTESTPATH_PATH_FOUND;
		} else {
			result = SHORTESTPATH_NO_PATH;
		}

#ifdef _HEAPSTATISTICS_
	cout << "steps:" << steps << ", maxHeapSize: " << maxHeapSize << ", avgHeapSize: " << (double)avgHeapSize / (double)steps << endl;
#endif

}

void AStarForwardBinaryHeap::reconstructPath(AStarForwardShortestPath* path) {

	int currentNode = to;

	while (true) {

		path->addRoad(previousRoad[currentNode]);

		currentNode = previous[currentNode];

		if (currentNode == from) {
			break;
		}
	}
}
