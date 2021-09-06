#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	obm.AddObject(new Map());
	obm.AddObject(player = new Player());
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