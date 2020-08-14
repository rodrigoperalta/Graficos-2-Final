#include "Game.h"




Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart()
{
	input = Input::getInstance();
	input->SetWindowContext(GetWindow());
	input->HideCursor();

	gameState = CONTINUE;
	matModel = new Material();
	matModel->LoadShader("Shaders\\TextureVertexShader.vertexshader"		// Vertex Shader
		, "Shaders\\TextureFragmentShader.fragmentshader"	// Fragment Shader
	);	
	matModel2 = new Material();
	matModel2->LoadShader("Shaders\\TextureVertexShader.vertexshader"		// Vertex Shader
		, "Shaders\\TextureFragmentShader.fragmentshader"	// Fragment Shader
	);	
	root = new SceneNode("root", GetRenderer());	
	SetScene(root);
	cameraComponent = new CameraC(GetRenderer());
	cameraCompnentNoFC = new CameraCNoFC(GetRenderer());
	root->AddComponent(cameraComponent);
	root->AddComponent(cameraCompnentNoFC);
	mesh1 = new SceneNode("Mesh1", root, GetRenderer());
	mesh1->ReturnTransform()->Teleport(0.0f, -10.0f, 70.0f);
	mesh2 = new SceneNode("Mesh2", root, GetRenderer());
	mesh2->ReturnTransform()->Teleport(0.0f, 0.0f, 70.0f);
	ourModel = new Model("nanosuit/nanosuit.obj", GetRenderer(), matModel, mesh1);
	ourModel2 = new Model("nave/E 45 Aircraft_obj.obj", GetRenderer(), matModel2,mesh2);
	root->AddChild(ourModel->GetParentNode());	
	root->AddChild(ourModel2->GetParentNode());

	return true;
}



bool Game::OnStop()
{	
	delete matModel;
	delete matModel2;	
	return true;
}




bool Game::OnUpdate()
{
	root->Update();
	
	switch (gameState)
	{
	case CONTINUE:
	{
		//Camera FC movement
		if (input->isInput(GLFW_KEY_W))
			cameraComponent->WalkFront(ADVANCE);	
		if (input->isInput(GLFW_KEY_S))
			cameraComponent->WalkFront(BACK);
		if (input->isInput(GLFW_KEY_A))
			cameraComponent->WalkSideWays(ADVANCE);
		if (input->isInput(GLFW_KEY_D))
			cameraComponent->WalkSideWays(BACK);
		if (input->isInput(GLFW_KEY_Q))
			cameraComponent->Rise(ADVANCE);
		if (input->isInput(GLFW_KEY_E))
			cameraComponent->Rise(BACK);

		//Camera noFC movement
		if (input->isInput(GLFW_KEY_KP_8))
			cameraCompnentNoFC->WalkFront(ADVANCE);
		if (input->isInput(GLFW_KEY_KP_5))
			cameraCompnentNoFC->WalkFront(BACK);
		if (input->isInput(GLFW_KEY_KP_4))
			cameraCompnentNoFC->WalkSideWays(ADVANCE);
		if (input->isInput(GLFW_KEY_KP_6))
			cameraCompnentNoFC->WalkSideWays(BACK);
		if (input->isInput(GLFW_KEY_KP_7))
			cameraCompnentNoFC->Rise(ADVANCE);
		if (input->isInput(GLFW_KEY_KP_9))
			cameraCompnentNoFC->Rise(BACK);
		
		if (input->isInput(GLFW_KEY_ESCAPE))
			return false;
		
		//Root Movement
		if (input->isInput(GLFW_KEY_RIGHT))
			root->ReturnTransform()->Translate(1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_LEFT))
			root->ReturnTransform()->Translate(-1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_UP))
			root->ReturnTransform()->Translate(0.0f, 1.0f, 0.0f);
		if (input->isInput(GLFW_KEY_DOWN))
			root->ReturnTransform()->Translate(0.0f, -1.0f, 0.0f);

		//Mesh 1 Movement
		if (input->isInput(GLFW_KEY_H))
			root->GetNode(0)->ReturnTransform()->Translate(-1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_F))
			root->GetNode(0)->ReturnTransform()->Translate(1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_T))
			root->GetNode(0)->ReturnTransform()->Translate(0.0f, 1.0f, 0.0f);
		if (input->isInput(GLFW_KEY_G))
			root->GetNode(0)->ReturnTransform()->Translate(0.0f, -1.0f, 0.0f);

		//Mesh 2 Movement
		if (input->isInput(GLFW_KEY_L))
			root->GetNode(1)->ReturnTransform()->Translate(1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_J))
			root->GetNode(1)->ReturnTransform()->Translate(-1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_I))
			root->GetNode(1)->ReturnTransform()->Translate(0.0f, 1.0f, 0.0f);
		if (input->isInput(GLFW_KEY_K))
			root->GetNode(1)->ReturnTransform()->Translate(0.0f, -1.0f, 0.0f);

		//Mesh 1 Node 7 Movement
		if (input->isInput(GLFW_KEY_R))
			mesh1->GetNode(6)->ReturnTransform()->Translate(1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_Y))
			mesh1->GetNode(6)->ReturnTransform()->Translate(-1.0f, 0.0f, 0.0f);

		//Mesh 1 Node 1 Movement
		if (input->isInput(GLFW_KEY_V))
			mesh1->GetNode(0)->ReturnTransform()->Translate(1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_N))
			mesh1->GetNode(0)->ReturnTransform()->Translate(-1.0f, 0.0f, 0.0f);

		//Mesh 2 Node 1 Movement
		if (input->isInput(GLFW_KEY_U))
			mesh2->GetNode(0)->ReturnTransform()->Translate(1.0f, 0.0f, 0.0f);
		if (input->isInput(GLFW_KEY_O))
			mesh2->GetNode(0)->ReturnTransform()->Translate(-1.0f, 0.0f, 0.0f);		

		GetRenderer()->SetPerspectiveProjection(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 1000.0f);
		GetRenderer()->SwitchProjection(Perspective);		
	}
	break;
	case WIN:
	{
	}
	break;
	case LOSE:
	{
	}
	break;
	}

	input->PollEvents();

	return true;
}

bool Game::OnDraw()
{		
	return true;
}

void Game::Restart()
{		
	gameState = CONTINUE;
}