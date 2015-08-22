/*
 * StatFileWriter.h
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#ifndef STATFILEWRITER_H_
#define STATFILEWRITER_H_

#include "../sp/ShortestPath.h"

class StatFileWriter {
public:
	void write(ShortestPath* spDistance, ShortestPath* spTime, double execDistance, double execTime, const char* fileName);
};


#endif /* STATFILEWRITER_H_ */
