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

	
	///////////////////////////////////
	/// Player
	///////////////////////////////////
	std::wstring soundPath = L"Assets/Sound/";
	std::wstring PlayerVoice = soundPath + L"Player/Voice/";

	// Behavior
	SoundManager::GetInstance().Create(L"Walk", soundPath + L"Player/Move/Walk.mp3", 1);

	SoundManager::GetInstance().Create(L"Slide", soundPath + L"Player/Move/Slide.mp3", 1);
	SoundManager::GetInstance().Create(L"SlideVoi", PlayerVoice + L"Slide.mp3", 1);

	SoundManager::GetInstance().Create(L"JumpVoi", PlayerVoice + L"Jump.mp3", 1);

	SoundManager::GetInstance().Create(L"Hit1Voi", PlayerVoice + L"Hit1.mp3", 1);
	SoundManager::GetInstance().Create(L"Hit2Voi", PlayerVoice + L"Hit2.mp3", 1);
	SoundManager::GetInstance().Create(L"Hit3Voi", PlayerVoice + L"Hit3.mp3", 1);

	SoundManager::GetInstance().Create(L"DieVoi", PlayerVoice + L"Die.mp3", 1);

	//Attack
	SoundManager::GetInstance().Create(L"BasicShoot", soundPath + L"Player/Bullet/Basic.mp3", 5);

	SoundManager::GetInstance().Create(L"AirShoot", soundPath + L"Player/Bullet/Airshot.mp3", 1);
	SoundManager::GetInstance().Create(L"AriShootVoi", PlayerVoice + L"AirShoot.mp3", 1);

	SoundManager::GetInstance().Create(L"GunKata", soundPath+ L"Player/Attack/GunKata1.mp3", 1);
	SoundManager::GetInstance().Create(L"GunKataVoi", PlayerVoice + L"GunKata.mp3", 1);

	SoundManager::GetInstance().Create(L"MachineVoi", PlayerVoice + L"Machine.mp3", 1);
	SoundManager::GetInstance().Create(L"MoveShotVoi", PlayerVoice + L"MoveShot.mp3", 1);

	SoundManager::GetInstance().Create(L"SniperReady", soundPath + L"Player/Bullet/SniperReady.mp3", 1);
	SoundManager::GetInstance().Create(L"Sniper", soundPath + L"Player/Bullet/Sniper.mp3", 1);
	SoundManager::GetInstance().Create(L"SniperVoi", PlayerVoice + L"Sniper.mp3", 1);

	SoundManager::GetInstance().Create(L"NuclearReady", soundPath + L"Player/Attack/NuclearReady.mp3", 1);
	SoundManager::GetInstance().Create(L"NuclaerSound", soundPath + L"Player/Attack/NuclaerSound.mp3", 1);
	SoundManager::GetInstance().Create(L"NuclearReady2", soundPath + L"Player/Attack/NuclearReady2.mp3", 1);
	SoundManager::GetInstance().Create(L"NuclearFall", soundPath + L"Player/Attack/NuclerFall.mp3", 1);
	SoundManager::GetInstance().Create(L"NuclearBoom", soundPath + L"Player/Attack/NuclearBoom.mp3", 1);

	SoundManager::GetInstance().Create(L"GrenadeVoi", PlayerVoice + L"Grenade.mp3", 1);

	SoundManager::GetInstance().Create(L"Kick", soundPath + L"Player/Attack/Kick.mp3", 1);


	///////////////////////////////////
	/// Player
	///////////////////////////////////
	SoundManager::GetInstance().Create(L"Enemy1", soundPath + L"Enemy/Spawn/1.mp3", 1);
	SoundManager::GetInstance().Create(L"Enemy2", soundPath + L"Enemy/Spawn/2.mp3", 1);
	SoundManager::GetInstance().Create(L"Enemy3", soundPath + L"Enemy/Spawn/3.mp3", 1);
	SoundManager::GetInstance().Create(L"Enemy4", soundPath + L"Enemy/Spawn/4.mp3", 1);

	SoundManager::GetInstance().Create(L"Enemy1Atk", soundPath + L"Enemy/Attack/1.mp3", 1);
	SoundManager::GetInstance().Create(L"Enemy2Atk", soundPath + L"Enemy/Attack/2.mp3", 1);
	SoundManager::GetInstance().Create(L"Enemy3Atk", soundPath + L"Enemy/Attack/3.mp3", 1);
	SoundManager::GetInstance().Create(L"Enemy3Atk2", soundPath + L"Enemy/Attack/3-2.mp3", 1);


	SoundManager::GetInstance().Create(L"BossIntro", soundPath + L"Enemy/BossIntro.mp3", 1);

	SoundManager::GetInstance().Create(L"BossField", soundPath + L"Enemy/BossField.mp3", 1);

	// Fx
	SoundManager::GetInstance().Create(L"Box", soundPath + L"Effect/Box.mp3", 1);
	SoundManager::GetInstance().Create(L"Start", soundPath + L"Effect/Fight.mp3", 1);
	SoundManager::GetInstance().Create(L"Hit", soundPath + L"Effect/Hit.mp3", 1);
	SoundManager::GetInstance().Create(L"Item", soundPath + L"Effect/Item.mp3", 1);

	// BGM
	SoundManager::GetInstance().Create(L"Main", soundPath + L"BGM/main.mp3", 1);

	SoundManager::GetInstance().Create(L"Stage1", soundPath + L"BGM/stage1.mp3", 1);
	SoundManager::GetInstance().Create(L"Stage2", soundPath + L"BGM/stage2-2.mp3", 1);
	SoundManager::GetInstance().Create(L"Stage3", soundPath + L"BGM/stage3.mp3", 1);
	SoundManager::GetInstance().Create(L"Ranking", soundPath + L"BGM/Ranking.mp3", 1);

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

