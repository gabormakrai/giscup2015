/*
 * StatFileWriter.cpp
 *
 *  Created on: 22 Aug 2015
 *  Author: Gabor Makrai
 */

#include "StatFileWriter.h"
#include <fstream>
#include <iomanip>

void StatFileWriter::write(ShortestPath* spDistance, ShortestPath* spTime, double execDistance, double execTime, const char* fileName) {
	std::ofstream output;
	output.open(fileName);
	output << std::setprecision(5) << spDistance->length << "," << spDistance->time << "," << execDistance / 1000000.0 << std::endl;
	output << std::setprecision(5) << spTime->length << "," << spTime->time << "," << execTime/ 1000000.0 << std::endl;
	output.close();
}


