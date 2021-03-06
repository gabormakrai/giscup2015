//============================================================================
// Name        : Giscup2015.cpp
// Author      : Gabor Makrai
// Version     :
// Copyright   :
// Description : GISCUP2015 main file
//============================================================================

#include "data/RoadParser.h"
#include "data/RoadStore.h"
#include "data/NodeStore.h"
#include "data/NeighbourDataBase.h"
#include "data/PolygonStore.h"
#include "data/PolygonParser.h"
#include "data/SimplifiedRoadStore.h"

#include "sp/ShortestPathAlgorithm.h"
#include "sp/astarforward/AStarForwardBinaryHeap.h"
#include "sp/astarbackward/AStarBackwardBinaryHeap.h"
#include "sp/astarbidirectional/AStarBidirectionalBinaryHeap.h"

#include <limits>
#include "datastructure/Heap.h"
#include "datastructure/BinaryHeap.h"
#include "datastructure/BinaryHeap4ary.h"

#include "output/ShortestPathWriter.h"
#include "output/GISVisualizer.h"
#include "output/StatFileWriter.h"

#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>

#include <iostream>
using namespace std;

// three different A* algorithm implementation: forward, backward and bi-directional, v2 bi-directional
#define ALGO1
//#define ALGO2
//#define ALGO3

// two binary heap implementations (2-ary/standard, 4-ary)
#define BINARYHEAP
//#define BINARYHEAP4ARY

// controls the output for the application
//#define _DEBUG_
//#define _GISVISUALIZER_
//#define _CONSOLE_

#define BUFFER_SIZE 16384

// function for showing the elapsed time
void showElapsedTime(struct timeval start, struct timeval end) {
#ifdef _CONSOLE_
	cout << (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec) << endl;
#endif
}

// calculate elapsed time
double calculateElapsedTime(struct timeval start, struct timeval end) {
	return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
}

// check that input file exists
inline bool fileExists(const char* file) {
    struct stat buf;
    return (stat(file, &buf) == 0);
}

