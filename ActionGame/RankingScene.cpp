#include "DXUT.h"
#include "RankingScene.h"

void RankingScene::Init()
{
	SoundManager::GetInstance().StopAll();
	obm.AddObject(new Ranking());
}

void RankingScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void RankingScene::Render()
{
	Scene::Render();
}
