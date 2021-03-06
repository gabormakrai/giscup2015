/*
 * AStarBidirectionalBinaryHeap.cpp
 *
 *  Created on: 18 Aug 2015
 *  Author: Gabor Makrai
 */

#include "AStarBidirectionalBinaryHeap.h"

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

AStarBidirectionalBinaryHeap::AStarBidirectionalBinaryHeap(NeighbourDataBase* forwardNeighbour, NeighbourDataBase* backwardNeighbour, NodeStore* nodeStore, RoadStore* roadStore, int* heapLookupTable1, int* heapNodeArray1, double* heapValueArray1, int* heapLookupTable2, int* heapNodeArray2, double* heapValueArray2) {
	this->nodeStore = nodeStore;
	this->forwardNeighbour = forwardNeighbour;
	this->backwardNeighbour = backwardNeighbour;
	this->closed = new int[nodeStore->storeSize];
	this->forwardGScore = new double[nodeStore->storeSize];
	this->backwardGScore = new double[nodeStore->storeSize];
	this->next = new int[nodeStore->storeSize];
	this->nextRoad = new int[nodeStore->storeSize];
	this->previous = new int[nodeStore->storeSize];
	this->previousRoad = new int[nodeStore->storeSize];
	this->forwardHeap = new BinaryHeap<double>(nodeStore->storeSize, 0.0, std::numeric_limits<double>::max(), heapLookupTable1, heapNodeArray1, heapValueArray1);
	this->backwardHeap = new BinaryHeap<double>(nodeStore->storeSize, 0.0, std::numeric_limits<double>::max(), heapLookupTable2, heapNodeArray2, heapValueArray2);
}

AStarBidirectionalBinaryHeap::~AStarBidirectionalBinaryHeap() {
	delete [] closed;
	delete [] next;
	delete [] nextRoad;
	delete [] previous;
	delete [] previousRoad;
	delete [] forwardGScore;
	delete [] backwardGScore;
	delete forwardHeap;
	delete backwardHeap;
}

