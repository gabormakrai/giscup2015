#pragma once

#include <cstdint>
#include <list>

class Link
{
public:
	int v1;
	int v2;
	Link(int v1, int v2);
};

class RoadParser
{
public:
	void parseFile(char* fileName, uint64_t* coordinates, int coordinatesCount, std::list<Link>& links);
};
