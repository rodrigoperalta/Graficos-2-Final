#pragma once


#include "Renderer.h"

struct BoundingBox
{
	vec3* vertex;

	bool initialized = false;

	float lMinX = 999999.0f, lMinY = 999999.0f, lMinZ = 999999.0f;
	float lMaxX = -999999.0f, lMaxY = -999999.0f, lMaxZ = -999999.0f;

	BoundingBox() { vertex = new vec3[8]; }

	void UpdateData()
	{
		vertex[0].x = lMaxX; vertex[1].x = lMaxX;  vertex[2].x = lMinX;  vertex[3].x = lMinX;
		vertex[0].y = lMaxY; vertex[1].y = lMaxY;  vertex[2].y = lMaxY;  vertex[3].y = lMaxY;
		vertex[0].z = lMaxZ; vertex[1].z = lMinZ;  vertex[2].z = lMaxZ;  vertex[3].z = lMinZ;

		vertex[4].x = lMaxX; vertex[5].x = lMaxX;  vertex[6].x = lMinX;  vertex[7].x = lMinX;
		vertex[4].y = lMinY; vertex[5].y = lMinY;  vertex[6].y = lMinY;  vertex[7].y = lMinY;
		vertex[4].z = lMaxZ; vertex[5].z = lMinZ;  vertex[6].z = lMaxZ;  vertex[7].z = lMinZ;

		initialized = true;
	}

	void CompareData(BoundingBox childFcData)
	{
		if (childFcData.vertex[0].x > vertex[0].x) // MaxX
		{
			vertex[0].x = childFcData.vertex[0].x;
			vertex[1].x = childFcData.vertex[1].x;
			vertex[4].x = childFcData.vertex[4].x;
			vertex[5].x = childFcData.vertex[5].x;
		}

		if (childFcData.vertex[0].y > vertex[0].y) // MaxY
		{
			vertex[0].y = childFcData.vertex[0].y;
			vertex[1].y = childFcData.vertex[1].y;
			vertex[2].y = childFcData.vertex[2].y;
			vertex[3].y = childFcData.vertex[3].y;
		}

		if (childFcData.vertex[0].z > vertex[0].z) // MaxZ
		{
			vertex[0].z = childFcData.vertex[0].z;
			vertex[2].z = childFcData.vertex[2].z;
			vertex[4].z = childFcData.vertex[4].z;
			vertex[6].z = childFcData.vertex[6].z;
		}

		if (childFcData.vertex[7].x < vertex[7].x) // MinX
		{
			vertex[2].x = childFcData.vertex[2].x;
			vertex[3].x = childFcData.vertex[3].x;
			vertex[6].x = childFcData.vertex[6].x;
			vertex[7].x = childFcData.vertex[7].x;
		}

		if (childFcData.vertex[7].y < vertex[7].y) // MinY
		{
			vertex[4].y = childFcData.vertex[4].y;
			vertex[5].y = childFcData.vertex[5].y;
			vertex[6].y = childFcData.vertex[6].y;
			vertex[7].y = childFcData.vertex[7].y;
		}

		if (childFcData.vertex[7].z < vertex[7].z) // MinZ
		{
			vertex[1].z = childFcData.vertex[1].z;
			vertex[3].z = childFcData.vertex[3].z;
			vertex[5].z = childFcData.vertex[5].z;
			vertex[7].z = childFcData.vertex[7].z;
		}
	}

	void NewValue(const vec3 newValue)
	{
		if (newValue.x > lMaxX) lMaxX = newValue.x;
		if (newValue.x < lMinX) lMinX = newValue.x;
		if (newValue.y > lMaxY) lMaxY = newValue.y;
		if (newValue.y < lMinY) lMinY = newValue.y;
		if (newValue.z > lMaxZ) lMaxZ = newValue.z;
		if (newValue.z < lMinZ) lMinZ = newValue.z;
	}
};