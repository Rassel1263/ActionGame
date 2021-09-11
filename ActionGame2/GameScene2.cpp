#include "DXUT.h"
#include "GameScene2.h"

void GameScene2::Init()
{
	curStage = 2;

	Game::GetInstance().timeScale = 0.0f;
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);

	obm.AddObject(new Map());
	obm.AddObject(player = new Player());
	enemyManager.SpawnEnemy(D3DXVECTOR2(400, 0), 4);
}

void GameScene2::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene2::Render()
{
	Scene::Render();
}

void GameScene2::UIRender()
{
	Scene::UIRender();
}
