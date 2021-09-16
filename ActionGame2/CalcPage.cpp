#include "DXUT.h"
#include "CalcPage.h"

CalcPage::CalcPage()
{
	nowScene->stopTime = true;

	bck.LoadAll(L"Assets/Sprites/UI/calcBck.png");
	bck.color.a = 0.0f;
	bck.bCamera = false;

	font.LoadAll(L"Assets/Sprites/UI/calcFont.png");
	font.color.a = 0.0f;
	font.bCamera = false;

	skillNum.LoadAll(L"Assets/Sprites/UI/calcSkillNum.png");
	skillNum.color.a = 0.0f;
	skillNum.bCamera = false;

	this->hp = nowScene->player->ability.hp;
	this->time = nowScene->gameTime;
	this->totalScore = nowScene->score + nowScene->destScore;
	this->combo = nowScene->player->maxCombo;

	nameGroups.resize(6);
	skill.resize(6);

	for (int i = 0; i < 6; ++i)
		nameGroups[i] = std::to_wstring(i);

	std::default_random_engine rnd(nowScene->rd());
	std::shuffle(nameGroups.begin(), nameGroups.end(), rnd);
	
	for (int i = 0; i < 6; ++i)
	{
		skill[i].LoadAll(L"Assets/Sprites/UI/Player/Skill/" + nameGroups[i] + L".png");
		skill[i].bCamera = false;
		skill[i].color.a = 0.0f;
	}

	layer = 3;

}

void CalcPage::Update(float deltaTime)
{
	if (drawTimer < 2.0f)
	{
		drawTimer += deltaTime;
		return;
	}

	if (bck.color.a < 1.0f)
		bck.color.a += deltaTime;

	if (input == 0)
	{
		if (font.color.a < 1.0f)
			font.color.a += deltaTime;

		if (!drawFont)
		{
			drawFont = true;

			nowScene->obm.AddObject(new Font(L"Score/", hp, D3DXVECTOR2(0, 300), D3DXVECTOR2(1, 1), 100, 0, layer + 1, &fontColor));
			nowScene->obm.AddObject(new Font(L"Score/", time, D3DXVECTOR2(0, 100), D3DXVECTOR2(1, 1), 100, 0, layer + 1, &fontColor));
			nowScene->obm.AddObject(new Font(L"Combo/", combo, D3DXVECTOR2(0, -100), D3DXVECTOR2(1, 1), 100, 0, layer + 1, &fontColor));
			nowScene->obm.AddObject(new Font(L"Score/", totalScore, D3DXVECTOR2(500, -300), D3DXVECTOR2(1, 1), 100, 3, layer + 1, &fontColor));
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
				if (Input::GetInstance().KeyDown(VK_RETURN))
				{
					if (nowScene->curStage == 3)
						++input;

					++input;
				}
			}
		}
	}
	else if (input == 1)
	{
		if (fontColor.a > 0.0f)
		{
			fontColor.a -= deltaTime;
			font.color.a -= deltaTime;
		}
		else
		{
			for (auto& spr : skill)
				spr.color.a += deltaTime;

			skillNum.color.a += deltaTime;

			bool numInput = false;

			if (Input::GetInstance().KeyDown(0x31))
			{
				numInput = true;
				nowScene->obm.AddObject(new UIAfterImage(skill[0], RenderInfo{ D3DXVECTOR2(-600, 0) }, 1.0f, D3DCOLOR_ARGB(155, 255, 255, 255), layer + 1));
				EnhanceData::GetInstance().SetData(std::stoi(nameGroups[0]));
			}
			else if (Input::GetInstance().KeyDown(0x32))
			{
				numInput = true;
				nowScene->obm.AddObject(new UIAfterImage(skill[1], RenderInfo{ D3DXVECTOR2(0, 0) }, 1.0f, D3DCOLOR_ARGB(155, 255, 255, 255), layer + 1));
				EnhanceData::GetInstance().SetData(std::stoi(nameGroups[1]));
			}
			else if (Input::GetInstance().KeyDown(0x33))
			{
				numInput = true;
				nowScene->obm.AddObject(new UIAfterImage(skill[2], RenderInfo{ D3DXVECTOR2(600, 0) }, 1.0f, D3DCOLOR_ARGB(155, 255, 255, 255), layer + 1));
				EnhanceData::GetInstance().SetData(std::stoi(nameGroups[2]));
			}

			if (numInput) input++;
		}
	}
	else if (input == 2)
	{
		drawFadeTimer += deltaTime;

		if (drawFadeTimer > 1.0f)
		{
			auto lambda = [] {Game::GetInstance().ChangeScene(nowScene->nextScene); };
			nowScene->obm.AddObject(new Fade(lambda));

			input++;
		}
	}
}

void CalcPage::Render()
{
	bck.Render(RenderInfo{});
	font.Render(RenderInfo{});

	skillNum.Render(RenderInfo{});

	for (int i = 0; i < 3; ++i)
		skill[i].Render(RenderInfo{ D3DXVECTOR2(-600 + i * 600, 0.0f) });

}

void CalcPage::CalcNum(float& num, float deltaTime, float speed)
{
	float tempNum = num;

	num -= speed * deltaTime;

	if (num < 0) num = 0;

	totalScore += tempNum - num;
}
