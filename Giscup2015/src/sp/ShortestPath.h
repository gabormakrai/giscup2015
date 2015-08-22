/*
 * ShortestPath.h
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#ifndef SHORTESTPATH_H_
#define SHORTESTPATH_H_

class ShortestPath {
public:
	virtual void init() = 0;
	virtual bool hasNext() = 0;
	virtual int next() = 0;
	virtual ~ShortestPath() { }
};


#endif /* SHORTESTPATH_H_ */
