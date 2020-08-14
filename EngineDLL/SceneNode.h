#pragma once
#include "Mesh.h"
#include "Transform.h"
#include <vector>
#include "BoundigBox.h"

class ENGINEDLL_API SceneNode	{
protected:	
	Renderer* renderer;
	std::vector <SceneNode*> nodes;
	std::vector <Component*> components;
	std::string name;
	SceneNode* parent;
	bool shouldDraw;
public:
	BoundingBox bb;
	SceneNode(Renderer* r);
	SceneNode(string n, Renderer* r);
	SceneNode(string n, SceneNode* p, Renderer* r);
	Transform* transform;
	~SceneNode(void);
	void AddChild(SceneNode* s);
	void RemoveChild(SceneNode* s);
	void AddComponent(Component* c);
	void RemoveComponent(Component* c);	
	void Update();
	void Draw();
	void CheckPlanes();
	string GetName(){ return name; }
	string GetParent();
	SceneNode* GetNode(unsigned int i);
	void SetParent(SceneNode* p) { parent = p; }
	Transform* ReturnTransform() {return transform;}
};

