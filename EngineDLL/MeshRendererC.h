#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "BoundigBox.h"

class ENGINEDLL_API MeshRendererC : public Component
{
public:
	Mesh* mesh;
	Material* material;
	Renderer* renderer;
	MeshRendererC();
	void setMesh(Mesh* m, Renderer* rend);
	void setMat(Material* ma);
	void Start() override;
	void Update() override;
	void Draw() override;
	//void DrawFCData(const BoundingBox& fcData);

private:
	unsigned int VAO, VBO, EBO;
};