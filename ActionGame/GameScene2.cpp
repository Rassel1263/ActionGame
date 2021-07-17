#include "DXUT.h"
#include "GameScene2.h"

void GameScene2::Init()
{
	srand(time(NULL));

	stage = 2;

	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	obm.AddObject(new Background(stage));

	//obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));
	//obm.AddObject(new EnemySpawner(D3DXVECTOR2(200, 0), EnemyType::Power));
	//obm.AddObject(new EnemySpawner(D3DXVECTOR2(600, 0), EnemyType::Speedy));
	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));

	//obm.AddObject(new Boss(D3DXVECTOR2(-300, 0)));

	timer = 180;

	obm.AddObject(player = new Player());
	obm.AddObject(new PGaze(player));
	obm.AddObject(new UnitHp());
	obm.AddObject(new Font(L"Timer", D3DXVECTOR2(0, 100), &timer));
}

void GameScene2::Update(float deltaTime)
{
	if (player->pos.x >= 500 && !spawnBoss)
	{
		spawnBoss = true;
		player->limitLeft = player->pos.x;

		obm.AddObject(new Boss(D3DXVECTOR2(1000, 0)));
	}

	timer -= deltaTime * 10;

	Scene::Update(deltaTime);
}

void GameScene2::Render()
{
	Scene::Render();
}
