#include "DXUT.h"
#include "Ranking.h"

Ranking::Ranking()
{
	Game::GetInstance().destCameraPos = { 0, 0 };

	spr.LoadAll(L"Assets/Sprites/UI/Font/World/A.png");
}

void Ranking::Update(float deltaTime)
{
	if (initial.size() < 3)
	{
		for (char c = 'A'; c <= 'Z'; ++c)
		{
			if (Input::GetInstance().KeyDown(c))
			{
				initial += c;
				break;
			}
		}

		int size = initial.size();
		fonts.resize(size);
		
		for (int i = 0; i < size; ++i)
			fonts[i].LoadAll(L"Assets/Sprites/UI/Font/Word/" + initial.substr(i, 1) + L".png");
	}
	else
		WriteFile();

	if (!initial.empty())
	{
		if (Input::GetInstance().KeyDown(VK_BACK))
			initial.pop_back();
	}

}

void Ranking::Render()
{
	int count = 0;
	for (auto& spr : fonts)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-100 + count * 100, 0) });
		count++;
	}
}

void Ranking::WriteFile()
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		int size = 3;

		rank.resize(size);
		std::wifstream read(L"Rank.txt");

		if (read.is_open())
		{
			for (int i = 0; i < size; ++i)
			{
				read >> rank[i].score;
				read >> rank[i].initial;
			}
		}

		std::wofstream write(L"Rank.txt");

		RankInfo temp;
		temp.initial = initial;
		temp.score = nowScene->score;

		rank.push_back(temp);
		std::sort(rank.begin(), rank.end(), [](const RankInfo& lhs, const RankInfo& rhs) { return lhs.score > rhs.score; });

		rank.erase(rank.end() - 1);

		for (int i = 0; i < size; ++i)
		{
			write << rank[i].score << std::endl;
			write << rank[i].initial << std::endl;
		}

		Game::GetInstance().ChangeScene(new MainScene());
	}
}
