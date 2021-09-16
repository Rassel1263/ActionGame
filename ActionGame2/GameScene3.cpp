#include "DXUT.h"
#include "GameScene3.h"

void GameScene3::Init()
{
	curStage = 3;
	nextScene = new RankingScene();

	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);
	ShaderManager::GetInstance().CreateEffect("Outline", L"Assets/Shader/OutlineShader.fx", 1);

	nowScene->obm.AddObject(new Font<float>(L"Score/", score, D3DXVECTOR2(800, 500), D3DXVECTOR2(1, 1), 30, 3, 1));
	nowScene->obm.AddObject(new Font<float>(L"Time/", gameTime, D3DXVECTOR2(0, 500), D3DXVECTOR2(1, 1), 50, 0, 1));

	Camera::GetInstance().destCameraScale = { 1.0f, 1.0f };

	for (int i = 0; i < 8; ++i)
		nowScene->obm.AddObject(new Box(D3DXVECTOR2(700 + 1500 * i, nowScene->GetRandomNum(-400, -50))));

	obm.AddObject(new Map(5));
	obm.AddObject(player = new Player());

	enemyManager.SetEnemyPos(curStage);

	nowScene->obm.AddObject(new StageFont(StageFont::Type::START));
}

void GameScene3::Update(float deltaTime)
{
	enemyManager.SpawnEnemy();

	if (!stopTime)
		gameTime -= deltaTime;

	if (gameTime <= 0.0f && !timeOver)
	{
		timeOver = true;
		nowScene->obm.AddObject(new StageFont(StageFont::Type::FAIL));
	}

	if (player->pos.x > 16000 && !spawnBoss)
		obm.AddObject(boss = new Boss2());

	Scene::Update(deltaTime);
}

void GameScene3::Render()
{
	Scene::Render();
}

void GameScene3::UIRender()
{
	Scene::UIRender();
}
