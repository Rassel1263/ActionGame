#include "DXUT.h"
#include "Help.h"

Help::Help()
{
	panel.LoadAll(L"Assets/Sprites/effect/bck.png");
	panel.color.a = 0.7f;


	bck.LoadAll(L"Assets/Sprites/UI/main/help");
	bck.color.a = 0.0f;
}

void Help::Update(float deltaTime)
{
	if (static_cast<MainScene*>(nowScene)->input)
	{
		if (bck.color.a < 1.0f)
			bck.color.a += deltaTime;
	}
	else
	{
		bck.color.a -= deltaTime;
		if (bck.color.a <= 0.0f)
			destroy = true;
	}

	if (bck.color.a >= 1.0f)
	{
		if (Input::GetInstance().KeyDown(VK_RETURN))
			static_cast<MainScene*>(nowScene)->input = false;
	}

	panel.color.a = bck.color.a;

	panel.color.a = std::clamp(panel.color.a, 0.0f, 0.7f);
}

void Help::Render()
{
	panel.Render(RenderInfo{});
	bck.Render(RenderInfo{});
}

