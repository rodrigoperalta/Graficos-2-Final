#include "MeshRendererC.h"

MeshRendererC::MeshRendererC()
{

}

void MeshRendererC::setMesh(Mesh* m, Renderer* rend)
{		
	name = "Mesh Renderer Component";	
	mesh = new Mesh(m->GetVertices(),m->GetIndices(), m->GetTextures(), m->GetRenderer(), m->GetMaterial());
	renderer = rend;
	VBO = renderer->GenBuffer(&mesh->vertices[0], mesh->vertices.size() * sizeof(Vertex));
	EBO = renderer->GenElementBuffer(&mesh->indices[0], mesh->indices.size() * sizeof(unsigned int));
}

void MeshRendererC::setMat(Material* ma)
{
	material = ma;
}

void MeshRendererC::Start()
{

}
void MeshRendererC::Update()
{

}
void MeshRendererC::Draw()
{
	if (material != NULL)
	{
		material->Bind();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
	}

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < mesh->textures.size(); i++)
	{
		// retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = mesh->textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream

												 // now set the sampler to the correct texture unit
		material->Bind((name + number).c_str(), mesh->textures[i].id, i);

	}

	// draw mesh	
	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->BindBuffer(VBO, 0, 3, sizeof(Vertex), 0);
	renderer->BindBuffer(1, 2, sizeof(Vertex), offsetof(Vertex, TexCoords));
	renderer->BindIndexBuffer(EBO);
	renderer->DrawElement(mesh->indices.size());
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);

	// always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < this->mesh->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}


