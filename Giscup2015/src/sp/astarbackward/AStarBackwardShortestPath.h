/*
 * AStarBackwardShortestPath.h
 *
 *  Created on: 22 Aug 2015
 *  Author: Gabor Makrai
 */

#ifndef ASTARBACKWARDSHORTESTPATH_H_
#define ASTARBACKWARDSHORTESTPATH_H_

#include "../ShortestPath.h"

/**
 *
 * Class contains the shortest path produced by the Backward A* shortest path algorithm
 *
 */
class AStarBackwardShortestPath : public ShortestPath {
public:
	int* storage;
	int current;
	int roads;
	AStarBackwardShortestPath(int* storage);
	bool hasNext();
	int next();
	void addRoad(int id);
	void lastRoadAdded();
};


#endif /* ASTARBACKWARDSHORTESTPATH_H_ */
