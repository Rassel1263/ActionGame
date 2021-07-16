#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	srand(time(NULL));

	stage = 1;
	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	obm.AddObject(new Background(stage));

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(200, 0), EnemyType::Power));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(600, 0), EnemyType::Speedy));

	obm.AddObject(new Enemy(D3DXVECTOR2(-400, 0), EnemyType::Bind));
	obm.AddObject(new Enemy(D3DXVECTOR2(500, 0), EnemyType::Bind));

	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));
	obm.AddObject(new Chest(D3DXVECTOR2(500, 100)));
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
