#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	curStage = 1;
	nextScene = new GameScene2();
	SoundManager::GetInstance().StopAll();

	LoadFiles();
	SoundManager::GetInstance().Play(L"Stage1", true);

	nowScene->obm.AddObject(new Font<float>(L"Score/", score, D3DXVECTOR2(800, 500), D3DXVECTOR2(1, 1), 30, 3, 1));
	nowScene->obm.AddObject(new Font<float>(L"Time/", gameTime, D3DXVECTOR2(0, 500), D3DXVECTOR2(1, 1), 50, 0, 1));

	Camera::GetInstance().destCameraScale = { 1.0f, 1.0f };

	for (int i = 0; i < 8; ++i)
		nowScene->obm.AddObject(new Box(D3DXVECTOR2(700 + 1500 * i, nowScene->GetRandomNum(-300, 200))));

	obm.AddObject(new Map(7));
	obm.AddObject(player = new Player());

	enemyManager.SetEnemyPos(curStage);

	nowScene->obm.AddObject(new StageFont(StageFont::Type::START));
}

void GameScene::Update(float deltaTime)
{
	enemyManager.SpawnEnemy();
	if(!stopTime) 
		gameTime -= deltaTime;

	if (gameTime <= 0.0f && !timeOver)
	{
		timeOver = true;
		nowScene->obm.AddObject(new StageFont(StageFont::Type::FAIL));
	}

	if (nowScene->player->pos.x > 15000 && !spawnBoss)
	{
		spawnBoss = true;
		nowScene->obm.AddObject(new CalcPage());
	}


	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::UIRender()
{
	Scene::UIRender();
}
