/*
 * GISVisualizer.cpp
 *
 *  Created on: 20 Aug 2015
 *      Author: makrai
 */

#include "GISVisualizer.h"
#include <fstream>
#include <iomanip>
#include <stdlib.h>

void GISVisualizer::writeGISFiles(const char* nodeFile, const char* roadFile, NodeStore* nodeStore, RoadStore* roadStore) {

	double* xNoise = new double[nodeStore->size];
	double* yNoise = new double[nodeStore->size];

	srand(42);

	for (int i = 0; i < nodeStore->size; ++i) {
		double noise = ((double)rand() / (RAND_MAX)) * 2.0 * NOISE_LEVEL - NOISE_LEVEL;
		xNoise[i] = noise;
		noise = ((double)rand() / (RAND_MAX)) * 2.0 * NOISE_LEVEL - NOISE_LEVEL;
		yNoise[i] = noise;
	}

	std::fstream fs;
	fs.open(nodeFile, std::fstream::out);

	fs << "id,x,y" << std::endl;

	for (int i = 0; i < nodeStore->size; ++i) {
		fs << std::setprecision(16) << nodeStore->id[i] << "," << nodeStore->x[i]+xNoise[i] << "," << nodeStore->y[i]+yNoise[i] << std::endl;
	}

	fs.close();

	fs.open(roadFile, std::fstream::out);

	fs << "id;linestring" << std::endl;

	for (int i = 0; i < roadStore->size; ++i) {
		double x1 = nodeStore->x[roadStore->startNode[i]] + xNoise[roadStore->startNode[i]];
		double y1 = nodeStore->y[roadStore->startNode[i]] + yNoise[roadStore->startNode[i]];
		double x2 = nodeStore->x[roadStore->endNode[i]] + xNoise[roadStore->endNode[i]];
		double y2 = nodeStore->y[roadStore->endNode[i]] + yNoise[roadStore->endNode[i]];
		fs << std::setprecision(16) << roadStore->edgeId[i] << ";LINESTRING(" << x1 << " " << y1 << "," << x2 << " " << y2 << ")" << std::endl;
	}

	fs.close();

}
