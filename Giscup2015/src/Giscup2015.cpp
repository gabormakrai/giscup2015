//============================================================================
// Name        : Giscup2015.cpp
// Author      : Gabor Makrai
// Version     :
// Copyright   : x
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "RoadParser.h"
#include "RoadStore.h"
#include "NodeStore.h"
#include <time.h>
#include <sys/time.h>

#include <iostream>
using namespace std;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16384
#endif

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
	roadParser.loadNodeFile("/home/makrai/giscup2015/data/sfo_nodes2.txt", buffer, BUFFER_SIZE, nodeStore);
//	cout << "#node: " << nodeStore->size << endl;

	roadParser.loadRoadFile("/home/makrai/giscup2015/data/sfo_roads.txt", buffer, BUFFER_SIZE, roadStore);
//	cout << "#road: " << roadStore->size << endl;

	gettimeofday(&endDataRead, NULL);

	gettimeofday(&startAlgo, NULL);

	// reassign id for nodes
	nodeStore->sort();

	// use new ids in roadStore
	roadStore->reassignNodeIds(nodeStore);

	int* inDegree = new int[nodeStore->storeSize];
	int* outDegree = new int[nodeStore->storeSize];
	int* inEdge = new int[nodeStore->storeSize];
	int* outEdge = new int[nodeStore->storeSize];

	for (int i = 0; i < nodeStore->size; ++i) {
		inDegree[i] = 0;
		outDegree[i] = 0;
	}

	for (int i = 0; i < roadStore->size; ++i) {
		++outDegree[roadStore->startNode[i]];
		++inDegree[roadStore->endNode[i]];
		inEdge[roadStore->endNode[i]] = i;
		outEdge[roadStore->startNode[i]] = i;
	}
	int asd = 0;
	for (int i = 0; i < nodeStore->size; ++i) {
		if (inDegree[i] == 1 && outDegree[i] == 1) {
//			cout << "node: " << i << endl;
			++asd;
		}
	}
//	cout << "asd: " << asd << endl;

	gettimeofday(&endAlgo, NULL);

	// dispose arrays
	delete [] inDegree;
	delete [] outDegree;
	delete [] inEdge;
	delete [] outEdge;

	// dispose roadStore
	roadStore->dispose();
	delete roadStore;

	// dispose nodeStore
	nodeStore->dispose();
	delete nodeStore;

	delete [] buffer;

	cout << (endDataRead.tv_sec - startDataRead.tv_sec) * 1000000 + (endDataRead.tv_usec - startDataRead.tv_usec) << endl;
	cout << (endAlgo.tv_sec - startAlgo.tv_sec) * 1000000 + (endAlgo.tv_usec - startAlgo.tv_usec) << endl;

//	double elapsedDataRead = (double)(endDataRead - startDataRead) * 1000.0 / CLOCKS_PER_SEC;
//	double elapsedAlgo = (double)(endAlgo - startAlgo) * 1000.0 / CLOCKS_PER_SEC;
//	cout << elapsedDataRead << "," << elapsedAlgo << endl;

	return 0;
}
