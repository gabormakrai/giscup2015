/*
 * ShortestPathWriter.h
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#ifndef SHORTESTPATHWRITER_H_
#define SHORTESTPATHWRITER_H_

#include "../sp/ShortestPath.h"
#include "../data/RoadStore.h"
#include "../data/NodeStore.h"

//#define _DEBUG_

class ShortestPathWriter {
public:
	void write(ShortestPath* sp, const char* fileName, const char* roadFile, RoadStore* roadStore, NodeStore* nodeStore, unsigned char* buffer, unsigned char* buffer2, int bufferSize);
};

#endif /* SHORTESTPATHWRITER_H_ */
