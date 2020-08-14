#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Input.h"
#include "Entity.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>


enum Direction
{
	BACK = -1,
	ADVANCE = 1
};

class ENGINEDLL_API CameraC : public Component
{	
	Transform* transform;
	vec3 globalPosition;
	vec3 viewDirection;
	vec4 right;
	vec4 up;
	vec4 fwd;
	vec4 pos;
	mat4 vMatrix;
	const float VERTICAL_RANGE = 70.0f;
	Renderer* renderer;
	Input* input;

public:

	void UpdateRendererPos();
	CameraC(Renderer* rend);	
	float speed;
	float rotationSpeed;
	void Teleport(float mountX, float mountY, float mountZ);	
	void Move(float mountX, float mountY, float mountZ);
	void WalkFront(Direction dir);
	void WalkSideWays(Direction dir);
	void Rise(Direction dir);
	void Pitch(float degrees);
	void Yaw(float degrees);
	void Roll(float degrees);
	void Rotate(float horRotation, float verRotation);
	void Start() override;
	void Draw() override;
	void Update() override;		
	unsigned int SetVertices(float* vertices, int count);
	~CameraC();
};

