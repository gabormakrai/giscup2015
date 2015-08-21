/*
 * ShortestPathAlgorithm.h
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
 */

#ifndef SHORTESTPATHALGORITHM_H_
#define SHORTESTPATHALGORITHM_H_

#include "../data/NodeStore.h"
#include "../data/RoadStore.h"
#include "../data/NeighbourDataBase.h"

#define SHORTESTPATH_SOURCE_NOT_FOUND -1
#define SHORTESTPATH_DESTINATION_NOT_FOUND -2
#define SHORTESTPATH_NO_PATH 0
#define SHORTESTPATH_PATH_FOUND 1

class ShortestPathAlgorithm {
public:
	void shortestPath(int from, int to);
};

#endif /* SHORTESTPATHALGORITHM_H_ */
