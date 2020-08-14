#pragma once

#include "Exports.h"
#include "Window.h"
#include "Material.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>

enum class Planes
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	NEAR,
	FAR,
	COUNT
};
enum Halfspace
{
	NEGATIVE = -1,
	POSITIVE = 1
};

enum ProjectionType
{
	Ortho,
	Perspective,
};

class ENGINEDLL_API Renderer
{
	Window* window;				// Reference to the actual window


	GLuint VertexArrayID;		// Id of the Vertex Array

	glm::vec3 eyePosition;		// Actual position of the Camera
	glm::vec3 cameraPosition;	// View of the Camera
	glm::vec3 headUpPosition;	// Head Up of the Camera
	glm::mat4 modelMatrix;		// Position of the entity based on the origin
	glm::mat4 viewMatrix;		// Position of the entity based on the camera
	glm::mat4 projectionMatrix;	// Position of the entity based on the frustum of the camera	
	glm::mat4 MVP;				// The final position of the entity in world space
	glm::mat4 auxPerspectiveMatrix;	//Aux of Position of the entity based on the frustum of the camera
	glm::mat4 auxOrthoMatrix;
	glm::vec4 planes[(int)Planes::COUNT];

	vec4 CreatePlane(const vec3& normal, const vec3& point);
	void NormalizePlanes();

public:

	
	vec4* GetPlanes() { return planes; };
	void ExtractPlanes(vec3 globalPos, vec3 fwd, vec3 right, vec3 up, float zNear, float zFar, float aspRatio, float fovy);
	void ExtractPlanes();
	Halfspace ClassifyPoint(const vec4& plane, const vec4& vertex);
	unsigned int GenElementBuffer(unsigned int* buffer, int size);
	void BindIndexBuffer(unsigned int bufferId);
	void DrawElement(unsigned int size);
	bool Start(
		Window* window	// Actual window
	);
	bool Stop();
	void SetOrthoProjection(float auxA, float auxB, float auxC, float auxD, float auxE, float auxF);
	void SetCameraPosition(mat4 position);
	void SetCameraPosition(float x, float y, float z);
	void SetViewport(int pos);
	GLuint GetVerteArrayID()
	{
		return VertexArrayID;
	}
	void SetPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
	void SwitchProjection(ProjectionType projType);
	void SetViewMatrix(vec3 camPos, vec3 eyePos, vec3 headIsUpTo);
	void SetClearColor(
		float r,	// Red
		float g,	// Green
		float b,	// Blue
		float a		// Transparency
	);
	void ClearScreen();
	void SwapBuffers();
	void DestroyBuffer(
		unsigned int bufferId		// Buffer to destroy
	);

	unsigned int GenBuffer(
		void* buffer,				// Data to fill in the buffer
		int size					// Size of the data
	);

	unsigned int GenTexture(
		unsigned int width,			// Width of the image
		unsigned int height,		// Height of the image
		unsigned char* data			// Data of the file
		);

	unsigned int GenTexture2(unsigned int width, unsigned int height, unsigned char* data);

	unsigned int GenTilemapTexture(
		unsigned int width,			// Width of the image
		unsigned int height,		// Height of the image
		unsigned char* data			// Data of the file
	);

	void EnableAttributes(
		unsigned int attributeId	// Location to fill in
	);
	void BindBuffer(
		unsigned int bufferId,		// Buffer to use.
		unsigned int attributeId	// Location to fill in
	);
	void BindBuffer(
		unsigned int bufferId,   // Location to fill in
		unsigned int attributeId,   // Location to fill in
		int size,
		int corrimiento,
		int desfase
	);
	void BindBuffer(
		unsigned int attributeId,   // Location to fill in
		int size,
		int corrimiento,
		int desfase
	);
	void BindTextureBuffer(
		unsigned int bufferId,		// Buffer to use.
		unsigned int attributeId	// Location to fill in
		
	);
	void DrawBuffer(
		unsigned int attributeId,	// Location to fill in
		int size,					// Total of vertices to draw
		GLenum mode					// Draw mode
	);
	void DisableAttributes(
		unsigned int attributeId	// Location to fill in
	);

	void GenVArray(unsigned int VAO);
	void BindVArray(unsigned int vertex);

	void EnableBlend();
	void DisableBlend();

	void MoveCamera(
		glm::vec3 newPos			// Position added to the actual View Matrix position
	);

	void ResetCamera(
		float x,
		float y
	);

	void loadIdentityMatrix();
	void SetModelMatrix(
		glm::mat4 model				// Model matrix of the entity
	);
	void MultiplyModelMatrix(
		glm::mat4 model				// Model matrix of the entity
	);
	void SetMVP();
	glm::mat4 GetModelMatrix();
	glm::mat4& GetMVP();
	unsigned int GetWindowWidht()  { return window->GetWidth();  };
	unsigned int GetWindowHeight() { return window->GetHeight(); };
	glm::vec3 GetCameraPosition()  { return eyePosition;		 };

	Renderer();
	~Renderer();
};

