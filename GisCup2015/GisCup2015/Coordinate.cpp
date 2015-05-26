#include "Coordinate.h"
#include <math.h>

uint64_t Coordinate::getHash(double x, double y)
{
	uint32_t xInt = static_cast<uint32_t>(x * 100.0);
	uint32_t yInt = static_cast<uint32_t>(y * 100.0);
	return (static_cast<uint64_t>(xInt) << 32) | yInt;
}

void Coordinate::getXY(uint64_t hash, double& x, double& y)
{
	uint32_t yInteger = static_cast<uint32_t>(hash);
	uint32_t xInteger = static_cast<uint32_t>(hash >> 32);
	x = (double)xInteger / 100.0;
	y = (double)yInteger / 100.0;
}

void Coordinate::getXY(uint64_t hash, float& x, float& y)
{
	uint32_t yInteger = static_cast<uint32_t>(hash);
	uint32_t xInteger = static_cast<uint32_t>(hash >> 32);
	x = (float)xInteger / 100.0f;
	y = (float)yInteger / 100.0f;
}

void Coordinate::convertHashArray(uint64_t* coordinates, int coordinatesCount, float*& x, float*& y)
{
	x = new float[coordinatesCount];
	y = new float[coordinatesCount];

	for (int i = 0; i < coordinatesCount; ++i)
	{
		Coordinate::getXY(coordinates[i], x[i], y[i]);
	}
}

float Coordinate::distance(float& x1, float& y1, float& x2, float& y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}