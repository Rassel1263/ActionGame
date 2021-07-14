#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	srand(time(NULL));

	//obm.AddObject(new Enemy(D3DXVECTOR2(900, -200), EnemyType::Speedy));
	//obm.AddObject(new Enemy(D3DXVECTOR2(500, -200), EnemyType::Power));
	obm.AddObject(new Enemy(D3DXVECTOR2(600, -200), EnemyType::Bind));
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
