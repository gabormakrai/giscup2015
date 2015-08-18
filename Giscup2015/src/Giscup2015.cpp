//============================================================================
// Name        : Giscup2015.cpp
// Author      : Gabor Makrai
// Version     :
// Copyright   : x
// Description : Hello World in C++, Ansi-style
//============================================================================

//#define _DEBUG_

#include "data/RoadParser.h"
#include "data/RoadStore.h"
#include "data/NodeStore.h"
#include "data/NeighbourDataBase.h"

#include "sp/ShortestPathAlgorithm.h"
#include "sp/AStarBinaryHeap.h"

#include <time.h>
#include <sys/time.h>

#include <iostream>
using namespace std;

#define BUFFER_SIZE 16384

int main() {
	struct timeval startDataRead;
	struct timeval endDataRead;
	struct timeval startAlgo;
	struct timeval endAlgo;

	gettimeofday(&startDataRead, NULL);

	// buffer
	unsigned char* buffer = new unsigned char[BUFFER_SIZE];

	// storages
	RoadStore* roadStore = new RoadStore(BUFFER_SIZE);
	NodeStore* nodeStore = new NodeStore(BUFFER_SIZE);

	// road parser
	RoadParser roadParser;

	// loading data from files
	//roadParser.loadNodeFile("/home/makrai/giscup2015/data/sfo_nodes2.txt", buffer, BUFFER_SIZE, nodeStore);
	roadParser.loadNodeFile("/home/makrai/giscup2015/data/example_nodes.txt", buffer, BUFFER_SIZE, nodeStore);
	cout << "#node: " << nodeStore->size << endl;

	//roadParser.loadRoadFile("/home/makrai/giscup2015/data/sfo_roads.txt", buffer, BUFFER_SIZE, roadStore);
	roadParser.loadRoadFile("/home/makrai/giscup2015/data/example_roads.txt", buffer, BUFFER_SIZE, roadStore);
	cout << "#road: " << roadStore->size << endl;

	gettimeofday(&endDataRead, NULL);

	gettimeofday(&startAlgo, NULL);

	// reassign id for nodes
	nodeStore->sort();

	// use new ids in roadStore
	roadStore->reassignNodeIds(nodeStore);

	// create neighbourdatabase
	NeighbourDataBase* neighbourDataBase = new NeighbourDataBase(nodeStore, roadStore);

//	int* inDegree = new int[nodeStore->storeSize];
//	int* outDegree = new int[nodeStore->storeSize];
//	int* inEdge = new int[nodeStore->storeSize];
//	int* outEdge = new int[nodeStore->storeSize];
//
//	for (int i = 0; i < nodeStore->size; ++i) {
//		inDegree[i] = 0;
//		outDegree[i] = 0;
//		inEdge[i] = -1;
//		outEdge[i] = -1;
//	}
//
//	for (int i = 0; i < roadStore->size; ++i) {
//		++outDegree[roadStore->startNode[i]];
//		++inDegree[roadStore->endNode[i]];
//		inEdge[roadStore->endNode[i]] = i;
//		outEdge[roadStore->startNode[i]] = i;
//	}
//
//	for (int i = 0; i < nodeStore->size; ++i) {
//		cout << "id[" << i << "] = " << nodeStore->id[i] << endl;
//		cout << "outDegree[" << i << "] = " << outDegree[i] << endl;
//		cout << "inDegree[" << i << "] = " << inDegree[i] << endl;
//		cout << "inEdge[" << i << "] = " << inEdge[i] << endl;
//		cout << "outEdge[" << i << "] = " << outEdge[i] << endl;
//	}

//	cout << "DistanceTest: " << nodeStore->distance(nodeStore->getIndex(1), nodeStore->getIndex(3)) << endl;
//	cout << "DistanceTest: " << nodeStore->distance(nodeStore->getIndex(3), nodeStore->getIndex(4)) << endl;
//	cout << "DistanceTest: " << nodeStore->distance(nodeStore->getIndex(8), nodeStore->getIndex(9)) << endl;

	AStarBinaryHeap* algo = new AStarBinaryHeap(neighbourDataBase, nodeStore, roadStore);
	algo->shortestPath(1, 10);

	gettimeofday(&endAlgo, NULL);

//	// dispose arrays
//	delete [] inDegree;
//	delete [] outDegree;
//	delete [] inEdge;
//	delete [] outEdge;

	delete algo;

	// dispose roadStore
	delete roadStore;

	// dispose nodeStore
	delete nodeStore;

	// dispose neighbourDB
	delete neighbourDataBase;

	delete [] buffer;

	cout << (endDataRead.tv_sec - startDataRead.tv_sec) * 1000000 + (endDataRead.tv_usec - startDataRead.tv_usec) << endl;
	cout << (endAlgo.tv_sec - startAlgo.tv_sec) * 1000000 + (endAlgo.tv_usec - startAlgo.tv_usec) << endl;

	return 0;
}
