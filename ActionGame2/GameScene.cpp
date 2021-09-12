#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	curStage = 1;

	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);

	nowScene->obm.AddObject(new Font<float>(L"Score/", score, D3DXVECTOR2(800, 500), D3DXVECTOR2(1, 1), 30, 3, 1));
	nowScene->obm.AddObject(new Font<float>(L"Time/", gameTime, D3DXVECTOR2(0, 500), D3DXVECTOR2(1, 1), 50, 0, 1));

	//Camera::GetInstance().destDivideProj = 2.0f;
	Camera::GetInstance().destCameraScale = { 1.0f, 1.0f };

	obm.AddObject(new Map());
	obm.AddObject(player = new Player());
	enemyManager.SpawnEnemy(D3DXVECTOR2(400, 0), 4);
	enemyManager.SpawnEnemy(D3DXVECTOR2(400, 0), 2);
	/*obm.AddObject(enemy = new Enemy1(D3DXVECTOR2(800, 0)));
	enemyVec.push_back(enemy);
	obm.AddObject(enemy = new Enemy1(D3DXVECTOR2(500, 0)));
	enemyVec.push_back(enemy);
	obm.AddObject(enemy = new Enemy1(D3DXVECTOR2(400, -200)));
	enemyVec.push_back(enemy);
	obm.AddObject(enemy = new Enemy1(D3DXVECTOR2(400, 300)));
	enemyVec.push_back(enemy);*/


	/*obm.AddObject(new Enemy2(D3DXVECTOR2(800, 0)));
	obm.AddObject(new Enemy3(D3DXVECTOR2(1200, 0)));
	obm.AddObject(new Enemy4(D3DXVECTOR2(500, 0)));*/
}

void GameScene::Update(float deltaTime)
{
	gameTime -= deltaTime;

	if(Input::GetInstance().KeyDown('G'))
		obm.AddObject(boss = new Boss1());

	if (Input::GetInstance().KeyDown('H'))
		obm.AddObject(new Warning(L"Warning", D3DXVECTOR2(0, 0), D3DXVECTOR2(-1, 1), D3DXVECTOR2(0, 0.5), 2.0f));

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
