#include "DXUT.h"
#include "BossIntro.h"

BossIntro::BossIntro(float x)
{
	nowScene->player->fallowCamera = false;
	nowScene->bossIntro = true;
	Camera::GetInstance().destCameraPos.x = x;

	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Play(L"BossIntro");

	spr.LoadAll(L"Assets/Sprites/Effect/enemy/bossIntro.png");
	spr.color.a = 0.0f;
	spr.bCamera = false;
}

void BossIntro::Update(float deltaTime)
{
	spr.color.a += deltaTime * destColor * 2;

	if (spr.color.a <= 0.0f || spr.color.a >= 1.0f)
	{
		std::clamp(spr.color.a, 0.0f, 1.0f);
		blink++;
		destColor = -destColor;
	}

	if (blink >= 4)
	{
		SoundManager::GetInstance().Play(L"BossField", true);

		nowScene->player->fallowCamera = true;
		nowScene->bossIntro = false;
		destroy = true;
	}
}

void BossIntro::Render()
{
	spr.Render(RenderInfo{});
}