// main function
int main(int argc, char *argv[]) {

	// timestamps
	// 1. data read
	// 2. data preprocess
	// 3. shortest path search by distance
	// 4. shortest path search by time
	// 5. data write
	struct timeval startDataRead;
	struct timeval endDataRead;
	struct timeval startPre;
	struct timeval endPre;
	struct timeval startSearch1;
	struct timeval endSearch1;
	struct timeval startSearch2;
	struct timeval endSearch2;
	struct timeval startDataWrite;
	struct timeval endDataWrite;

	gettimeofday(&startDataRead, NULL);

	// parameters
	const char* inputRoadFile;
	const char* inputNodeFile;
	const char* inputPolygonFile;
	const char* sourceNode;
	const char* destinationNode;
	const char* outputShortestDistancePathFile;
	const char* outputShortestTimePathFile;
	const char* outputStatFile;

	if (argc == 1) { // TEST MODE
		inputNodeFile = "/home/makrai/giscup2015/data/sfo_nodes.txt";
		inputRoadFile = "/home/makrai/giscup2015/data/sfo_roads.txt";
		inputPolygonFile = "/home/makrai/giscup2015/data/sfo_poly.txt";
		sourceNode = "50096828";
		destinationNode = "48432214";

//		inputNodeFile = "/home/makrai/giscup2015/data/example_nodes.txt";
//		inputRoadFile = "/home/makrai/giscup2015/data/example_roads.txt";
//		inputPolygonFile = "/home/makrai/giscup2015/data/example_roads.txt";
//		sourceNode = "1";
//		destinationNode = "10";

//		inputNodeFile = "/home/makrai/giscup2015/data/example2_nodes.txt";
//		inputRoadFile = "/home/makrai/giscup2015/data/example2_roads.txt";
//		inputPolygonFile = "/home/makrai/giscup2015/data/sfo_poly.txt";
//		sourceNode = "6";
//		destinationNode = "20";

		outputShortestDistancePathFile = "/media/sf_ubuntu_shared_folder/output_SP_distance.txt";
		outputShortestTimePathFile = "/media/sf_ubuntu_shared_folder/output_SP_time.txt";
		outputStatFile = "/media/sf_ubuntu_shared_folder/output_Stat.txt";
	} else if (argc == 9) { // NORMAL MODE
		inputRoadFile = argv[1];
		inputNodeFile = argv[2];
		inputPolygonFile = argv[3];
		sourceNode = argv[4];
		destinationNode = argv[5];
		outputShortestDistancePathFile = argv[6];
		outputShortestTimePathFile = argv[7];
		outputStatFile = argv[8];
	} else {
		cout << "Not enough parameter..." << endl;
		return 0;
	}

#ifdef _DEBUG_
	cout << "Parameters:" << endl;
	cout << "\tinputNodeFile: " << inputNodeFile << endl << "\tinputRoadFile: " << inputRoadFile << endl << "\tinputPolygonFile: " << inputPolygonFile << endl << "\tsourceNode: " << sourceNode << endl;
	cout << "\tdestinationNode: " << destinationNode << endl << "\toutputShortestDistancePathFile: " << outputShortestDistancePathFile << endl << "\toutputShortestTimePathFile: " << outputShortestTimePathFile << endl << "\toutputStatFile: " << outputStatFile << endl;
#endif

	// check input files
	if (!fileExists(inputRoadFile)) {
		cout << "Problem: input road file (" << inputRoadFile << ") does not exist..." << endl;
		return 0;
	}
	if (!fileExists(inputNodeFile)) {
		cout << "Problem: input node file (" << inputNodeFile << ") does not exist..." << endl;
		return 0;
	}
	if (!fileExists(inputPolygonFile)) {
		cout << "Problem: input polygon file (" << inputPolygonFile << ") does not exist..." << endl;
		return 0;
	}

	// buffers
	unsigned char* buffer = new unsigned char[BUFFER_SIZE];
	unsigned char* buffer2 = new unsigned char[BUFFER_SIZE];

	// storages
	RoadStore* roadStore = new RoadStore(BUFFER_SIZE);
	NodeStore* nodeStore = new NodeStore(BUFFER_SIZE);
	PolygonStore* polygonStore = new PolygonStore(BUFFER_SIZE / 4096);

	// road parser & polygon parser
	RoadParser roadParser;
	PolygonParser PolygonParser;

	// loading data from files
	roadParser.loadNodeFile(inputNodeFile, buffer, BUFFER_SIZE, nodeStore);
	roadParser.loadRoadFile(inputRoadFile, buffer, BUFFER_SIZE, roadStore);
	PolygonParser.parse(inputPolygonFile, buffer, BUFFER_SIZE, polygonStore);

	// allocating the necessary memory
	int* sp1 = new int[roadStore->storeSize];
	int* sp2 = new int[roadStore->storeSize];

#ifdef ALGO3
	int* sp3 = new int[roadStore->storeSize];
	int* sp4 = new int[roadStore->storeSize];
#endif

	int* bannedNodes = sp1;

	int* simplyStartNode = new int[roadStore->storeSize];
	int* simplyEndNode = new int[roadStore->storeSize];
	double* simplyLength = new double[roadStore->storeSize];
	double* simplyTime = new double[roadStore->storeSize];
	int* simplySeekOffset = new int[roadStore->storeSize];
	int* simplySeekCount = new int[roadStore->storeSize];
	int* simplySeek = new int[roadStore->storeSize];
	int* simplySeekLength = new int[roadStore->storeSize];

	// temporary arrays for simplification and other operations
	int* array1 = new int[nodeStore->storeSize];
	int* array2 = new int[nodeStore->storeSize];
	int* array3 = new int[nodeStore->storeSize];
	int* array4 = new int[nodeStore->storeSize];
	int* array5 = new int[roadStore->storeSize];
	int* array6 = new int[nodeStore->storeSize];
	double* array7 = new double[nodeStore->storeSize];
#ifdef ALGO3
	int* array1a = new int[nodeStore->storeSize];
	int* array2a = new int[nodeStore->storeSize];
	double* array7a = new double[nodeStore->storeSize];
#endif

#ifdef BINARYHEAP
	BinaryHeap<double>* heap = new BinaryHeap<double>(nodeStore->storeSize, 0.0, std::numeric_limits<double>::max(), array1, array2, array7);
#endif
#ifdef BINARYHEAP4ARY
	BinaryHeap4ary<double>* heap = new BinaryHeap4ary<double>(nodeStore->storeSize, 0.0, std::numeric_limits<double>::max(), array1, array2, array7);
#endif

	gettimeofday(&endDataRead, NULL);
	gettimeofday(&startPre, NULL);

#ifdef _DEBUG_
	// print out general statistics
	cout << "#node: " << nodeStore->size << endl;
	cout << "#road: " << roadStore->size << endl;
	cout << "#polygon: " << polygonStore->size << endl;
#endif

	// polygon obstacles avoidance by banning nodes out
	polygonStore->doCalculation(bannedNodes, nodeStore, POLYGON_SEQUENTIAL);

#ifdef _DEBUG_
	int bannedNodeCounter = 0;
	for (int i = 0; i < nodeStore->size; ++i) {
		bannedNodeCounter += bannedNodes[i];
	}
	cout << "#bannedNodes: " << bannedNodeCounter << endl;
#endif

#ifdef ALGO1
	AStarForwardShortestPath* spDistance = new AStarForwardShortestPath(sp1);
	AStarForwardShortestPath* spTime = new AStarForwardShortestPath(sp2);
#endif

#ifdef ALGO2
	AStarBackwardShortestPath* spDistance = new AStarBackwardShortestPath(sp1);
	AStarBackwardShortestPath* spTime = new AStarBackwardShortestPath(sp2);
#endif

#ifdef ALGO3
	AStarBidirectionalShortestPath* spDistance = new AStarBidirectionalShortestPath(sp1, sp2);
	AStarBidirectionalShortestPath* spTime = new AStarBidirectionalShortestPath(sp3, sp4);
#endif

	int sourceNodeId = atoi(sourceNode);
	int destinationNodeId = atoi(destinationNode);

	// reassign id for nodes
	nodeStore->sort();

	// use new ids in roadStore
	roadStore->reassignNodeIds(nodeStore);

	int sourceNodeIndex = nodeStore->getIndex(sourceNodeId);
	int destinationNodeIndex = nodeStore->getIndex(destinationNodeId);

#ifdef _GISVISUALIZER_
	GISVisualizer gisVisualizer;
	gisVisualizer.writeGISFiles("/media/sf_ubuntu_shared_folder/nodes.csv", "/media/sf_ubuntu_shared_folder/roads.csv", "/media/sf_ubuntu_shared_folder/bannedNodes.csv", "/media/sf_ubuntu_shared_folder/polygons.csv", nodeStore, roadStore, polygonStore, array1);
#endif

	SimplifiedRoadStore* simplifiedRoadStore = new SimplifiedRoadStore(nodeStore, roadStore, sourceNodeIndex, destinationNodeIndex, ROADSIMPLIFICATION_SIMPLIFIED,
		simplyStartNode, simplyEndNode, simplyLength, simplyTime, simplySeekOffset, simplySeekCount, simplySeek, simplySeekLength,
		array1, array2, array3, array4, array5, array6);

#ifdef _GISVISUALIZER_
	gisVisualizer.writeSimplifiedRoads("/media/sf_ubuntu_shared_folder/simplifiedRoads.csv", nodeStore, simplifiedRoadStore);
#endif

#ifdef _DEBUG_
	// print out general statistics
	cout << "#sroad: " << simplifiedRoadStore->size << endl;
#endif

	// create neighbourdatabase
#if defined(ALGO1) || defined(ALGO3)
	NeighbourDataBase* forwardNeighbour = new NeighbourDataBase(nodeStore, simplifiedRoadStore, NEIGHBOURDATABASE_FORWARD, sp1);
#endif
#if defined(ALGO2) || defined(ALGO3)
	NeighbourDataBase* backwardNeighbour = new NeighbourDataBase(nodeStore, simplifiedRoadStore, NEIGHBOURDATABASE_BACKWARD, sp1);
#endif

	gettimeofday(&endPre, NULL);
	gettimeofday(&startSearch1, NULL);

#ifdef ALGO1
	AStarForwardBinaryHeap* algo1 = new AStarForwardBinaryHeap(forwardNeighbour, nodeStore, roadStore, heap);
	algo1->shortestPath(sourceNodeId, destinationNodeId, SHORTESTPATH_DISTANCE);
	// cout << algo1->result << endl;
	algo1->reconstructPath(spDistance);
	gettimeofday(&endSearch1, NULL);
#endif
#if defined(_GISVISUALIZER_) && defined(ALGO1)
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo1_heap_distance.csv", "/media/sf_ubuntu_shared_folder/algo1_closed_distance.csv", "/media/sf_ubuntu_shared_folder/algo1_sp_distance.csv", algo1);
#endif
#ifdef ALGO1
	gettimeofday(&startSearch2, NULL);
	algo1->shortestPath(sourceNodeId, destinationNodeId, SHORTESTPATH_TIME);
	// cout << algo1->result << endl;
	algo1->reconstructPath(spTime);
#endif
#if defined(_GISVISUALIZER_) && defined(ALGO1)
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo1_heap_time.csv", "/media/sf_ubuntu_shared_folder/algo1_closed_time.csv", "/media/sf_ubuntu_shared_folder/algo1_sp_time.csv", algo1);
#endif

#ifdef ALGO2
	AStarBackwardBinaryHeap* algo2 = new AStarBackwardBinaryHeap(backwardNeighbour, nodeStore, roadStore, array1, array2, array7);
	algo2->shortestPath(sourceNodeId, destinationNodeId, SHORTESTPATH_DISTANCE);
	// cout << algo2->result << endl;
	algo2->reconstructPath(spDistance);
	gettimeofday(&endSearch1, NULL);
#endif
#if defined(_GISVISUALIZER_) && defined(ALGO2)
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo2_heap_distance.csv", "/media/sf_ubuntu_shared_folder/algo2_closed_distance.csv", "/media/sf_ubuntu_shared_folder/algo2_sp_distance.csv", algo2);
#endif
#ifdef ALGO2
	gettimeofday(&startSearch2, NULL);
	algo2->shortestPath(sourceNodeId, destinationNodeId, SHORTESTPATH_TIME);
	// cout << algo1->result << endl;
	algo2->reconstructPath(spTime);
#endif
#if defined(_GISVISUALIZER_) && defined(ALGO2)
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo2_heap_time.csv", "/media/sf_ubuntu_shared_folder/algo2_closed_time.csv", "/media/sf_ubuntu_shared_folder/algo2_sp_time.csv", algo2);
#endif

#ifdef ALGO3
	AStarBidirectionalBinaryHeap* algo3 = new AStarBidirectionalBinaryHeap(forwardNeighbour, backwardNeighbour, nodeStore, roadStore, array1, array2, array7, array1a, array2a, array7a);
	algo3->shortestPath(sourceNodeId, destinationNodeId, SHORTESTPATH_DISTANCE);
	// cout << algo2->result << endl;
	algo3->reconstructPath(spDistance);
	gettimeofday(&endSearch1, NULL);
#endif
#if defined(_GISVISUALIZER_) && defined(ALGO3)
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo3_heap_distance.csv", "/media/sf_ubuntu_shared_folder/algo3_closed_distance.csv", "/media/sf_ubuntu_shared_folder/algo3_sp_distance.csv", algo3);
#endif
#ifdef ALGO3
	gettimeofday(&startSearch2, NULL);
	algo3->shortestPath(sourceNodeId, destinationNodeId, SHORTESTPATH_TIME);
	// cout << algo1->result << endl;
	algo3->reconstructPath(spTime);
#endif
#if defined(_GISVISUALIZER_) && defined(ALGO3)
	gisVisualizer.writeAStarBinaryHeap("/media/sf_ubuntu_shared_folder/algo3_heap_time.csv", "/media/sf_ubuntu_shared_folder/algo3_closed_time.csv", "/media/sf_ubuntu_shared_folder/algo3_sp_time.csv", algo3);
#endif

	gettimeofday(&endSearch2, NULL);
	gettimeofday(&startDataWrite, NULL);

	// shortest path writer
	ShortestPathWriter shortestPathWriter;
	shortestPathWriter.write(spDistance, outputShortestDistancePathFile, inputRoadFile, simplifiedRoadStore, nodeStore, buffer, buffer2, BUFFER_SIZE);
	shortestPathWriter.write(spTime, outputShortestTimePathFile, inputRoadFile, simplifiedRoadStore, nodeStore, buffer, buffer2, BUFFER_SIZE);

#ifdef _DEBUG_
	cout << "ShortestPathDistance: length: " << spDistance->length << ", time: " << spDistance->time << endl;
	cout << "ShortestPathTime: length: " << spTime->length << ", time: " << spTime->time << endl;
#endif

	// stat file writer
	StatFileWriter statFileWriter;
	double preTime = calculateElapsedTime(startPre, endPre);
	double searchDistance = calculateElapsedTime(startSearch1, endSearch1);
	double searchTime = calculateElapsedTime(startSearch2, endSearch2);
	statFileWriter.write(spDistance, spTime, preTime + searchDistance, preTime + searchTime, outputStatFile);

#ifdef ALGO1
	delete algo1;
#endif

#ifdef ALGO2
	delete algo2;
#endif

#ifdef ALGO3
	delete algo3;
#endif

	// delete simplifiedRoadSTORe
	delete simplifiedRoadStore;

	// dispose storages
	delete roadStore;
	delete nodeStore;
	delete polygonStore;

	// dispose neighbourDB
#if defined(ALGO1) || defined(ALGO3)
	delete forwardNeighbour;
#endif

#if defined(ALGO2) || defined(ALGO3)
	delete backwardNeighbour;
#endif

	// delete arrays
	delete spDistance;
	delete spTime;

	delete [] buffer;
	delete [] buffer2;

	delete [] sp1;
	delete [] sp2;

	delete [] simplyStartNode;
	delete [] simplyEndNode;
	delete [] simplyLength;
	delete [] simplyTime;
	delete [] simplySeekOffset;
	delete [] simplySeekCount;
	delete [] simplySeek;
	delete [] simplySeekLength;

	delete [] array1;
	delete [] array2;
	delete [] array3;
	delete [] array4;
	delete [] array5;
	delete [] array6;
	delete [] array7;

	gettimeofday(&endDataWrite, NULL);

//	cout << "DataRead:";
	showElapsedTime(startDataRead, endDataRead);
//	cout << "Pre:";
	showElapsedTime(startPre, endPre);
//	cout << "Search1:";
	showElapsedTime(startSearch1, endSearch1);
//	cout << "Search1:";
	showElapsedTime(startSearch2, endSearch2);
//	cout << "DataWrite:";
	showElapsedTime(startDataWrite, endDataWrite);

	return 0;
}

