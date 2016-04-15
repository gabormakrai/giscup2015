/*
 * ShortestPathWriter.h
 *
 *  Created on: 22 Aug 2015
 *  Author: Gabor Makrai
 */

#ifndef SHORTESTPATHWRITER_H_
#define SHORTESTPATHWRITER_H_

#include "../sp/ShortestPath.h"
#include "../data/SimplifiedRoadStore.h"
#include "../data/NodeStore.h"

//#define _DEBUG_

/**
 *
 * Class for generating the required output shortest path file
 *
 */
class ShortestPathWriter {
public:
	void write(ShortestPath* sp, const char* fileName, const char* roadFile, SimplifiedRoadStore* simplifiedRoadStore, NodeStore* nodeStore, unsigned char* buffer, unsigned char* buffer2, int bufferSize);
};

#endif /* SHORTESTPATHWRITER_H_ */
