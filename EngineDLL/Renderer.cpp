#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::Start(Window* win)
{
	window = win;

	glfwMakeContextCurrent((GLFWwindow*)window->GetContext());
	
	

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return false;
	}

	// Habilidad el test de profundidad
	glEnable(GL_DEPTH_TEST);

	// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
	glDepthFunc(GL_LESS);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	projectionMatrix = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f, 0.0f, 100.0f);

	cameraPosition = glm::vec3(0, 0, 3);
	eyePosition = glm::vec3(0, 0, 0);
	headUpPosition = vec3(0, 1, 0);
	modelMatrix = projectionMatrix = mat4(1.0f);

	viewMatrix = glm::lookAt(
		cameraPosition,		// Camera is at (0, 0, 3), is World Space
		eyePosition,		// Looks at the origin
		headUpPosition  // Head is up to (0, 1, 0)
	);
	
	return true;
}

void Renderer::ResetCamera(float x, float y)
{
	vec3 newPos = vec3(x, y, 3);

	cameraPosition = vec3(newPos.x, newPos.y, newPos.z);
	eyePosition = vec3(0.0f, newPos.y, 0.0f);
	headUpPosition = vec3(0.0f, 1.0f, 0.0f);

	viewMatrix = glm::lookAt(
		cameraPosition,
		eyePosition,
		headUpPosition
	);

	SetMVP();
}

void Renderer::SetViewport(int pos)
{
	if (pos == 0)
		glViewport(0, 0, 1024, 768 * 0.5);
	if (pos == 1)
		glViewport(0, 768 * 0.5, 1024, 768 * 0.5);
}

void Renderer::SetCameraPosition(mat4 newPosition)
{
	viewMatrix = newPosition;
	

	SetMVP();
}

void Renderer::SetCameraPosition(float x, float y, float z)
{
	cameraPosition = vec3(x, y, z);

	viewMatrix = glm::lookAt(
		cameraPosition,
		eyePosition,
		headUpPosition
	);

	SetMVP();
}

vec4 Renderer::CreatePlane(const vec3& normal, const vec3& point)
{
	vec4 plane;

	plane.x = normal.x;
	plane.y = normal.y;
	plane.z = normal.z;
	plane.w = -dot(normal, point);

	return plane;
}

void Renderer::ExtractPlanes()
{
	glm::mat4 comboMatrix = projectionMatrix * glm::transpose(viewMatrix);

	// Left clipping plane
	planes[0].x = comboMatrix[0][3] + comboMatrix[0][3];
	planes[0].y = comboMatrix[1][3] + comboMatrix[1][3];
	planes[0].z = comboMatrix[2][3] + comboMatrix[2][3];
	planes[0].w = comboMatrix[3][3] + comboMatrix[3][3];

	// Right clipping plane
	planes[1].x = comboMatrix[0][3] - comboMatrix[0][3];
	planes[1].y = comboMatrix[1][3] - comboMatrix[1][3];
	planes[1].z = comboMatrix[2][3] - comboMatrix[2][3];
	planes[1].w = comboMatrix[3][3] - comboMatrix[3][3];

	// Top clipping plane
	planes[2].x = comboMatrix[0][3] - comboMatrix[0][3];
	planes[2].y = comboMatrix[1][3] - comboMatrix[1][3];
	planes[2].z = comboMatrix[2][3] - comboMatrix[2][3];
	planes[2].w = comboMatrix[3][3] - comboMatrix[3][3];

	// Bottom clipping plane
	planes[3].x = comboMatrix[0][3] + comboMatrix[0][3];
	planes[3].y = comboMatrix[1][3] + comboMatrix[1][3];
	planes[3].z = comboMatrix[2][3] + comboMatrix[2][3];
	planes[3].w = comboMatrix[3][3] + comboMatrix[3][3];

	// Near clipping plane
	planes[4].x = comboMatrix[0][3] + comboMatrix[0][3];
	planes[4].y = comboMatrix[1][3] + comboMatrix[1][3];
	planes[4].z = comboMatrix[2][3] + comboMatrix[2][3];
	planes[4].w = comboMatrix[3][3] + comboMatrix[3][3];

	// Far clipping plane
	planes[5].x = comboMatrix[0][3] - comboMatrix[0][3];
	planes[5].y = comboMatrix[1][3] - comboMatrix[1][3];
	planes[5].z = comboMatrix[2][3] - comboMatrix[2][3];
	planes[5].w = comboMatrix[3][3] - comboMatrix[3][3];
}

