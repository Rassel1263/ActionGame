#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	EnhanceData::GetInstance().Init();

	LoadFiles();
	SoundManager::GetInstance().Play(L"Main", true);

	score = 0.0f;
	nowScene->obm.AddObject(new Main());
}

void MainScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MainScene::Render()
{
	Scene::Render();
}
