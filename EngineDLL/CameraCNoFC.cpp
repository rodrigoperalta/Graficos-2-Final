#include "CameraCNoFC.h"

void CameraCNoFC::Start()
{

}


CameraCNoFC::CameraCNoFC(Renderer* rend) :Component()
{
	name = "CameraComponent";
	renderer = rend;
	right = vec4(1, 0, 0, 0);
	up = vec4(0, 1, 0, 0);
	fwd = vec4(0, 0, 1, 0);
	pos = vec4(0, 0, 0, 1);
	vMatrix = lookAt(
		(vec3)pos,
		(vec3)(pos + fwd),
		(vec3)up
	);
	speed = 10.0f;
	rotationSpeed = 50.0f;
	renderer->SetPerspectiveProjection(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 400.0f);	
	
}

void CameraCNoFC::Update()
{
	
}

CameraCNoFC::~CameraCNoFC()
{

}

unsigned int CameraCNoFC::SetVertices(float* vertices, int count)
{
	return 0;
}

void CameraCNoFC::UpdateRendererPos()
{
	vMatrix = lookAt(
		(vec3)pos,
		(vec3)(pos + fwd),
		(vec3)up
	);

	renderer->SetCameraPosition(vMatrix);	
}

void CameraCNoFC::Teleport(float mountX, float mountY, float mountZ)
{
	pos.x = mountX;
	pos.y = mountY;
	pos.z = mountZ;

	UpdateRendererPos();
}

void CameraCNoFC::Move(float mountX, float mountY, float mountZ)
{
	pos = translate(mat4(1.0f), (vec3)((right * mountX) + (up * mountY) + (fwd * mountZ))) * pos;

	UpdateRendererPos();
}

void CameraCNoFC::WalkFront(Direction dir)
{
	float mountZ = dir * speed * Defs::getInstance()->deltaTime;

	pos = translate(mat4(1.0f), (vec3)(fwd * mountZ)) * pos;

	UpdateRendererPos();
}

void CameraCNoFC::WalkSideWays(Direction dir)
{
	float mountX = dir * speed * Defs::getInstance()->deltaTime;

	pos = translate(mat4(1.0f), (vec3)(right * mountX)) * pos;

	UpdateRendererPos();
}

void CameraCNoFC::Rise(Direction dir)
{
	float mountY = dir * speed * Defs::getInstance()->deltaTime;

	pos = translate(mat4(1.0f), (vec3)(up * mountY)) * pos;

	UpdateRendererPos();
}

void CameraCNoFC::Pitch(float degrees)
{
	fwd = rotate(mat4(1.0f), radians(degrees), vec3(right.x, right.y, right.z)) * fwd;
	up = rotate(mat4(1.0f), radians(degrees), vec3(right.x, right.y, right.z)) * up;

	UpdateRendererPos();
}

void CameraCNoFC::Yaw(float degrees)
{
	fwd = rotate(mat4(1.0f), radians(degrees), vec3(up.x, up.y, up.z)) * fwd;
	right = rotate(mat4(1.0f), radians(degrees), vec3(up.x, up.y, up.z)) * right;

	UpdateRendererPos();
}

void CameraCNoFC::Roll(float degrees)
{
	right = rotate(mat4(1.0f), radians(degrees), vec3(fwd.x, fwd.y, fwd.z)) * right;
	up = rotate(mat4(1.0f), radians(degrees), vec3(fwd.x, fwd.y, fwd.z)) * up;

	UpdateRendererPos();
}

void CameraCNoFC::Rotate(float horRotation, float verRotation)
{
	verRotation = clamp(verRotation, -VERTICAL_RANGE, VERTICAL_RANGE);

	Pitch(verRotation);
	Yaw(horRotation);

	up = vec4(0, 1, 0, 0);
}

void CameraCNoFC::Draw()
{
	
}