#include "DXUT.h"
#include "GameScene2.h"

void GameScene2::Init()
{
	curStage = 2;
	nextScene = new GameScene3();

	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);
	ShaderManager::GetInstance().CreateEffect("Outline", L"Assets/Shader/OutlineShader.fx", 1);

	nowScene->obm.AddObject(new Font<float>(L"Score/", score, D3DXVECTOR2(800, 500), D3DXVECTOR2(1, 1), 30, 3, 1));
	nowScene->obm.AddObject(new Font<float>(L"Time/", gameTime, D3DXVECTOR2(0, 500), D3DXVECTOR2(1, 1), 50, 0, 1));

	Camera::GetInstance().destCameraScale = { 1.0f, 1.0f };

	obm.AddObject(new Map());
	obm.AddObject(player = new Player());
	enemyManager.SpawnEnemy(D3DXVECTOR2(400, 0), 4);
	obm.AddObject(new Box(D3DXVECTOR2(200, 0)));
	nowScene->obm.AddObject(new StageFont(StageFont::Type::START));
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
