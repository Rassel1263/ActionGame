#include "DXUT.h"
#include "MainBackground.h"

MainBackground::MainBackground()
{
	spr.LoadAll(L"Assets/Sprites/UI/Main/background.png");

	button.resize(3);

	button[0].LoadAll(L"Assets/Sprites/UI/Main/Help");
	button[1].LoadAll(L"Assets/Sprites/UI/Main/Start");
	button[2].LoadAll(L"Assets/Sprites/UI/Main/Ranking");

}

void MainBackground::Update(float deltaTime)
{
	int prevBtn = curBtn;

	if (Input::GetInstance().KeyDown(VK_LEFT) && curBtn > 0 && nowScene->click)
		curBtn--;
	else if(Input::GetInstance().KeyDown(VK_RIGHT) && curBtn < 2 && nowScene->click)
		curBtn++;

	if (prevBtn != curBtn)
		button[prevBtn].scene = 0;

	button[curBtn].scene = 1;

	if (Input::GetInstance().KeyDown(VK_RETURN) && nowScene->click)
	{
		nowScene->click = false;

		switch (curBtn)
		{
		case 0:
			nowScene->obm.AddObject(new HelpPage());
			break;
		case 1:
			nowScene->obm.AddObject(new Fade(0));
			break;
		case 2:
			nowScene->obm.AddObject(new RankPage());
			break;
		}
	}
}

void MainBackground::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	int count = 0;
	for (auto& spr : button)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-200 + count * 200, -50) });
		count++;
	}
}
