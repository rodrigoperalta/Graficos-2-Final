#pragma once
#include "Component.h"
#include "Renderer.h"
#include "Input.h"
#include "Entity.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "CameraC.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>



class ENGINEDLL_API CameraCNoFC : public Component
{
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
	CameraCNoFC(Renderer* rend);
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
	void Start() override;
	void Draw() override;
	void Update() override;
	void Rotate(float horRotation, float verRotation);
	unsigned int SetVertices(float* vertices, int count);
	~CameraCNoFC();
};

