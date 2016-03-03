/*
 * AStarBackwardShortestPath.h
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#ifndef ASTARBACKWARDSHORTESTPATH_H_
#define ASTARBACKWARDSHORTESTPATH_H_

#include "../ShortestPath.h"

class AStarBackwardShortestPath : public ShortestPath {
public:
	int* storage;
	int current;
	int roads;
	AStarBackwardShortestPath(int* storage);
	void init();
	bool hasNext();
	int next();
	void addRoad(int id);
	void lastRoadAdded();
};


#endif /* ASTARBACKWARDSHORTESTPATH_H_ */
