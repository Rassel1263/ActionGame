#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	Camera::GetInstance().cameraPos = { 0, 0 };
	Camera::GetInstance().destCameraPos = { 0, 0 };

	SoundManager::GetInstance().StopAll();

	EnhanceData::GetInstance().Init();
	LoadFiles();

	if (!TextureManager::GetInstance().textureLoad)
		nowScene->obm.AddObject(new LoadSprite());
	else
		nowScene->obm.AddObject(new Main());


	score = 0.0f;
}

void MainScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MainScene::Render()
{
	Scene::Render();
}
