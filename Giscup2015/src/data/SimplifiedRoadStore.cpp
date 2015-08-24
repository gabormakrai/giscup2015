/*
 * SimlifiedRoadStore.cpp
 *
 *  Created on: 24 Aug 2015
 *      Author: makrai
 */

#include "SimplifiedRoadStore.h"

#ifdef _SDEBUG_
#include <iostream>
using namespace std;
#endif

SimplifiedRoadStore::SimplifiedRoadStore(NodeStore* nodeStore, RoadStore* roadStore, int source, int destination, int mode) {

	if (mode == ROADSIMPLIFICATION_NORMAL) {

		storeSize = roadStore->storeSize;
		startNode = new int[storeSize];
		endNode = new int[storeSize];
		length = new double[storeSize];
		time = new double[storeSize];

		seekOffset = new int[storeSize];
		seekCount = new int[storeSize];
//		seek = new int[storeSize * 2];
//		seekLength = new int[storeSize * 2];
		seek = new int[storeSize];
		seekLength = new int[storeSize];

		size = 0;

		for (int i = 0; i < roadStore->size; ++i) {
			startNode[size] = roadStore->startNode[i];
			endNode[size] = roadStore->endNode[i];
			length[size] = roadStore->length[i];
			time[size] = roadStore->time[i];

			seekOffset[size] = size;
			seekCount[size] = 1;
			seek[size] = roadStore->positionInFile[i];
			seekLength[size] = roadStore->lengthInFile[i];

//			seekOffset[size] = 2 * size;
//			seekCount[size] = 2;
//			seek[2 * size] = roadStore->positionInFile[i];
//			seekLength[2 * size] = roadStore->lengthInFile[i];
//			seek[2 * size + 1] = roadStore->positionInFile[i];
//			seekLength[2 * size + 1] = roadStore->lengthInFile[i];

			++size;
		}
	} else {
		storeSize = roadStore->storeSize;
		startNode = new int[storeSize];
		endNode = new int[storeSize];
		length = new double[storeSize];
		time = new double[storeSize];

		seekOffset = new int[storeSize];
		seekCount = new int[storeSize];
		seek = new int[storeSize];
		seekLength = new int[storeSize];

		size = 0;

		int* inDegree = new int[nodeStore->storeSize];
		int* outDegree = new int[nodeStore->storeSize];
		int* inRoad = new int[nodeStore->storeSize];
		int* outRoad = new int[nodeStore->storeSize];

		for (int i = 0; i < nodeStore->size; ++i) {
			inDegree[i] = 0;
			outDegree[i] = 0;
			inRoad[i] = -1;
			outRoad[i] = -1;
		}

		for (int i = 0; i < roadStore->size; ++i) {
			++inDegree[roadStore->endNode[i]];
			inRoad[roadStore->endNode[i]] = i;
			++outDegree[roadStore->startNode[i]];
			outRoad[roadStore->startNode[i]] = i;
		}

		// source and destination cannot be part of a simplifaction chain

		inDegree[source] = 0;
		outDegree[source] = 0;
		inDegree[destination] = 0;
		outDegree[destination] = 0;

		int* simplifiedRoad = new int[roadStore->storeSize];
		for (int i = 0; i < roadStore->size; ++i) {
			simplifiedRoad[i] = 0;
		}

#ifdef _SDEBUG_
		//	for (int i = 0; i < nodeStore->size; ++i) {
		//		cout << "node(" << nodeStore->id[i] << ") inDegree" << inDegree[i] << ", outDegree: " << outDegree[i] << endl;
		//	}
		for (int i = 0; i < nodeStore->size; ++i) {
			if (inDegree[i] == 1 && outDegree[i] == 1) {
				cout << "node(" << nodeStore->id[i] << ") is 1-in-1-out node..." << endl;
			}
		}
#endif

		int seekIndex = size;

		int* backwardChain = new int[roadStore->storeSize];

		for (int i = 0; i < nodeStore->size; ++i) {
			if (inDegree[i] == 1 && outDegree[i] == 1) {

				double length = 0.0;
				double time = 0.0;

				int roadCount = 0;
				int offset = seekIndex;

				int backwardIndex = 0;

				// simplification chain start at node i
				// backward search to find out the start node of the chain

				int current = i;
				int previous = -1;
				while (true) {
					previous = roadStore->startNode[inRoad[current]];
					backwardChain[backwardIndex] = inRoad[current];
					++backwardIndex;
					if (inDegree[previous] == 1 && outDegree[previous] == 1) {
						// found an other 1-in-1-out node
						inDegree[previous] = -1;
						current = previous;
					} else {
						break;
					}
				}

				--backwardIndex;
				for (;backwardIndex >= 0; --backwardIndex) {

					int road = backwardChain[backwardIndex];
					simplifiedRoad[road] = 1;

					length += roadStore->length[road];
					time += roadStore->time[road];
					seek[seekIndex] = roadStore->positionInFile[road];
					seekLength[seekIndex] = roadStore->lengthInFile[road];
					++seekIndex;
					++roadCount;
#ifdef _SDEBUG_
					cout << "backwardEdge: " << roadStore->roadId[road] << ", from: " << nodeStore->id[roadStore->startNode[road]] << ", to: " << nodeStore->id[roadStore->endNode[road]] << endl;
#endif
				}

				int startNode = previous;

				// simplification chain start at node i
				// forward search to find out the end node of the chain

				current = i;

				int next = -1;
				while (true) {
					next = roadStore->endNode[outRoad[current]];
					int road = outRoad[current];
					simplifiedRoad[road] = 1;

					length += roadStore->length[road];
					time += roadStore->time[road];
					seek[seekIndex] = roadStore->positionInFile[road];
					seekLength[seekIndex] = roadStore->lengthInFile[road];
					++seekIndex;
					++roadCount;
#ifdef _SDEBUG_
					cout << "forwardEdge: " << roadStore->roadId[road] << ", from: " << nodeStore->id[roadStore->startNode[road]] << ", to: " << nodeStore->id[roadStore->endNode[road]] << endl;
#endif
					if (inDegree[next] == 1 && outDegree[next] == 1) {
						inDegree[next] = -1;
						// found an other 1-in-1-out node
						current = next;
					} else {
						break;
					}
				}

				int endNode = next;

#ifdef _SDEBUG_
				cout << "chain found: chainSearchFromNode: " << nodeStore->id[i] << ", startNode: " << nodeStore->id[startNode] << ", endNode: " << nodeStore->id[endNode] << endl;
#endif

				this->startNode[size] = startNode;
				this->endNode[size] = endNode;
				this->length[size] = length;
				this->time[size] = time;
				seekOffset[size] = offset;
				seekCount[size] = roadCount;

#ifdef _SDEBUG_
				if (roadCount == 1) {
					cout << "-----------------------????" << endl;
				}
#endif

#ifdef _SDEBUG_
				cout << "new Road: length:" << length << ", time: " << time << endl;
#endif

				++size;
			}
		}

		// add roads where neither the startNode nor the endNode is not 1-on-1-out node
		for (int i = 0; i < roadStore->size; ++i) {
			if (simplifiedRoad[i] == 0)  {
				startNode[size] = roadStore->startNode[i];
				endNode[size] = roadStore->endNode[i];
				length[size] = roadStore->length[i];
				time[size] = roadStore->time[i];
				seekOffset[size] = size;
				seekCount[size] = 1;
				seek[size] = roadStore->positionInFile[i];
				seekLength[size] = roadStore->lengthInFile[i];

#ifdef _SDEBUG_
				cout << "road (" << roadStore->roadId[i] << ") has non sNode & eNode as 1-in-1-out node..." << endl;
#endif

				++size;
			}
		}

#ifdef _SDEBUG_
		int overallRoads = 0;
		for (int i = 0; i < size; ++i) {
			overallRoads += this->seekCount[i];
		}
		cout << "overall Simplified road: " << overallRoads << endl;
		int skipped = 0;
		for (int i = 0; i < roadStore->size; ++i) {
			if (simplifiedRoad[i] == 0)  {
				cout << "SkippedRoad: road" << roadStore->roadId[i] << endl;
				++skipped;
			}
		}
		cout << "#skipped: " << skipped << endl;
#endif

	}



}



SimplifiedRoadStore::~SimplifiedRoadStore() {

}


