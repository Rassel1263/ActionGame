#include "DXUT.h"
#include "GameScene3.h"

void GameScene3::Init()
{
	curStage = 3;
	nextScene = new RankingScene();

	Game::GetInstance().timeScale = 0.0f;
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);

	obm.AddObject(new Map());
	obm.AddObject(player = new Player());
	enemyManager.SpawnEnemy(D3DXVECTOR2(400, 0), 4);
}

void GameScene3::Update(float deltaTime)
{
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
