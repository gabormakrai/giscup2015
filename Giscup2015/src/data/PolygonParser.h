/*
 * PolygonParser.h
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#ifndef POLYGONPARSER_H_
#define POLYGONPARSER_H_

//#define _PDEBUG_

#include "PolygonStore.h"

class PolygonParser {
public:
	void parse(const char* fileName, unsigned char* buffer, int bufferSize, PolygonStore* store);
};

#endif /* POLYGONPARSER_H_ */
