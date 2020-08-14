#pragma once
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>


#include "Component.h"
#include "Layers.h"




class ENGINEDLL_API Transform : public Component{
protected:

	glm::vec3 vectorPosition;	// Actual Position
	glm::vec3 vectorRotation;	// Actual Rotation
	glm::vec3 vectorScale;		// Actual Scale

	glm::mat4 model;			// Model Matrix
	Transform* parent;
	glm::mat4 translationMatrix;// Translation Matrix
	glm::mat4 rotateX;			// RotationX Matrix
	glm::mat4 rotateY;			// RotationX Matrix
	glm::mat4 rotateZ;			// RotationX Matrix
	glm::mat4 scallingMatrix;	// Scale Matrix

	Layers tag;		// Tag		

public:
	void Start() override;
	void Update() override;
	void Draw() override;
	
	void UpdateModel();
	void Translate(
		glm::vec3 vector3	// Vector3 to Translate
	);
	void Translate(
		float newX,	// Value in X
		float newY,	// Value in Y
		float newZ	// Value in Z
	);
	void Teleport(
		float newX, // Value in X
		float newY,	// Value in Y
		float newZ	// Value in Z
	);
	void Scale(
		glm::vec3 vector3	// Vector3 to Scale
	);
	void Scale(
		float newX, // Value in X
		float newY, // Value in Y
		float newZ  // Value in Z
	);
	void RotateX(
		float angle // Value in X axis
	);
	void RotateY(
		float angle // Value in Y axis
	);
	void RotateZ(
		float angle // Value in Z axis
	);	
	   
	Transform* GetTransform() { return this; } 	
	Transform* GetParent() { return parent; }	
	glm::mat4 GetModelMatrix() { return model; }
	glm::vec3 GetPosition() { return vectorPosition; } // Returns the actual position
	glm::vec3 GetScale() { return vectorScale; } // Returns the actual scale
	glm::vec3 GetRotation() { return vectorRotation; } // Returns the actual rotation		
	
	
	Transform();	
	~Transform();
};


