#include "DXUT.h"
#include "EndPage.h"

DiePage::DiePage()
{
	spr.LoadAll(L"Assets/Sprites/UI/Die");
	spr.bCamera = false;

	layer = 99;

	spr.color.a = 0.0f;
}

void DiePage::Update(float deltaTime)
{
	if (spr.color.a >= 1.0f)
	{
		if (Input::GetInstance().KeyDown(VK_RETURN))
		{
			Game::GetInstance().ChangeScene(new MainScene());
		}
	}
	else
		spr.color.a += deltaTime;
}

void DiePage::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
