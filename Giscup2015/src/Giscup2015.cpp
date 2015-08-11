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

#include <iostream>
using namespace std;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16384
#endif

int main() {
	// buffer
	unsigned char* buffer = new unsigned char[BUFFER_SIZE];

	// storages
	RoadStore* roadStore = new RoadStore(BUFFER_SIZE);
	NodeStore* nodeStore = new NodeStore(BUFFER_SIZE);

	// road parser
	RoadParser roadParser;

	// loading data from files
	roadParser.loadNodeFile("/home/makrai/giscup2015/data/sfo_nodes2.txt", buffer, BUFFER_SIZE, nodeStore);
	cout << "#node: " << nodeStore->size << endl;

	roadParser.loadRoadFile("/home/makrai/giscup2015/data/sfo_roads.txt", buffer, BUFFER_SIZE, roadStore);
	cout << "#road: " << roadStore->size << endl;

	// reassign id for nodes
	nodeStore->sort();

	// use new ids in roadStore
	// roadStore->reassignNodeIds(nodeStore);

	// dispose roadStore
	roadStore->dispose();
	delete roadStore;

	// dispose nodeStore
	nodeStore->dispose();
	delete nodeStore;

	delete [] buffer;

	return 0;
}
