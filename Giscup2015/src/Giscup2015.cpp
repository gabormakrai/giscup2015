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
#include "sp/AStarForwardBinaryHeap.h"
#include "sp/AStarBackwardBinaryHeap.h"
#include "sp/AStarBidirectionalBinaryHeap.h"

#include "output/GISVisualizer.h"

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
	roadParser.loadNodeFile("/home/makrai/giscup2015/data/sfo_nodes2.txt", buffer, BUFFER_SIZE, nodeStore);
	//roadParser.loadNodeFile("/home/makrai/giscup2015/data/example_nodes.txt", buffer, BUFFER_SIZE, nodeStore);

	roadParser.loadRoadFile("/home/makrai/giscup2015/data/sfo_roads.txt", buffer, BUFFER_SIZE, roadStore);
	//roadParser.loadRoadFile("/home/makrai/giscup2015/data/example_roads.txt", buffer, BUFFER_SIZE, roadStore);

	// print out general statistics
	cout << "#node: " << nodeStore->size << endl;
	cout << "#road: " << roadStore->size << endl;

	gettimeofday(&endDataRead, NULL);

	gettimeofday(&startAlgo, NULL);

	// reassign id for nodes
	nodeStore->sort();

	// use new ids in roadStore
	roadStore->reassignNodeIds(nodeStore);

	// create neighbourdatabase
	NeighbourDataBase* forwardNeighbour = new NeighbourDataBase(nodeStore, roadStore, NEIGHBOURDATABASE_FORWARD);
	NeighbourDataBase* backwardNeighbour = new NeighbourDataBase(nodeStore, roadStore, NEIGHBOURDATABASE_BACKWARD);

	AStarForwardBinaryHeap* algo1 = new AStarForwardBinaryHeap(forwardNeighbour, nodeStore, roadStore);
	//algo->shortestPath(1, 10);
	algo1->shortestPath(50096828,48432214);
	cout << "sp(50096828,48432214):" << algo1->result << endl;

	AStarBackwardBinaryHeap* algo2 = new AStarBackwardBinaryHeap(backwardNeighbour, nodeStore, roadStore);
	//cout << "sp(1,10):" << algo->shortestPath(1,10) << endl;
	algo2->shortestPath(50096828,48432214);
	cout << "sp(50096828,48432214):" << algo2->result << endl;

	AStarBidirectionalBinaryHeap* algo3 = new AStarBidirectionalBinaryHeap(forwardNeighbour, backwardNeighbour, nodeStore, roadStore);
	// cout << "sp(1,10):" << algo->shortestPath(1,10) << endl;
	algo3->shortestPath(50096828,48432214);
	cout << "sp(50096828,48432214):" << algo3->result << endl;

	gettimeofday(&endAlgo, NULL);

	GISVisualizer gisVisualizer;
//	gisVisualizer.writeGISFiles("/media/sf_ubuntu_shared_folder/nodes.csv", "/media/sf_ubuntu_shared_folder/roads.csv", nodeStore, roadStore);
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo1_heapNodes.csv", "/media/sf_ubuntu_shared_folder/algo1_closedNodes.csv", "/media/sf_ubuntu_shared_folder/algo1_shortestPath.csv", algo1);
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo2_heapNodes.csv", "/media/sf_ubuntu_shared_folder/algo2_closedNodes.csv", "/media/sf_ubuntu_shared_folder/algo2_shortestPath.csv", algo2);
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo3_heapNodes.csv", "/media/sf_ubuntu_shared_folder/algo3_closedNodes.csv", "/media/sf_ubuntu_shared_folder/algo3_shortestPath.csv", algo3);

	delete algo1;
	delete algo2;
	delete algo3;

	// dispose roadStore
	delete roadStore;

	// dispose nodeStore
	delete nodeStore;

	// dispose neighbourDB
	delete forwardNeighbour;
	delete backwardNeighbour;

	delete [] buffer;

	cout << (endDataRead.tv_sec - startDataRead.tv_sec) * 1000000 + (endDataRead.tv_usec - startDataRead.tv_usec) << endl;
	cout << (endAlgo.tv_sec - startAlgo.tv_sec) * 1000000 + (endAlgo.tv_usec - startAlgo.tv_usec) << endl;

	return 0;
}

// dead code

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

//	// dispose arrays
//	delete [] inDegree;
//	delete [] outDegree;
//	delete [] inEdge;
//	delete [] outEdge;