void Renderer::ExtractPlanes(vec3 globalPos, vec3 fwd, vec3 right, vec3 up, float zNear, float zFar, float aspRatio, float fovy)
{
	vec3 nearCenter = globalPos + fwd * zNear;
	vec3 farCenter = globalPos + fwd * zFar;

	float fovTan = tan(fovy);

	float nHeight = zNear * fovTan;
	float nWidth = nHeight * aspRatio;

	vec3 leftPlaneVec = (nearCenter - right * nWidth  * 0.5f) - globalPos;
	vec3 rightPlaneVec = (nearCenter + right * nWidth  * 0.5f) - globalPos;
	vec3 topPlaneVec = (nearCenter + up * nHeight * 0.5f) - globalPos;
	vec3 bottomPlaneVec = (nearCenter - up * nHeight * 0.5f) - globalPos;

	vec3 normalLeft = -normalize(cross(leftPlaneVec, up));
	vec3 normalRight = normalize(cross(rightPlaneVec, up));
	vec3 normalTop = -normalize(cross(topPlaneVec, right));
	vec3 normalBottom = normalize(cross(bottomPlaneVec, right));

	planes[(int)Planes::NEAR] = CreatePlane(fwd, nearCenter);
	planes[(int)Planes::FAR] = CreatePlane(-fwd, farCenter);
	planes[(int)Planes::LEFT] = CreatePlane(normalLeft, globalPos);
	planes[(int)Planes::RIGHT] = CreatePlane(normalRight, globalPos);
	planes[(int)Planes::TOP] = CreatePlane(normalTop, globalPos);
	planes[(int)Planes::BOTTOM] = CreatePlane(normalBottom, globalPos);
}

void Renderer::NormalizePlanes()
{
	for (int i = 0; i < 6; i++)
	{
		float mag;
		mag = sqrt(planes[i].x * planes[i].x + planes[i].y * planes[i].y + planes[i].z * planes[i].z);
		planes[i].x = planes[i].x / mag;
		planes[i].y = planes[i].y / mag;
		planes[i].z = planes[i].z / mag;
		planes[i].w = planes[i].w / mag;
	}

}

Halfspace Renderer::ClassifyPoint(const vec4& plane, const vec4& vertex)
{
	float distToPlane = plane.x * vertex.x + plane.y * vertex.y + plane.z * vertex.z + plane.w;

	return distToPlane >= 0.0f ? POSITIVE : NEGATIVE;
}

void Renderer::SetOrthoProjection(float auxA, float auxB, float auxC, float auxD, float auxE, float auxF)
{
	auxOrthoMatrix = glm::ortho(auxA, auxB, auxC, auxD, auxE, auxF);
}

void Renderer::SetPerspectiveProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	auxPerspectiveMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

	SetMVP();
}

void Renderer::SwitchProjection(ProjectionType projType)
{
	if (projType == Ortho)
		projectionMatrix = auxOrthoMatrix;
	if (projType == Perspective)
		projectionMatrix = auxPerspectiveMatrix;

	SetMVP();
}

void Renderer::SetViewMatrix(vec3 camPos, vec3 eyePos, vec3 headIsUpTo)
{
	viewMatrix = glm::lookAt(camPos, eyePos, headIsUpTo);
	SetMVP();
}

bool Renderer::Stop()
{
	return true;
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::SwapBuffers()
{
	glfwSwapBuffers((GLFWwindow*)window->GetContext());
}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DestroyBuffer(unsigned int bufferId)
{
	glDeleteBuffers(1, &bufferId);
}

unsigned int Renderer::GenBuffer(void* buffer, int size)
{
	// Identificar el vertex buffer
	unsigned int vertexbuffer;
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &vertexbuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

	return vertexbuffer;
}

unsigned int Renderer::GenElementBuffer(unsigned int* buffer, int size)
{

	unsigned int indexbuffer;
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size,
		&buffer[0], GL_STATIC_DRAW);

	return indexbuffer;

}

