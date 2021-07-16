#include "DXUT.h"
#include "GameScene2.h"

void GameScene2::Init()
{
	srand(time(NULL));

	stage = 2;

	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	obm.AddObject(new Background(stage));

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(200, 0), EnemyType::Power));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(800, 0), EnemyType::Speedy));
	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));

	obm.AddObject(new Boss(D3DXVECTOR2(-300, 0)));

	obm.AddObject(player = new Player());
	obm.AddObject(new PGaze(player));
	obm.AddObject(new UnitHp());
}

void GameScene2::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene2::Render()
{
	Scene::Render();
}
