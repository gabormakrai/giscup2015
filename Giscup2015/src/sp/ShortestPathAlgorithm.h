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

class ShortestPathAlgorithm {
public:
	void shortestPath(int from, int to);
};

#endif /* SHORTESTPATHALGORITHM_H_ */
