/*
 * AStarBinaryHeap.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
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

AStarBidirectionalBinaryHeap::AStarBidirectionalBinaryHeap(NeighbourDataBase* forwardNeighbour, NeighbourDataBase* backwardNeighbour, NodeStore* nodeStore, RoadStore* roadStore) {
	this->nodeStore = nodeStore;
	this->forwardNeighbour = forwardNeighbour;
	this->backwardNeighbour = backwardNeighbour;
	this->closed = new int[nodeStore->storeSize];
	this->forwardGScore = new double[nodeStore->storeSize];
	this->backwardGScore = new double[nodeStore->storeSize];
	this->next = new int[nodeStore->storeSize];
	this->previous = new int[nodeStore->storeSize];
	this->forwardHeap = 0; //new BinaryHeap<double>(nodeStore->storeSize, 0.0, std::numeric_limits<double>::max());
	this->backwardHeap = 0; //new BinaryHeap<double>(nodeStore->storeSize, 0.0, std::numeric_limits<double>::max());
}

AStarBidirectionalBinaryHeap::~AStarBidirectionalBinaryHeap() {
	delete [] closed;
	delete [] next;
	delete [] previous;
	delete [] forwardGScore;
	delete [] backwardGScore;
	delete forwardHeap;
	delete backwardHeap;
}

void AStarBidirectionalBinaryHeap::shortestPath(int fromId, int toId) {
	int from = this->nodeStore->getIndex(fromId);
	int to = this->nodeStore->getIndex(toId);

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

			if (closed[neighbour] == 1) {
				continue;
			}

			double gCandidate = forwardGScore[forwardCurrent] + this->forwardNeighbour->weight[neighbourIndex];

			if (forwardHeap->lookupTable[neighbour] == -1 || gCandidate < forwardGScore[neighbour]) {
				previous[neighbour] = forwardCurrent;
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

			if (closed[neighbour] == 1) {
				continue;
			}

			double gCandidate = backwardGScore[backwardCurrent] + this->backwardNeighbour->weight[neighbourIndex];

			if (backwardHeap->lookupTable[neighbour] == -1 || gCandidate < backwardGScore[neighbour]) {
				next[neighbour] = backwardCurrent;
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
