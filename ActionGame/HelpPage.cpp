#include "DXUT.h"
#include "HelpPage.h"

HelpPage::HelpPage()
{
	pos.x = -640;
	Game::GetInstance().destCameraPos = { pos.x, 0 };

	page.LoadAll(L"Assets/Sprites/UI/Main/HelpBackground");

	arrow.LoadAll(L"Assets/Sprites/UI/Main/arrow.png");
}

void HelpPage::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		Game::GetInstance().destCameraPos = { 0, 0 };
	}

	if (Input::GetInstance().KeyDown(VK_RIGHT))
	{
		if (page.scene >= page.szScene)
			Game::GetInstance().destCameraPos = { 0, 0 };
		else
			page.scene++;
	}

	if (Game::GetInstance().cameraPos.x >= -0.1f)
	{
		nowScene->click = true;
		destroy = true;
	}
}

void HelpPage::Render()
{
	ri.pos = pos;
	page.Render(ri);
}
