/*
 * ShortestPath.h
 *
 *  Created on: 22 Aug 2015
 *      Author: Gabor Makrai
 */

#ifndef SHORTESTPATH_H_
#define SHORTESTPATH_H_

class ShortestPath {
public:
	double length;
	double time;
	virtual bool hasNext() = 0;
	virtual int next() = 0;
	virtual ~ShortestPath() { }
};

#endif /* SHORTESTPATH_H_ */
