//============================================================================
// Name        : Giscup2015.cpp
// Author      : Gabor Makrai
// Version     :
// Copyright   : x
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "RoadParser.h"
#include "RoadStore.h"

#include <iostream>
using namespace std;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16384
#endif

int main() {
	unsigned char* buffer = new unsigned char[BUFFER_SIZE];

	RoadStore* roadStore = new RoadStore(BUFFER_SIZE);

	RoadParser roadParser;
	roadParser.loadFile("/home/makrai/giscup2015/data/sfo_roads.txt", buffer, BUFFER_SIZE, roadStore);

	roadStore->dispose();
	delete roadStore;

	delete [] buffer;

	return 0;
}
