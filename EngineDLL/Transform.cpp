#include "Transform.h"

Transform::Transform()
{
	name = "Transform Compnent";
	vectorPosition = vectorRotation = vectorScale = glm::vec3(0.0f);

	model = glm::mat4(1.0f);
	translationMatrix = glm::mat4(1.0f);
	rotateX = glm::mat4(1.0f);
	rotateY = glm::mat4(1.0f);
	rotateZ = glm::mat4(1.0f);
	scallingMatrix = glm::mat4(1.0f);

	UpdateModel();	
}



Transform::~Transform()
{
}

void Transform::Start()
{

}

void Transform::Update()
{
	
}

void Transform::Draw()
{

}

void Transform::UpdateModel()
{
	model = translationMatrix * rotateX * rotateY * rotateZ * scallingMatrix;
}

void Transform::Translate(glm::vec3 vector3)
{
	vectorPosition += vector3;

	// Changes the actual position multiplying Matrix4x4 * position
	translationMatrix = glm::translate(glm::mat4(1.0f), vectorPosition);


	UpdateModel();
}

void Transform::Translate(float newX, float newY, float newZ)
{
	// Changes the actual position multiplying Matrix4x4 * position
	vectorPosition += glm::vec3(newX, newY, newZ);

	translationMatrix = glm::translate(glm::mat4(1.0f), vectorPosition);

	UpdateModel();
}

void Transform::Teleport(float newX, float newY, float newZ)
{
	// Changes the actual position to the new position
	vectorPosition = glm::vec3(newX, newY, newZ);

	translationMatrix = glm::translate(glm::mat4(1.0f), vectorPosition);

	UpdateModel();
}

void Transform::Scale(glm::vec3 vector3)
{
	scallingMatrix = glm::scale(vector3);

	vectorScale += vector3;

	UpdateModel();
}

void Transform::Scale(float newX, float newY, float newZ)
{
	glm::vec3 vector3(newX, newY, newZ);

	scallingMatrix = glm::scale(vector3);

	vectorScale += vector3;

	UpdateModel();
}

void Transform::RotateX(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[1] = vecAxis[2] = 0.0f;
	vecAxis[0] = 1.0f;

	rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vecAxis);

	vectorRotation += vecAxis;

	UpdateModel();
}

void Transform::RotateY(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[0] = vecAxis[2] = 0.0f;
	vecAxis[1] = 1.0f;

	rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vecAxis);

	vectorRotation += vecAxis;

	UpdateModel();
}

void Transform::RotateZ(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[0] = vecAxis[1] = 0.0f;
	vecAxis[2] = 1.0f;

	rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(angle), vecAxis);

	vectorRotation += vecAxis;

	UpdateModel();
}
