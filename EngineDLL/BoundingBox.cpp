#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct BoundingBox
{

	vec4* vertex;

	bool initialized = false;

	float minX = 999999.0f, minY = 999999.0f, minZ = 999999.0f;
	float maxX = -999999.0f, maxY = -999999.0f, maxZ = -999999.0f;

	BoundingBox() { vertex = new vec4[8]; }

	void UpdateData()
	{
		

		vertex = new vec4[8];

		vertex[0].x = maxX;	 vertex[1].x = maxX;  vertex[2].x = minX;  vertex[3].x = minX;
		vertex[0].y = maxY;	 vertex[1].y = maxY;  vertex[2].y = maxY;  vertex[3].y = maxY;
		vertex[0].z = maxZ;	 vertex[1].z = minZ;  vertex[2].z = maxZ;  vertex[3].z = minZ;
		vertex[0].w = 1.0f;	 vertex[1].w = 1.0f;  vertex[2].w = 1.0f;  vertex[3].w = 1.0f;

		vertex[4].x = maxX;  vertex[5].x = maxX;  vertex[6].x = minX;  vertex[7].x = minX;
		vertex[4].y = minY;	 vertex[5].y = minY;  vertex[6].y = minY;  vertex[7].y = minY;
		vertex[4].z = maxZ;	 vertex[5].z = minZ;  vertex[6].z = maxZ;  vertex[7].z = minZ;
		vertex[4].w = 1.0f;	 vertex[5].w = 1.0f;  vertex[6].w = 1.0f;  vertex[7].w = 1.0f;

		initialized = true;
	}

	void NewValue(const vec3 newValue)
	{
		if (newValue.x > maxX) maxX = newValue.x;
		if (newValue.x < minX) minX = newValue.x;
		if (newValue.y > maxY) maxY = newValue.y;
		if (newValue.y < minY) minY = newValue.y;
		if (newValue.z > maxZ) maxZ = newValue.z;
		if (newValue.z < minZ) minZ = newValue.z;
	}
};