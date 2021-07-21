#include "DXUT.h"
#include "GameScene2.h"

void GameScene2::Init()
{
	stage = 2;
	nextScene = new GameScene3();

	wave = 3;

	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	obm.AddObject(new Background(stage));

	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));
	obm.AddObject(new Chest(D3DXVECTOR2(500, 100)));

	obm.AddObject(new Enemy(D3DXVECTOR2(-400, 50), EnemyType::Speedy));
	obm.AddObject(new Enemy(D3DXVECTOR2(-280, 0), EnemyType::Speedy));
	obm.AddObject(new Enemy(D3DXVECTOR2(-430, -30), EnemyType::Power));
	obm.AddObject(new Enemy(D3DXVECTOR2(-350, -30), EnemyType::Bind));

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));

	obm.AddObject(new Enemy(D3DXVECTOR2(100, 10), EnemyType::Bind));
	obm.AddObject(new Enemy(D3DXVECTOR2(120, -20), EnemyType::Power));
	obm.AddObject(new Enemy(D3DXVECTOR2(200, 10), EnemyType::Range));

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(200, 0), EnemyType::Power));

	obm.AddObject(player = new Player());
	obm.AddObject(new PGaze(player));
	obm.AddObject(new UnitHp());

	obm.AddObject(new Font(L"Timer", D3DXVECTOR2(-20, 150), D3DXVECTOR2(1, 1), 18, &timer));
	obm.AddObject(new Font(L"Timer", D3DXVECTOR2(-300, 110), D3DXVECTOR2(0.7, 0.7), 15, &score));

	obm.AddObject(new Fade(stage));
}

void GameScene2::Update(float deltaTime)
{
	if (player->pos.x >= 500 && !spawnBoss)
	{
		spawnBoss = true;
		player->limitLeft = player->pos.x;

		obm.AddObject(boss = new Boss(D3DXVECTOR2(1000, 0)));
	}

	Scene::Update(deltaTime);
}

void GameScene2::Render()
{
	Scene::Render();
}

void GameScene2::LoadAll()
{
	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	SoundManager::GetInstance().Create(L"Assets/Sound/LAttack.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Dash.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/FireBall.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Explosion.mp3", 1);
}
