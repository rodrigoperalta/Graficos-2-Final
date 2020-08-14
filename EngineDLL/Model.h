#pragma once

#include "Mesh.h"
#include "Assimp\Importer.hpp"
#include "Assimp\scene.h"
#include "Assimp\postprocess.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "SceneNode.h"
#include "MeshRendererC.h"



unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class ENGINEDLL_API Model
{
public:
	Renderer* rendereraux;
	Material* materialaux;
	/*  Model Data  */	
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	SceneNode* parent;
	
	/*  Functions   */
	Model(const char *path, Renderer* renderer, Material* material, SceneNode* p);
	void Draw();
	SceneNode* GetParentNode();
	
private:
	/*  Functions   */
	void loadModel(string path);
	SceneNode processNode(aiNode *node, const aiScene *scene, SceneNode *parent);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene, SceneNode* parent, SceneNode* child);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		string typeName);
	
};
