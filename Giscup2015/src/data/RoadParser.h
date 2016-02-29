/*
 * RoadParser.h
 *
 *  Created on: 10 Aug 2015
 *      Author: Gabor Makrai
 */

#ifndef ROADPARSER_H_
#define ROADPARSER_H_

// #define _DEBUG_

#include "RoadStore.h"
#include "NodeStore.h"

/**
 *
 * A parser class for parsing road and node file
 *
 */
class RoadParser {
public:
	void loadRoadFile(const char* fileName, unsigned char* buffer, int bufferSize, RoadStore* roadStore);
	void loadNodeFile(const char* fileName, unsigned char* buffer, int bufferSize, NodeStore* nodeStore);
};

#endif /* ROADPARSER_H_ */
