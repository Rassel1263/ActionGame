#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	obm.AddObject(new Map());
	obm.AddObject(player = new Player());
	obm.AddObject(new Enemy1(D3DXVECTOR2(400, 0)));

	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);
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
