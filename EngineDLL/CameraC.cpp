#include "CameraC.h"

void CameraC::Start()
{
	
}


CameraC::CameraC(Renderer* rend) :Component()
{
	input = Input::getInstance();
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
	rotationSpeed = 90.0f;	
	renderer->SetCameraPosition(vMatrix);
	renderer->SetPerspectiveProjection(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 400.0f);	
	renderer->ExtractPlanes(pos, fwd, right, up, 0.1f, 400.0f, 4.0f / 3.0f, radians(45.0f));
}

void CameraC::Update()
{
	//Uncomment for mouse movement, breaks noFC camera
	/*float horRotation = input->GetAxis(Axis::HORIZONTAL) * rotationSpeed * Defs::getInstance()->deltaTime;
	float verRotation = input->GetAxis(Axis::VERTICAL)   * rotationSpeed * Defs::getInstance()->deltaTime;
	Rotate(horRotation, verRotation);*/
}

CameraC::~CameraC()
{

}

unsigned int CameraC::SetVertices(float* vertices, int count)
{
	return 0;
}

void CameraC::UpdateRendererPos()
{
	vMatrix = lookAt(
		(vec3)pos,
		(vec3)(pos + fwd),
		(vec3)up
	);

	renderer->SetCameraPosition(vMatrix);
	renderer->ExtractPlanes(pos, fwd, right, up, 0.1f, 400.0f, 4.0f / 3.0f, radians(45.0f));
}

void CameraC::Teleport(float mountX, float mountY, float mountZ)
{
	pos.x = mountX;
	pos.y = mountY;
	pos.z = mountZ;

	UpdateRendererPos();
}

void CameraC::Move(float mountX, float mountY, float mountZ)
{
	pos = translate(mat4(1.0f), (vec3)((right * mountX) + (up * mountY) + (fwd * mountZ))) * pos;

	UpdateRendererPos();
}

void CameraC::WalkFront(Direction dir)
{
	float mountZ = dir * speed * Defs::getInstance()->deltaTime;

	pos = translate(mat4(1.0f), (vec3)(fwd * mountZ)) * pos;

	UpdateRendererPos();
}

void CameraC::WalkSideWays(Direction dir)
{
	float mountX = dir * speed * Defs::getInstance()->deltaTime;

	pos = translate(mat4(1.0f), (vec3)(right * mountX)) * pos;

	UpdateRendererPos();
}

void CameraC::Rise(Direction dir)
{
	float mountY = dir * speed * Defs::getInstance()->deltaTime;

	pos = translate(mat4(1.0f), (vec3)(up * mountY)) * pos;

	UpdateRendererPos();
}

void CameraC::Pitch(float degrees)
{
	fwd = rotate(mat4(1.0f), radians(degrees), vec3(right.x, right.y, right.z)) * fwd;
	up = rotate(mat4(1.0f), radians(degrees), vec3(right.x, right.y, right.z)) * up;

	UpdateRendererPos();
}

void CameraC::Yaw(float degrees)
{
	fwd = rotate(mat4(1.0f), radians(degrees), vec3(up.x, up.y, up.z)) * fwd;
	right = rotate(mat4(1.0f), radians(degrees), vec3(up.x, up.y, up.z)) * right;

	UpdateRendererPos();
}

void CameraC::Roll(float degrees)
{
	right = rotate(mat4(1.0f), radians(degrees), vec3(fwd.x, fwd.y, fwd.z)) * right;
	up = rotate(mat4(1.0f), radians(degrees), vec3(fwd.x, fwd.y, fwd.z)) * up;

	UpdateRendererPos();
}

void CameraC::Rotate(float horRotation, float verRotation)
{
	verRotation = clamp(verRotation, -70.0f, 70.0f);

	Pitch(verRotation);
	Yaw(horRotation);

	up = vec4(0, 1, 0, 0);
}

void CameraC::Draw()
{	
}