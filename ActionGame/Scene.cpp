#include "DXUT.h"
#include "Scene.h"

float Scene::score = 0.0f;

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{
	timer -= deltaTime;

	if (Input::GetInstance().KeyDown(VK_F1))
		nowScene->player->invincibility = !nowScene->player->invincibility;

	if (Input::GetInstance().KeyDown(VK_F2))
		nowScene->player->PlusSpecialGaze(100);

	if (Input::GetInstance().KeyDown(VK_F2))
	{
		for (auto& enemy : enemyVecs)
		{
			if (enemy->pos.x > Game::GetInstance().destCameraPos.x - 360 && enemy->pos.x < Game::GetInstance().destCameraPos.x + 360)
			{
				enemy->bHit = true;
				enemy->damage = enemy->ability.maxHp;
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

	if (Input::GetInstance().KeyDown(VK_F8))
		gameStop = !gameStop;

	(gameStop) ? Game::GetInstance().timeScale = 0.0f : Game::GetInstance().timeScale = 1.0f;

	obm.Collision();
	obm.Update(deltaTime);
}

void Scene::Render()
{
	obm.Render();
}

void Scene::GetScore(int score)
{
	this->score += score;
}
