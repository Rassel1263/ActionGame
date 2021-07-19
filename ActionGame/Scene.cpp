#include "DXUT.h"
#include "Scene.h"

float Scene::score = 0.0f;

void Scene::Init()
{
	LoadAll();
}

void Scene::Update(float deltaTime)
{
	timer -= deltaTime;

	if (Input::GetInstance().KeyDown(VK_F1))
		nowScene->player->invincibility = !nowScene->player->invincibility;

	if (Input::GetInstance().KeyDown(VK_F2))
		nowScene->player->PlusSpecialGaze(100);

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

	if (timer <= 0.0f)
	{
		timer = 999.0f;
		obm.AddObject(new DiePage());
	}

	obm.Collision();
	obm.Update(deltaTime);
}

void Scene::Render()
{
	obm.Render();
}

void Scene::LoadAll()
{

}

void Scene::GetScore(int score)
{
	this->score += score;
}
