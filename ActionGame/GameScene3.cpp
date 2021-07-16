#include "DXUT.h"
#include "GameScene3.h"

void GameScene3::Init()
{
	srand(time(NULL));

	stage = 2;

	obm.AddObject(new Background(stage));

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(200, 0), EnemyType::Power));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(800, 0), EnemyType::Speedy));
	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));
	obm.AddObject(player = new Player());
	obm.AddObject(new PGaze(player));
	obm.AddObject(new UnitHp());
}

void GameScene3::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene3::Render()
{
	Scene::Render();
}
