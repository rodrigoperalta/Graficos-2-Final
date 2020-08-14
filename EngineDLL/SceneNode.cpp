#include "SceneNode.h"

SceneNode::SceneNode(Renderer* r)
{
	bb = BoundingBox();
	renderer = r;
	transform = new Transform();
	AddComponent(transform);
	shouldDraw = true;
}

SceneNode::SceneNode(string n, Renderer* r)
{
	bb = BoundingBox();
	name = n;
	renderer = r;
	transform = new Transform();
	AddComponent(transform);
	shouldDraw = true;
}

SceneNode::SceneNode(string n, SceneNode* p, Renderer* r)
{
	bb = BoundingBox();
	name = n;
	renderer = r;
	parent = p;
	transform = new Transform();
	AddComponent(transform);
	shouldDraw = true;
}

SceneNode ::~SceneNode(void)
{
}



void SceneNode::AddChild(SceneNode * s)
{
	nodes.push_back(s);
	cout << "I added child: " << s->name << "with parent: " << s->GetParent() << endl;	
}

string SceneNode::GetParent()
{
	if (parent != NULL)
		return parent->GetName();
	else
		return "This node is root";

}

void SceneNode::CheckPlanes()
{
	if (bb.initialized)
	{
		vec4* planes = renderer->GetPlanes();

		for (int i = 0; i < 6; i++)
		{
			bool allBehind = true;

			for (int j = 0; j < 8; j++)
			{
				if (renderer->ClassifyPoint(planes[i], renderer->GetModelMatrix() * vec4(bb.vertex[j], 1.0f)) == POSITIVE)
				{
					allBehind = false;
					break;
				}
			}
			if (allBehind)
			{
				shouldDraw = false;
			}
		}
	}
}

void SceneNode::Draw()
{

	mat4 currentModelMatrix = renderer->GetModelMatrix();
	renderer->MultiplyModelMatrix(transform->GetModelMatrix());

	CheckPlanes();

	if (shouldDraw)
	{
		for (int i = 0; i < components.size(); i++)
			components[i]->Draw();

		for (unsigned int i = 0; i < nodes.size(); i++)
			nodes[i]->Draw();
	}


	if (bb.initialized)
	{
		bb.UpdateData();
		if (shouldDraw)
			cout << name << " on" << endl;
		else
			cout << name << " off" << endl;		
	}	
	shouldDraw = true;

	renderer->SetModelMatrix(currentModelMatrix);

}

void SceneNode::RemoveChild(SceneNode* s)
{

}
void SceneNode::AddComponent(Component* c)
{
	components.push_back(c);
}
void SceneNode::RemoveComponent(Component* c)
{

}

void SceneNode::Update() {
	for (int i = 0; i < components.size(); i++)
		components[i]->Update();

	for (int i = 0; i < nodes.size(); i++)
		nodes[i]->Update();
}

SceneNode* SceneNode::GetNode(unsigned int i)
{
	if (i < nodes.size())
	{
		cout << "Returning node name: " << nodes[i]->GetName() << endl;
		return nodes[i];
	}
	else
	{
		cout << "Node doesnt exist" << endl;
		return false;
	}

}




