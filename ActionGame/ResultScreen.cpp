#include "DXUT.h"
#include "ResultScreen.h"

ResultScreen::ResultScreen()
{
	fade.LoadAll(L"Assets/Sprites/UI/ResultScene/fade.png");
	fade.bCamera = false;
	fade.color.a = 0.0f;

	ui.resize(3);
	ui[0].LoadAll(L"Assets/Sprites/UI/ResultScene/Time.png");
	ui[1].LoadAll(L"Assets/Sprites/UI/ResultScene/hp.png");
	ui[2].LoadAll(L"Assets/Sprites/UI/ResultScene/Score.png");

	for (int i = 0; i < 3; ++i)
		ui[i].bCamera = false;

	this->score = nowScene->score;
	this->time = nowScene->timer;
	this->hp = nowScene->player->ability.hp;
}

void ResultScreen::Update(float deltaTime)
{
	if (fade.color.a >= 1.0f && bFade)
	{
		bFade = false;
		nowScene->obm.AddObject(new Font(L"Timer", D3DXVECTOR2(0, 100), D3DXVECTOR2(2, 2), 30, &time));
		nowScene->obm.AddObject(new Font(L"Timer", D3DXVECTOR2(0, 0), D3DXVECTOR2(2, 2), 30, &hp));
		nowScene->obm.AddObject(new Font(L"Timer", D3DXVECTOR2(0, -100), D3DXVECTOR2(2, 2), 30, &score));

	}
	else
		fade.color.a += deltaTime * 0.5f;

	if (!bFade)
	{
		CalcNum(time, 100);
		CalcNum(hp, 50);

		if (Input::GetInstance().KeyDown(VK_SPACE))
		{
			Scene::score = score;
			Game::GetInstance().ChangeScene(nowScene->nextScene);
		}

	}

}

void ResultScreen::Render()
{
	ri.pos = pos;
	fade.Render(ri);

	int count = 0;
	if (fade.color.a >= 1.0f)
	{
		for (auto& spr : ui)
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-200, 100 + count * 100) });
			count--;
		}
	}
}

void ResultScreen::CalcNum( float& num, float multifle)
{
	float tempNum = num;

	if (num > 0)
	{
		num -= Game::GetInstance().unscaleTime * 100;

		if (num < 0) num = 0;

		tempNum = tempNum - num;

		score += tempNum * multifle;
	}
}

