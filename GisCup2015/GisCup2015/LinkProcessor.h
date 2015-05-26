#pragma once

#include <list>
#include "RoadParser.h"

class LinkProcessor
{
public:
	void process(std::list<Link> links, int coordinatesCount);
};