#include "DXUT.h"
#include "CalcPage.h"

CalcPage::CalcPage()
{
	spr.LoadAll(L"Assets/Sprites/UI/calcBck.png");

	spr.color.a = 0.0f;
	spr.bCamera = false;

	this->hp = nowScene->player->ability.hp;
	this->time = nowScene->gameTime;
	this->totalScore = nowScene->score + nowScene->destScore;
	this->combo = 0;

	layer = 3;

}

void CalcPage::Update(float deltaTime)
{
	if (spr.color.a < 1.0f)
		spr.color.a += deltaTime;
	else
	{
		if (!drawFont)
		{
			drawFont = true;

			nowScene->obm.AddObject(new Font(L"Score/", hp, D3DXVECTOR2(0, 200), D3DXVECTOR2(1, 1), 100, 0, layer + 1));
			nowScene->obm.AddObject(new Font(L"Score/", time, D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), 100, 0, layer + 1));
			nowScene->obm.AddObject(new Font(L"Combo/", combo, D3DXVECTOR2(0, -200), D3DXVECTOR2(1, 1), 100, 0, layer + 1));
			nowScene->obm.AddObject(new Font(L"Score/", totalScore, D3DXVECTOR2(500, -400), D3DXVECTOR2(1, 1), 100, 3, layer + 1));
		}

		stopTimer += deltaTime;

		if (stopTimer > 1.0f)
		{
			if (hp > 0)
				CalcNum(hp, deltaTime, 100);
			else if (time > 0)
				CalcNum(time, deltaTime, 100);
			else if (combo > 0)
				CalcNum(combo, deltaTime, 100);
			else
			{
				if (Input::GetInstance().KeyDown(VK_RETURN) && !drawFade)
				{
					drawFade = true;
					auto lambda = [] {Game::GetInstance().ChangeScene(nowScene->nextScene); };
					nowScene->obm.AddObject(new Fade(lambda));
				}
			}
		}
	}
}

void CalcPage::Render()
{
	spr.Render(RenderInfo{});
}

void CalcPage::CalcNum(float& num, float deltaTime, float speed)
{
	float tempNum = num;

	num -= speed * deltaTime;

	if (num < 0) num = 0;

	totalScore += tempNum - num;
}
