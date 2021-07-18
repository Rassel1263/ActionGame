#include "DXUT.h"
#include "Fade.h"

Fade::Fade(int stage)
{
	if (stage != 0)
	{
		fade.LoadAll(L"Assets/Sprites/UI/Start/fade.png");
		font.LoadAll(L"Assets/Sprites/UI/Start/" + std::to_wstring(stage) + L".png");
		
		fade.bCamera = false;
		font.bCamera = false;
	}
	else
	{
		fade.color.a = 0.0f;
		fade.LoadAll(L"Assets/Sprites/UI/Start/fade.png");
	}
}

void Fade::Update(float deltaTime)
{
	if (nowScene->stage != 0)
	{
		fade.color.a -= deltaTime * 0.3f;
		font.color = fade.color;

		if (fade.color.a <= 0.0f)
			destroy = true;
	}
	else
	{
		fade.color.a += deltaTime;

		if (fade.color.a >= 1.0f)
		{
			destroy = true;
			Game::GetInstance().ChangeScene(new GameScene());
		}
	}
}

void Fade::Render()
{
	ri.pos = pos;

	fade.Render(RenderInfo{});

	if(nowScene->stage != 0)
		font.Render(ri);
}