void AStarBidirectionalBinaryHeap::shortestPath(int fromId, int toId, int mode) {
	int from = this->nodeStore->getIndex(fromId);
	int to = this->nodeStore->getIndex(toId);

	this->nodeStore->setDistanceFunction(mode);
	this->forwardNeighbour->setWeight(mode);
	this->backwardNeighbour->setWeight(mode);

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
		cout << "AStarBidirectionalBinaryHeap: shortestPath: fromId:" << fromId << ", from:" << from << ", toId:" << toId << ", to: " << to << endl;
#endif

	for (int i = 0; i < nodeStore->size; ++i) {
		forwardGScore[i] = std::numeric_limits<double>::max();
		backwardGScore[i] = std::numeric_limits<double>::max();
		next[i] = -1;
		previous[i] = -1;
		closed[i] = 0;
	}

	forwardGScore[from] = 0.0;
	forwardHeap->init(from, nodeStore->distance(from, to));
	backwardGScore[to] = 0.0;
	backwardHeap->init(to, nodeStore->distance(from, to));

	int forwardCurrent = -1;
	int backwardCurrent = -1;

#ifdef _HEAPSTATISTICS_
	int forwardSteps = 0;
	int maxForwardHeapSize = 0;
	int avgForwardHeapSize = 0;
	int backwardSteps = 0;
	int maxBackwardHeapSize = 0;
	int avgBackwardHeapSize = 0;
#endif

#ifdef _HEAPANALYSIS_
	int heapIteration = 0;
#endif

	while (forwardHeap->size + backwardHeap->size > 0) {

		// FORWARD STEP
		forwardCurrent = forwardHeap->extractMin();

#ifdef _HEAPSTATISTICS_
	++forwardSteps;
	if (forwardHeap->size > maxForwardHeapSize) {
		maxForwardHeapSize = forwardHeap->size;
	}
	avgForwardHeapSize += forwardHeap->size;
#endif

#ifdef _DEBUG_
			cout << "forwardStep: forwardCurrent: " << forwardCurrent << endl;
#endif

#ifdef _HEAPANALYSIS_
		cout<<"iterationForward:"<<(heapIteration++)<<",forwardHeapSize:"<<forwardHeap->size<<",currentNode:"<<forwardCurrent<<",toNode:"<<to<<endl;
#endif
		if (closed[forwardCurrent] == 1) {
			this->meetingNode = forwardCurrent;

#ifdef _DEBUG_
			cout << "forward step found one which node was found by the backward step" << endl;
#endif
			break;
		}

		closed[forwardCurrent] = 1;

		for (int i = 0; i < this->forwardNeighbour->count[forwardCurrent]; ++i) {
			int neighbourIndex = this->forwardNeighbour->offset[forwardCurrent] + i;
			int neighbour = this->forwardNeighbour->id[neighbourIndex];
			int roadId = this->forwardNeighbour->roadId[neighbourIndex];

			if (closed[neighbour] == 1) {
				continue;
			}

			double gCandidate = forwardGScore[forwardCurrent] + this->forwardNeighbour->weight[neighbourIndex];

			if (forwardHeap->lookupTable[neighbour] == -1 || gCandidate < forwardGScore[neighbour]) {
				previous[neighbour] = forwardCurrent;
				previousRoad[neighbour] = roadId;
				forwardGScore[neighbour] = gCandidate;
				forwardHeap->decreaseKey(neighbour, gCandidate + nodeStore->distance(neighbour, to));
			}
		}

		// BACKWARD STEP
		backwardCurrent = backwardHeap->extractMin();

#ifdef _HEAPSTATISTICS_
	++backwardSteps;
	if (backwardHeap->size > maxBackwardHeapSize) {
		maxBackwardHeapSize = backwardHeap->size;
	}
	avgBackwardHeapSize += backwardHeap->size;
#endif

#ifdef _DEBUG_
			cout << "backwardStep: backwardCurrent: " << backwardCurrent << endl;
#endif

#ifdef _HEAPANALYSIS_
		cout<<"iterationBackward:"<<(heapIteration)<<",backwardHeapSize:"<<backwardHeap->size<<",currentNode:"<<backwardCurrent<<",toNode:"<<to<<endl;
#endif

		if (closed[backwardCurrent] == 1) {

			this->meetingNode = backwardCurrent;

#ifdef _DEBUG_
			cout << "backward step found one which node was found by the forward step" << endl;
#endif
			break;
		}

		closed[backwardCurrent] = 1;

		for (int i = 0; i < this->backwardNeighbour->count[backwardCurrent]; ++i) {
			int neighbourIndex = this->backwardNeighbour->offset[backwardCurrent] + i;
			int neighbour = this->backwardNeighbour->id[neighbourIndex];
			int roadId = this->backwardNeighbour->roadId[neighbourIndex];

			if (closed[neighbour] == 1) {
				continue;
			}

			double gCandidate = backwardGScore[backwardCurrent] + this->backwardNeighbour->weight[neighbourIndex];

			if (backwardHeap->lookupTable[neighbour] == -1 || gCandidate < backwardGScore[neighbour]) {
				next[neighbour] = backwardCurrent;
				nextRoad[neighbour] = roadId;
				backwardGScore[neighbour] = gCandidate;
				backwardHeap->decreaseKey(neighbour, gCandidate + nodeStore->distance(neighbour, from));
			}
		}
	}

	if (closed[forwardCurrent] == 1 || closed[backwardCurrent] == 1) {
		result = SHORTESTPATH_PATH_FOUND;
	} else {
		result = SHORTESTPATH_NO_PATH;
	}

#ifdef _HEAPSTATISTICS_
	cout << "forwardSteps:" << forwardSteps << ", maxForwardHeapSize: " << maxForwardHeapSize << ", avgForwardHeapSize: " << (double)avgForwardHeapSize / (double)forwardSteps << endl;
	cout << "backwardSteps:" << backwardSteps << ", maxBackwardHeapSize: " << maxBackwardHeapSize << ", avgBackwardHeapSize: " << (double)avgBackwardHeapSize / (double)backwardSteps << endl;
#endif

}

void AStarBidirectionalBinaryHeap::reconstructPath(AStarBidirectionalShortestPath* path) {
	// forward: from -> forwardBackwardNode

	int currentNode = meetingNode;

	while (true) {

		path->addForwardRoad(previousRoad[currentNode]);
		currentNode = previous[currentNode];

		if (currentNode == from) {
			break;
		}
	}

	// backward forwardBackwardNode -> to

	currentNode = meetingNode;

	while (true) {

		path->addBackwardRoad(nextRoad[currentNode]);

		currentNode = next[currentNode];

		if (currentNode == to) {
			break;
		}
	}

	path->lastRoadAdded();
}

