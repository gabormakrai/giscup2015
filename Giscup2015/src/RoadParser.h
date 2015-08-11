/*
 * RoadParser.h
 *
 *  Created on: 10 Aug 2015
 *      Author: makrai
 */

#ifndef ROADPARSER_H_
#define ROADPARSER_H_

#define _DEBUG_

#include <fstream>
#include "RoadStore.h"

class RoadParser {
public:
	void loadFile(const char* fileName, unsigned char* buffer, int bufferSize, RoadStore* roadStore);
};

#endif /* ROADPARSER_H_ */
