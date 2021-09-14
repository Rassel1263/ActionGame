#include "DXUT.h"
#include "Main.h"

Main::Main()
{
	ui.resize(7);

	std::wstring filePath = L"Assets/Sprites/UI/main/";

	for (int i = 0; i < 4; ++i)
	{
		ui[i].LoadAll(filePath + L"menu/" + std::to_wstring(i));
		ui[i].bCamera = false;
		ui[i].scene = 1;
	}

	ui[0].scene = 0;

	ui[4].LoadAll(filePath + L"menu/select.png");
	ui[4].bCamera = false;

	ui[5].LoadAll(filePath + L"mainlogo");
	ui[5].bCamera = false;

	ui[6].LoadAll(filePath + L"background", 0.02f);
	ui[6].bCamera = false;
}

void Main::Update(float deltaTime)
{
	ChoiceBtn();

	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		switch (cNum)
		{
		case 0:
			Game::GetInstance().ChangeScene(new GameScene());
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			PostQuitMessage(0);
			break;
		}
	}

	for (int i = 4; i < 7; ++i)
		ui[i].Update(deltaTime);
}

void Main::Render()
{
	ui[6].Render(RenderInfo{ D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2) });

	ui[5].Render(RenderInfo{ D3DXVECTOR2(-450, 180) });

	ui[4].Render(RenderInfo{});

	for (int i = 0; i < 4; ++i)
		ui[i].Render(RenderInfo{ D3DXVECTOR2(-700 + i * 450, -400) });
}

void Main::ChoiceBtn()
{
	pNum = cNum;

	if (Input::GetInstance().KeyDown(VK_LEFT))
		cNum--;

	if (Input::GetInstance().KeyDown(VK_RIGHT))
		cNum++;

	cNum = std::clamp(cNum, 0, 3);

	if (cNum != pNum)
	{
		ui[cNum].scene = 0;
		ui[pNum].scene = 1;
	}
}
