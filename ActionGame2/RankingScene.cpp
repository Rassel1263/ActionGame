#include "DXUT.h"
#include "RankingScene.h"
#include "Rank.h"

void RankingScene::Init()
{
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Play(L"Ranking", true);

	Camera::GetInstance().destCameraPos = { 0, 0 };
	Camera::GetInstance().cameraPos = { 0, 0 };

	nowScene->obm.AddObject(new Rank());
}

void RankingScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void RankingScene::Render()
{
	Scene::Render();
}
