#include "DXUT.h"
#include "Scene.h"

float Scene::score = 0.0f;

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{
	if (destScore > 0.0f)
	{
		float tempScore = destScore;
		destScore -= 1000 * deltaTime;
		score += tempScore - destScore;
	}


	if (curStage > 0)
	{
		if (Input::GetInstance().KeyDown(VK_F1))
			player->invincible = !player->invincible;

		if (Input::GetInstance().KeyDown(VK_F2))
			player->PlusMp(player->maxMp);

		if (Input::GetInstance().KeyDown(VK_F3))
		{
			for (auto& enemy : enemyManager.enemyVec)
			{
				if (enemy->pos.x > Camera::GetInstance().cameraPos.x - 960 &&
					enemy->pos.x < Camera::GetInstance().cameraPos.x + 960)

					enemy->Hit(enemy->ability.maxHp, D3DXVECTOR2(0, 0));
			}
		}
	}

	if (Input::GetInstance().KeyDown(VK_F4))
		Game::GetInstance().ChangeScene(new MainScene());
	if (Input::GetInstance().KeyDown(VK_F5))
		Game::GetInstance().ChangeScene(new GameScene());
	if (Input::GetInstance().KeyDown(VK_F6))
		Game::GetInstance().ChangeScene(new GameScene2());
	if (Input::GetInstance().KeyDown(VK_F7))
		Game::GetInstance().ChangeScene(new GameScene3());

	if (Input::GetInstance().KeyDown(VK_F11))
		Game::GetInstance().ChangeScene(new RankingScene());

	obm.Collision();
	obm.Update(deltaTime);
}

void Scene::Render()
{
	obm.Render();
}

void Scene::UIRender()
{
	obm.UIRender();
}

void Scene::LoadFiles()
{
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);
	ShaderManager::GetInstance().CreateEffect("Outline", L"Assets/Shader/OutlineShader.fx", 1);

	// Player
	SoundManager::GetInstance().Create(L"basicShoot", L"Assets/Sound/Player/Bullet/basic.mp3", 1);

	// BGM
	SoundManager::GetInstance().Create(L"Main", L"Assets/Sound/BGM/main.wav", 1);
	SoundManager::GetInstance().Create(L"Stage1", L"Assets/Sound/BGM/stage1.wav", 1);
	SoundManager::GetInstance().Create(L"Stage2", L"Assets/Sound/BGM/stage2-2.wav", 1);
	SoundManager::GetInstance().Create(L"Stage3", L"Assets/Sound/BGM/stage3.wav", 1);
	SoundManager::GetInstance().Create(L"Ranking", L"Assets/Sound/BGM/Ranking.wav", 1);
}

int Scene::GetRandomNum(int min, int max)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> dis(min, max);

	return dis(rnd);
}

D3DXVECTOR2 Scene::GetRandomVector(int xMin, int xMax, int yMin, int yMax)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> x(xMin, xMax);
	std::uniform_int_distribution<int> y(yMin, yMax);
	return D3DXVECTOR2(x(rnd), y(rnd));
}

void Scene::AddScore(float value)
{
	destScore = value;
}

