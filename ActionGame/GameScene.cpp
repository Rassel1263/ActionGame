#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	Scene::Init();

	srand(time(NULL));
	stage = 1;
	nextScene = new GameScene2();

	obm.AddObject(new Background(stage));

	obm.AddObject(new Chest(D3DXVECTOR2(-700, 100)));
	obm.AddObject(new Chest(D3DXVECTOR2(500, 100)));

	obm.AddObject(new Enemy(D3DXVECTOR2(-400, -40), EnemyType::Speedy));
	obm.AddObject(new Enemy(D3DXVECTOR2(-300,  0), EnemyType::Power));

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(-300, 0), EnemyType::Speedy));

	obm.AddObject(new Enemy(D3DXVECTOR2(-100, -33), EnemyType::Power));
	obm.AddObject(new Enemy(D3DXVECTOR2(0, 50), EnemyType::Power));
	obm.AddObject(new Enemy(D3DXVECTOR2(120, 20), EnemyType::Speedy));

	obm.AddObject(new EnemySpawner(D3DXVECTOR2(200, 0), EnemyType::Power));
	obm.AddObject(new EnemySpawner(D3DXVECTOR2(600, 0), EnemyType::Speedy));




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

void GameScene::LoadAll()
{
	ShaderManager::GetInstance().CreateEffect("Simple", L"Assets/Shader/SimpleShader.fx", 0);

	SoundManager::GetInstance().Create(L"Assets/Sound/BGM/Game.mp3", 1);
	SoundManager::GetInstance().Play(L"Assets/Sound/BGM/Game.mp3", true);

	SoundManager::GetInstance().Create(L"Assets/Sound/LAttack.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Dash.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/FireBall.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Explosion.mp3", 1);
}
