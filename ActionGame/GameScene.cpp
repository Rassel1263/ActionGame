#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	obm.AddObject(new Enemy(D3DXVECTOR2(900, -200), EnemyType::Speedy));
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