unsigned int Renderer::GenTexture(unsigned int width, unsigned int height, unsigned char* data)
{
	// Identificar el vertex buffer
	unsigned int vertexbuffer;
	glGenTextures(1, &vertexbuffer);

	// Se "Ata" la nueva textura : Todas las futuras funciones de texturas van a modificar esta textura
	glBindTexture(GL_TEXTURE_2D, vertexbuffer);

	// Se le pasa la imagen a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return vertexbuffer;
}

unsigned int Renderer::GenTexture2(unsigned int width, unsigned int height, unsigned char* data)
{
	// Identificar el vertex buffer
	unsigned int vertexbuffer;
	glGenTextures(1, &vertexbuffer);

	// Se "Ata" la nueva textura : Todas las futuras funciones de texturas van a modificar esta textura
	glBindTexture(GL_TEXTURE_2D, vertexbuffer);

	// Se le pasa la imagen a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return vertexbuffer;
}

unsigned int Renderer::GenTilemapTexture(unsigned int width, unsigned int height, unsigned char* data)
{
	unsigned int vertexbuffer;

	glGenTextures(1, &vertexbuffer);

	glBindTexture(GL_TEXTURE_2D, vertexbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return vertexbuffer;
}

void Renderer::EnableAttributes(unsigned int attributebId)
{
	glEnableVertexAttribArray(attributebId);
}

void Renderer::BindBuffer(unsigned int bufferId, unsigned int attributebId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glVertexAttribPointer(
		attributebId,       // debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                  // corrimiento
		(void*)0            // desfase del buffer
	);
}

void Renderer::BindBuffer(unsigned int bufferId, unsigned int attributebId, int size, int corrimiento, int desfase)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glVertexAttribPointer(
		attributebId,       // debe corresponder en el shader.
		size,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		corrimiento,                  // corrimiento
		(void*)desfase           // desfase del buffer
	);
}

void Renderer::BindBuffer(unsigned int attributebId, int size, int corrimiento, int desfase)
{
	glVertexAttribPointer(
		attributebId,       // debe corresponder en el shader.
		size,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		corrimiento,                  // corrimiento
		(void*)desfase           // desfase del buffer
	);
}

void Renderer::GenVArray(unsigned int VAO)
{
	glGenVertexArrays(1, &VAO);
}

void Renderer::BindVArray(unsigned int vertex)
{
	glBindVertexArray(vertex);
}



void Renderer::BindTextureBuffer(unsigned int bufferId, unsigned int attributebId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glVertexAttribPointer(
		attributebId,       // debe corresponder en el shader.
		2,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                  // corrimiento
		(void*)0            // desfase del buffer
	);
}

void Renderer::BindIndexBuffer(unsigned int bufferId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void Renderer::DrawElement(unsigned int size)
{
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}

void Renderer::DrawBuffer(unsigned int attributeId, int size, GLenum mode)
{
	glDrawArrays(mode, 0, size);
}

void Renderer::DisableAttributes(unsigned int attributeId)
{
	glDisableVertexAttribArray(attributeId);
}

void Renderer::EnableBlend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DisableBlend()
{
	glDisable(GL_BLEND);
}

void Renderer::MoveCamera(glm::vec3 newPos)
{
	cameraPosition += glm::vec3(newPos.x, newPos.y, 0);
	eyePosition += newPos;

	viewMatrix = glm::lookAt(
		cameraPosition,
		eyePosition,
		glm::vec3(0, 1, 0)  // Head is up to (0, 1, 0)
	);
}

void Renderer::loadIdentityMatrix()
{
	modelMatrix = glm::mat4(1.0f);

	SetMVP();
}

void Renderer::SetModelMatrix(glm::mat4 model)
{
	modelMatrix = model;

	SetMVP();
}


void Renderer::MultiplyModelMatrix(glm::mat4 model)
{
	modelMatrix *= model;

	SetMVP();
}

void Renderer::SetMVP()
{
	MVP = projectionMatrix * viewMatrix * modelMatrix;
}

glm::mat4& Renderer::GetMVP()
{
	return MVP;
}

glm::mat4 Renderer::GetModelMatrix()
{
	return modelMatrix;
}