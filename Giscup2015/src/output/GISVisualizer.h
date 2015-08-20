/*
 * GISVisualizer.h
 *
 *  Created on: 20 Aug 2015
 *      Author: makrai
 */

#ifndef GISVISUALIZER_H_
#define GISVISUALIZER_H_

#define NOISE_LEVEL 20.0

#include "../data/NodeStore.h"
#include "../data/RoadStore.h"

class GISVisualizer {
public:
	void writeGISFiles(const char* nodeFile, const char* roadFile, NodeStore* nodeStore, RoadStore* roadStore);
};


#endif /* GISVISUALIZER_H_ */
