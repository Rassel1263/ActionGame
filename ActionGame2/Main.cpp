#include "DXUT.h"
#include "Main.h"

bool Main::intro = false;

Main::Main()
{
	if (!intro)
		introSpr.LoadAll(L"Assets/Sprites/UI/Intro", 0.03f, false);

	SoundManager::GetInstance().Play(L"Main", true);

	Camera::GetInstance().destCameraPos = { 0, 0 };
	Camera::GetInstance().cameraPos = { 0, 0 };

	nowScene->obm.AddObject(new Effect(L"bck.png", D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 2.0f, false));

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
	if (!intro)
	{
		if (!introSpr.bAnimation)
			intro = true;

		introSpr.Update(deltaTime);
	}
	else 
	{
		ChoiceBtn();

		if (Input::GetInstance().KeyDown(VK_RETURN) && !static_cast<MainScene*>(nowScene)->input)
		{
			SoundManager::GetInstance().Play(L"ClickBtn");

			static_cast<MainScene*>(nowScene)->input = true;

			switch (cNum)
			{
			case 0:
				Game::GetInstance().ChangeScene(new GameScene());
				SoundManager::GetInstance().StopAll();
				break;
			case 1:
				nowScene->obm.AddObject(new RankPage());
				break;
			case 2:
				nowScene->obm.AddObject(new Help());
				break;
			case 3:
				PostQuitMessage(0);
				break;
			}
		}

		for (int i = 4; i < 7; ++i)
			ui[i].Update(deltaTime);
	}
}

void Main::Render()
{
	if (!intro)
		introSpr.Render(RenderInfo{D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2)});
	else
	{
		ui[6].Render(RenderInfo{ D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2) });

		ui[5].Render(RenderInfo{ D3DXVECTOR2(-450, 180) });

		ui[4].Render(RenderInfo{ D3DXVECTOR2(-880 + cNum * 450, -400) });

		for (int i = 0; i < 4; ++i)
			ui[i].Render(RenderInfo{ D3DXVECTOR2(-700 + i * 450, -400) });
	}
}

void Main::ChoiceBtn()
{
	if (static_cast<MainScene*>(nowScene)->input) return;

	pNum = cNum;

	if (Input::GetInstance().KeyDown(VK_LEFT))
		cNum--;

	if (Input::GetInstance().KeyDown(VK_RIGHT))
		cNum++;

	cNum = std::clamp(cNum, 0, 3);

	if (cNum != pNum)
	{
		SoundManager::GetInstance().Play(L"MoveBtn");

		ui[cNum].scene = 0;
		ui[pNum].scene = 1;
	}
}
