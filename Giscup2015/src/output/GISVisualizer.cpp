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

void GISVisualizer::writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarForwardBinaryHeap* algo, int from, int to) {

	NodeStore* nodeStore = algo->nodeStore;

	// do the heapFile
	std::fstream fs;
	fs.open(heapNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	BinaryHeap<double>* heap = algo->heap;
	for (int i = 0; i < heap->size; ++i) {
		int node = heap->nodeArray[i];

		fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;

	}
	fs.close();

	// do the closedFile
	fs.open(closedNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	for (int i = 0; i < nodeStore->size; ++i) {
		if (algo->closed[i] == 1) {
			int node = i;
			fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;
		}
	}
	fs.close();

	// do the shortestPath
	fs.open(shortestPathFile, std::fstream::out);
	fs << "id,linestring" << std::endl;

	int current = nodeStore->getIndex(to);
	int previous = algo->previous[current];
	int edgeId = 0;

	while (true) {

		double x1 = nodeStore->x[previous];
		double y1 = nodeStore->y[previous];
		double x2 = nodeStore->x[current];
		double y2 = nodeStore->y[current];

		previous = current;
		current = algo->previous[current];

		fs << std::setprecision(16) << (edgeId++) << ";LINESTRING(" << x1 << " " << y1 << "," << x2 << " " << y2 << ")" << std::endl;

		if (current == nodeStore->getIndex(from)) {
			break;
		}
	}

	fs.close();

}

