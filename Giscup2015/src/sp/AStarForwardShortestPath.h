/*
 * AStarForwardShortestPath.h
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#ifndef ASTARFORWARDSHORTESTPATH_H_
#define ASTARFORWARDSHORTESTPATH_H_

#include "ShortestPath.h"

class AStarForwardShortestPath : public ShortestPath {
public:
	int* storage;
	int current;
	AStarForwardShortestPath(int* storage);
	void init();
	bool hasNext();
	int next();
	void addRoad(int id);
};


#endif /* ASTARFORWARDSHORTESTPATH_H_ */
