#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, Renderer* renderer, Material* material) : Entity(renderer, material)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;	
}


void Mesh::setupMesh()
{	
	
}

void Mesh::Draw()
{	
	
}

void Mesh::ShouldDispose()
{

}

unsigned int Mesh::SetVertices(float* vertices, int count)
{
	return 0;
}