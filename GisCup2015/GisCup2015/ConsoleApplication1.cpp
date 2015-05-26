#include <iostream>
#include <cstdint>

#include <chrono>

#include "JunctionParser.h"
#include "RoadParser.h"
#include "Coordinate.h"
#include "Search.h"
#include "LinkProcessor.h"

using namespace std;

int main(int argc, char* argv[])
{
	auto start = std::chrono::high_resolution_clock::now();

	uint64_t* coordinates = 0;
	int coordinatesCount = 0;

	JunctionParser junctionParser;
	junctionParser.parseFile("c:\\temp\\giscup2015\\LA_nd_Junctions.shp", coordinates, coordinatesCount);

	float* coordinatesX = 0;
	float* coordinatesY = 0;

	Coordinate::convertHashArray(coordinates, coordinatesCount, coordinatesX, coordinatesY);

	std::list<Link> links;

	RoadParser roadParser;
	roadParser.parseFile("c:\\temp\\giscup2015\\LA_nd_roads.shp", coordinates, coordinatesCount, links);

	std::list<Link> links2;
	links2.push_back(Link(0, 1));
	links2.push_back(Link(1, 2));
	links2.push_back(Link(1, 3));
	links2.push_back(Link(2, 4));
	links2.push_back(Link(3, 4));
	links2.push_back(Link(4, 5));

	LinkProcessor linkProcessor;
	//linkProcessor.process(links, coordinatesCount);
	linkProcessor.process(links2, 6);

	for (int i = 0; i < 10; ++i)
	{
		cout << i << ": " << coordinates[i] << " -> x: " << fixed << coordinatesX[i] << ", y: " << fixed << coordinatesY[i] << endl;
	}

	cout << "is 355391321306662117 in the array: " << Search::binary_search(coordinates, 0, coordinatesCount, 355391321306662117) << endl;
	cout << "is 355391321306662118 in the array: " << Search::binary_search(coordinates, 0, coordinatesCount, 355391321306662118) << endl;

	cout << "distance (1-2): " << fixed << Coordinate::distance(coordinatesX[1], coordinatesY[1], coordinatesX[2], coordinatesY[2]) << endl;

	cout << "coordinatesCount: " << coordinatesCount << endl;

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	cout << "elapsed time: " << elapsed.count() << endl;

	int exitInteger = 0;
	cout << endl << "enter a number: ";
	cin >> exitInteger;

	return 0;
}
