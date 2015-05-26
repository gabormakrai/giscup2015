#pragma once

#include <cstdint>

class Coordinate
{
public:
	static uint64_t getHash(double x, double y);
	static void getXY(uint64_t hash, double& x, double& y);
	static void getXY(uint64_t hash, float& x, float& y);
	static void convertHashArray(uint64_t* coordinates, int coordinatesCount, float*& x, float*& y);
	static float distance(float& x1, float& y1, float& x2, float& y2);
};