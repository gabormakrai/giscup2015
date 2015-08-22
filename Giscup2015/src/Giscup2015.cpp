//============================================================================
// Name        : Giscup2015.cpp
// Author      : Gabor Makrai
// Version     :
// Copyright   : x
// Description : Hello World in C++, Ansi-style
//============================================================================

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
#include <sys/stat.h>

#include <iostream>
using namespace std;

//#define ALGO1
//#define ALGO2
#define ALGO3

#define BUFFER_SIZE 16384

void showElapsedTime(struct timeval start, struct timeval end) {
	cout << (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec) << endl;
}

inline bool fileExists(const char* file) {
    struct stat buf;
    return (stat(file, &buf) == 0);
}

int main(int argc, char *argv[]) {

	struct timeval startDataRead;
	struct timeval endDataRead;
	struct timeval startPre;
	struct timeval endPre;
	struct timeval startSearch;
	struct timeval endSearch;
	struct timeval startDataWrite;
	struct timeval endDataWrite;

	gettimeofday(&startDataRead, NULL);

	const char* inputRoadFile;
	const char* inputNodeFile;
	const char* inputPolygonFile;
	const char* sourceNode;
	const char* destinationNode;
	const char* outputShortestPathFile;
	const char* outputStatFile;

	if (argc == 1) { // TEST MODE
		inputNodeFile = "/home/makrai/giscup2015/data/sfo_nodes.txt";
		inputRoadFile = "/home/makrai/giscup2015/data/sfo_roads.txt";
		inputPolygonFile = "/home/makrai/giscup2015/data/sfo_roads.txt";
		sourceNode = "50096828";
		destinationNode = "48432214";
//		inputNodeFile = "/home/makrai/giscup2015/data/example_nodes.txt";
//		inputRoadFile = "/home/makrai/giscup2015/data/example_roads.txt";
//		inputPolygonFile = "/home/makrai/giscup2015/data/example_roads.txt";
//		sourceNode = "1";
//		destinationNode = "10";
		outputShortestPathFile = "/media/sf_ubuntu_shared_folder/output_SP.txt";
		outputStatFile = "/media/sf_ubuntu_shared_folder/output_Stat.txt";
	} else if (argc == 8) { // NORMAL MODE
		inputRoadFile = argv[1];
		inputNodeFile = argv[2];
		inputPolygonFile = argv[3];
		sourceNode = argv[4];
		destinationNode = argv[5];
		outputShortestPathFile = argv[6];
		outputStatFile = argv[7];
	} else {
		cout << "Not enough parameter..." << endl;
		// TODO: here...
		cout << "usage: " << endl;
		return 0;
	}

	// check input files
	if (!fileExists(inputRoadFile)) {
		cout << "Problem: input road file (" << inputRoadFile << ") does not exist..." << endl;
		return 0;
	}
	if (!fileExists(inputNodeFile)) {
		cout << "Problem: input road file (" << inputNodeFile << ") does not exist..." << endl;
		return 0;
	}
	if (!fileExists(inputPolygonFile)) {
		cout << "Problem: input road file (" << inputPolygonFile << ") does not exist..." << endl;
		return 0;
	}

	// buffer
	unsigned char* buffer = new unsigned char[BUFFER_SIZE];

	// storages
	RoadStore* roadStore = new RoadStore(BUFFER_SIZE);
	NodeStore* nodeStore = new NodeStore(BUFFER_SIZE);

	// road parser
	RoadParser roadParser;

	// loading data from files
	roadParser.loadNodeFile(inputNodeFile, buffer, BUFFER_SIZE, nodeStore);

	roadParser.loadRoadFile(inputRoadFile, buffer, BUFFER_SIZE, roadStore);

//	// print out general statistics
//	cout << "#node: " << nodeStore->size << endl;
//	cout << "#road: " << roadStore->size << endl;

	gettimeofday(&endDataRead, NULL);
	gettimeofday(&startPre, NULL);

	// reassign id for nodes
	nodeStore->sort();

	// use new ids in roadStore
	roadStore->reassignNodeIds(nodeStore);

	// create neighbourdatabase
#if defined(ALGO1) || defined(ALGO3)
	NeighbourDataBase* forwardNeighbour = new NeighbourDataBase(nodeStore, roadStore, NEIGHBOURDATABASE_FORWARD);
#endif
#if defined(ALGO2) || defined(ALGO3)
	NeighbourDataBase* backwardNeighbour = new NeighbourDataBase(nodeStore, roadStore, NEIGHBOURDATABASE_BACKWARD);
#endif

	gettimeofday(&endPre, NULL);
	gettimeofday(&startSearch, NULL);

#ifdef ALGO1
	AStarForwardBinaryHeap* algo1 = new AStarForwardBinaryHeap(forwardNeighbour, nodeStore, roadStore);
	//algo->shortestPath(1, 10);
	algo1->shortestPath(50096828,48432214);
	//cout << "sp(50096828,48432214):" << algo1->result << endl;
#endif

#ifdef ALGO2
	AStarBackwardBinaryHeap* algo2 = new AStarBackwardBinaryHeap(backwardNeighbour, nodeStore, roadStore);
	//cout << "sp(1,10):" << algo->shortestPath(1,10) << endl;
	algo2->shortestPath(50096828,48432214);
	//cout << "sp(50096828,48432214):" << algo2->result << endl;
#endif

#ifdef ALGO3
	AStarBidirectionalBinaryHeap* algo3 = new AStarBidirectionalBinaryHeap(forwardNeighbour, backwardNeighbour, nodeStore, roadStore);
	// cout << "sp(1,10):" << algo->shortestPath(1,10) << endl;
	algo3->shortestPath(50096828,48432214);
	//cout << "sp(50096828,48432214):" << algo3->result << endl;
#endif

	gettimeofday(&endSearch, NULL);
	gettimeofday(&startDataWrite, NULL);

//	GISVisualizer gisVisualizer;
//	gisVisualizer.writeGISFiles("/media/sf_ubuntu_shared_folder/nodes.csv", "/media/sf_ubuntu_shared_folder/roads.csv", nodeStore, roadStore);
//	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo1_heapNodes.csv", "/media/sf_ubuntu_shared_folder/algo1_closedNodes.csv", "/media/sf_ubuntu_shared_folder/algo1_shortestPath.csv", algo1);
//	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo2_heapNodes.csv", "/media/sf_ubuntu_shared_folder/algo2_closedNodes.csv", "/media/sf_ubuntu_shared_folder/algo2_shortestPath.csv", algo2);
//	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo3_heapNodes.csv", "/media/sf_ubuntu_shared_folder/algo3_closedNodes.csv", "/media/sf_ubuntu_shared_folder/algo3_shortestPath.csv", algo3);

#ifdef ALGO1
	delete algo1;
#endif

#ifdef ALGO2
	delete algo2;
#endif

#ifdef ALGO3
	delete algo3;
#endif

	// dispose roadStore
	delete roadStore;

	// dispose nodeStore
	delete nodeStore;

	// dispose neighbourDB
#if defined(ALGO1) || defined(ALGO3)
	delete forwardNeighbour;
#endif

#if defined(ALGO2) || defined(ALGO3)
	delete backwardNeighbour;
#endif

	delete [] buffer;

	gettimeofday(&endDataWrite, NULL);

//	cout << "DataRead:";
	showElapsedTime(startDataRead, endDataRead);
//	cout << "Pre:";
	showElapsedTime(startPre, endPre);
//	cout << "Search:";
	showElapsedTime(startSearch, endSearch);
//	cout << "DataWrite:";
	showElapsedTime(startDataWrite, endDataWrite);

	return 0;
}

