#include "DXUT.h"
#include "GameScene3.h"

void GameScene3::Init()
{
	stage = 3;
	nextScene = new RankingScene();

	wave = 5;

	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	obm.AddObject(new Background(stage));

	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));
	obm.AddObject(new Chest(D3DXVECTOR2(500, 100)));

	obm.AddObject(new Enemy(D3DXVECTOR2(-400, 0), EnemyType::Bind));
	obm.AddObject(new Enemy(D3DXVECTOR2(-350, 70), EnemyType::Power));
	obm.AddObject(new Enemy(D3DXVECTOR2(-380, -50), EnemyType::Power));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));

	obm.AddObject(new Enemy(D3DXVECTOR2(-100, -35), EnemyType::Bind));
	obm.AddObject(new Enemy(D3DXVECTOR2(100, 0), EnemyType::Range));
	obm.AddObject(new Enemy(D3DXVECTOR2(20, 50), EnemyType::Bind));

	obm.AddObject(new Enemy(D3DXVECTOR2(200, 50), EnemyType::Speedy));
	obm.AddObject(new Enemy(D3DXVECTOR2(240, 80), EnemyType::Speedy));
	obm.AddObject(new Enemy(D3DXVECTOR2(320, 0), EnemyType::Bind));
	obm.AddObject(new Enemy(D3DXVECTOR2(370, -70), EnemyType::Bind));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(200, 0), EnemyType::Range));
	obm.AddObject(new Enemy(D3DXVECTOR2(400, 10), EnemyType::Power));
	obm.AddObject(new Enemy(D3DXVECTOR2(450, -30), EnemyType::Power));


	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));

	obm.AddObject(player = new Player());
	obm.AddObject(new PGaze(player));
	obm.AddObject(new UnitHp());

	obm.AddObject(new Font(L"Timer", D3DXVECTOR2(-20, 150), D3DXVECTOR2(1, 1), 18, &timer));
	obm.AddObject(new Font(L"Timer", D3DXVECTOR2(-300, 110), D3DXVECTOR2(0.7, 0.7), 15, &score));


}

void GameScene3::Update(float deltaTime)
{
	if (player->pos.x >= 500 && !spawnBoss)
	{
		spawnBoss = true;
		player->limitLeft = player->pos.x;

		obm.AddObject(boss = new Boss2(D3DXVECTOR2(1000, 0)));
	}

	Scene::Update(deltaTime);
}

void GameScene3::Render()
{
	Scene::Render();
}

void GameScene3::LoadAll()
{
	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	SoundManager::GetInstance().Create(L"Assets/Sound/LAttack.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Dash.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/FireBall.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Explosion.mp3", 1);
}
