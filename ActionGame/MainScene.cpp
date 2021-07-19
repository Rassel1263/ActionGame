#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	SoundManager::GetInstance().StopAll();

	Scene::Init();
	

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

void MainScene::LoadAll()
{
	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	//SoundManager::GetInstance().Create(L"Assets/Sound/LAttack.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/BGM/Main.mp3", 1);
	SoundManager::GetInstance().SetVolume(L"Assets/Sound/BGM/Main.mp3", 500);
	SoundManager::GetInstance().Play(L"Assets/Sound/BGM/Main.mp3", 1);
}
