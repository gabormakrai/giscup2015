/*
 * SimlifiedRoadStore.cpp
 *
 *  Created on: 24 Aug 2015
 *      Author: makrai
 */

#include "SimplifiedRoadStore.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

SimplifiedRoadStore::SimplifiedRoadStore(NodeStore* nodeStore, RoadStore* roadStore, int mode) {

	if (mode == ROADSIMPLIFICATION_NORMAL) {

		storeSize = roadStore->storeSize;
		startNode = new int[storeSize];
		endNode = new int[storeSize];
		length = new double[storeSize];
		speedLimit = new double[storeSize];

		seekOffset = new int[storeSize];
		seekCount = new int[storeSize];
		seek = new int[storeSize * 2];
		seekLength = new int[storeSize * 2];

		size = 0;

		for (int i = 0; i < roadStore->size; ++i) {
			startNode[size] = roadStore->startNode[i];
			endNode[size] = roadStore->endNode[i];
			length[size] = roadStore->length[i];
			speedLimit[size] = roadStore->speedLimit[i];
			seekOffset[size] = 2 * size;
			seekCount[size] = 2;

			seek[2 * size] = roadStore->positionInFile[i];
			seekLength[2 * size] = roadStore->lengthInFile[i];

			seek[2 * size + 1] = roadStore->positionInFile[i];
			seekLength[2 * size + 1] = roadStore->lengthInFile[i];

			++size;
		}
	}

//	int* inDegree = new int[nodeStore->storeSize];
//	int* outDegree = new int[nodeStore->storeSize];
//	int* inRoad = new int[nodeStore->storeSize];
//	int* outRoad = new int[nodeStore->storeSize];
//
//	for (int i = 0; i < nodeStore->size; ++i) {
//		inDegree[i] = 0;
//		outDegree[i] = 0;
//		inRoad[i] = -1;
//		outRoad[i] = -1;
//	}
//
//	for (int i = 0; i < roadStore->size; ++i) {
//		++inDegree[roadStore->endNode[i]];
//		inRoad[roadStore->endNode[i]] = i;
//		++outDegree[roadStore->startNode[i]];
//		outRoad[roadStore->startNode[i]] = i;
//	}
//
//#ifdef _DEBUG_
////	for (int i = 0; i < nodeStore->size; ++i) {
////		cout << "node(" << nodeStore->id[i] << ") inDegree" << inDegree[i] << ", outDegree: " << outDegree[i] << endl;
////	}
//	for (int i = 0; i < nodeStore->size; ++i) {
//		if (inDegree[i] == 1 && outDegree[i] == 1) {
//			cout << "node(" << nodeStore->id[i] << ") is 1-in-1-out node..." << endl;
//		}
//	}
//#endif



}



SimplifiedRoadStore::~SimplifiedRoadStore() {

}


