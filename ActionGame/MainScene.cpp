#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	Game::GetInstance().cameraPos = { 0, -360 };
	Game::GetInstance().destCameraPos = { 0, 0 };

	obm.AddObject(new MainBackground());
}

void MainScene::Update(float deltaTime)
{

	Scene::Update(deltaTime);
}

void MainScene::Render()
{
	Scene::Render();
}
