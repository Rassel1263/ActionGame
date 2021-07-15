#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	srand(time(NULL));

	obm.AddObject(new Background());
	obm.AddObject(new Enemy(D3DXVECTOR2(900, 0), EnemyType::Speedy));
	obm.AddObject(new Enemy(D3DXVECTOR2(500, 0), EnemyType::Power));
	obm.AddObject(new Enemy(D3DXVECTOR2(600, 0), EnemyType::Bind));
	obm.AddObject(player = new Player());
	obm.AddObject(new PGaze(player));
	obm.AddObject(new UnitHp());
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
