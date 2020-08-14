#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "Input.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Asteroid.h"
#include "Model.h"
#include "SceneNode.h"
#include "CameraC.h"
#include "CameraCNoFC.h"


enum GameState
{
	LOSE = -1,
	CONTINUE,
	WIN
};

class Game : public GameBase
{
	Input* input;	
	Material* matModel;
	Material* matModel2;	
	//Camera* camera;
	Model* ourModel;
	Model* ourModel2;	
	GameState gameState;	
	void Restart();
	SceneNode* root;
	SceneNode* mesh1;
	SceneNode* mesh2;
	CameraC* cameraComponent;
	CameraCNoFC* cameraCompnentNoFC;
	MeshRendererC* mRC;

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	bool OnDraw() override;
	

public:
	Game();
	~Game();
};

