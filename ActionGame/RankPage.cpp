#include "DXUT.h"
#include "RankPage.h"

RankPage::RankPage()
{
	pos.x = 640.0f;
	Game::GetInstance().destCameraPos = { pos.x, 0 };

	spr.LoadAll(L"Assets/Sprites/UI/Main/Rank");

	std::wifstream read(L"Rank.txt");

	rank.resize(3);
	initial.resize(3);
	score.resize(3);

	for (int i = 0; i < 3; ++i)
		initial[i].resize(i);

	if (read.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			read >> rank[i].score;
			read >> rank[i].initial;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		initial[i].resize(3);

		for (int j = 0; j < 3; ++j)
			initial[i][j].LoadAll(L"Assets/Sprites/UI/Font/Word/" + rank[i].initial.substr(j, 1) + L".png");

		std::wstring nums = std::to_wstring(rank[i].score);
		int numSize = nums.size();
		score[i].resize(numSize);

		for (int j = 0; j < numSize; ++j)
			score[i][j].LoadAll(L"Assets/Sprites/UI/Font/Timer/" + nums.substr(j, 1) + L".png");
	}
}

void RankPage::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		Game::GetInstance().destCameraPos = { 0, 0 };
	}

	if (Game::GetInstance().cameraPos.x <= 0.1f)
	{
		nowScene->click = true;
		destroy = true;
	}
}

void RankPage::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	int yCount = 0;

	for (int i = 0; i < 3; ++i)
	{
		int xCount = 0;

		for (auto& spr : initial[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(pos.x - 200 + xCount * 50, 30 - yCount * 70) });
			xCount++;
		}

		xCount = 0;
		for (auto& spr : score[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(pos.x + 20 + xCount * 40, 30 - yCount * 70), D3DXVECTOR2(2, 2)});
			xCount++;
		}

		yCount++;
	}
}
