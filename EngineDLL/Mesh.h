#pragma once

#include "Entity.h"
#include "TextureImporter.h"

/*struct Vertex {
	glm::vec3 Position;
};*/
struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};


struct Texture {
	unsigned int id;
	string type;
	string path;
};


class ENGINEDLL_API Mesh : public Entity
{
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	/*  Functions  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Renderer* renderer, Material* material);
	vector<Vertex> GetVertices() { return vertices; }
	vector<unsigned int> GetIndices() { return indices; }
	vector<Texture> GetTextures() { return textures; }
	Renderer* GetRenderer() { return renderer; }
	Material* GetMaterial() { return material; }

	void Draw() override;
	void ShouldDispose() override;
	unsigned int SetVertices(float* vertices, int count) override;

private:
	/*  Render data  */
	unsigned int VAO, VBO, EBO;
	/*  Functions    */
	void setupMesh();

};