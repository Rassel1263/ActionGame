#include "DXUT.h"
#include "RankPage.h"

RankPage::RankPage()
{
	panel.LoadAll(L"Assets/Sprites/effect/bck.png");
	panel.color.a = 0.7f;


	bck.LoadAll(L"Assets/Sprites/UI/main/rank");
	bck.color.a = 0.0f;

	ReadFile();
}

void RankPage::Update(float deltaTime)
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

void RankPage::Render()
{
	panel.Render(RenderInfo{});
	bck.Render(RenderInfo{});

	int yCnt = 0;
	for (int i = 0; i < 3; ++i)
	{
		int xCnt = 0;
		for (auto& spr : word[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-500 + xCnt * 150, 100 - yCnt * 200), D3DXVECTOR2(0.8, 0.8)});
			xCnt++;

			spr.color.a = bck.color.a;
		}

		xCnt = 0;
		for (auto& spr : score[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(100 + xCnt * 100, 100 - yCnt * 200), D3DXVECTOR2(2, 2)});
			xCnt++;
			spr.color.a = bck.color.a;

		}

		yCnt++;
	}
}

void RankPage::ReadFile()
{
	rank.resize(3);

	std::wifstream file(L"Assets/RankData.txt");

	if (file.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			file >> rank[i].initial;
			file >> rank[i].score;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		word[i].resize(3);
		score[i].resize(6);

		for (int j = 0; j < 6; ++j)
		{
			if (j < 3)
			{
				word[i][j].LoadAll(L"Assets/Sprites/UI/Font/Rank/" + rank[i].initial.substr(j, 1) + L".png");
				word[i][j].color.a = 0.0f;
			}

			score[i][j].LoadAll(L"Assets/Sprites/UI/Font/Score/" + rank[i].score.substr(j, 1) + L".png");
			score[i][j].color.a = 0.0f;
		}
	}
}
