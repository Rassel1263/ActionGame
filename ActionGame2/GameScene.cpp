#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	curStage = 1;
	nextScene = new GameScene2();

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

void GameScene::Update(float deltaTime)
{
	if(!stopTime) gameTime -= deltaTime;

	if(Input::GetInstance().KeyDown('G'))
		obm.AddObject(boss = new Boss1());

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
