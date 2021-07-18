#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	srand(time(NULL));
	stage = 1;
	nextScene = new GameScene2();
	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	obm.AddObject(new Background(stage));

	Enemy* enemy = NULL;

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(200, 0), EnemyType::Power));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(600, 0), EnemyType::Speedy));

	obm.AddObject(enemy = new Enemy(D3DXVECTOR2(-400, 0), EnemyType::Range));
	enemyVecs.push_back(enemy);
	obm.AddObject(enemy = new Enemy(D3DXVECTOR2(500, 0), EnemyType::Bind));
	enemyVecs.push_back(enemy);

	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));
	obm.AddObject(new Chest(D3DXVECTOR2(500, 100)));
	obm.AddObject(player = new Player());
	obm.AddObject(new PGaze(player));
	obm.AddObject(new UnitHp());

	obm.AddObject(new Font(L"Timer", D3DXVECTOR2(-20, 150), D3DXVECTOR2(1, 1), 18, &timer));
	obm.AddObject(new Font(L"Timer", D3DXVECTOR2(-300, 110), D3DXVECTOR2(0.7, 0.7), 15, &score));

	obm.AddObject(new Fade(stage));
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
