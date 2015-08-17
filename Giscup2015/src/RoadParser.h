/*
 * RoadParser.h
 *
 *  Created on: 10 Aug 2015
 *      Author: makrai
 */

#ifndef ROADPARSER_H_
#define ROADPARSER_H_

#include <fstream>
#include <stdlib.h>
#include "RoadStore.h"
#include "NodeStore.h"

class RoadParser {
public:
	void loadRoadFile(const char* fileName, unsigned char* buffer, int bufferSize, RoadStore* roadStore);
	void loadNodeFile(const char* fileName, unsigned char* buffer, int bufferSize, NodeStore* nodeStore);
};

#endif /* ROADPARSER_H_ */
