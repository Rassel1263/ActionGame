#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	Game::GetInstance().timeScale = 0.0f;
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);

	obm.AddObject(new Map());
	obm.AddObject(player = new Player());
	obm.AddObject(new Enemy1(D3DXVECTOR2(400, 0)));
	obm.AddObject(new Enemy2(D3DXVECTOR2(800, 0)));
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::UIRender()
{
	Scene::UIRender();
}
