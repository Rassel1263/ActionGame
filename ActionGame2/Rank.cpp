#include "DXUT.h"
#include "Rank.h"

Rank::Rank()
{
	bck.LoadAll(L"Assets/Sprites/effect/bck.png");
	
	WCHAR temp[10] = L"";
	wsprintf(temp, L"%06d", (int)nowScene->score);
	std::wstring str = temp;
	
	int size = str.size();
	curScore.resize(size);

	for (int i = 0; i < size; ++i)
		curScore[i].LoadAll(L"Assets/Sprites/UI/Font/Score/" + str.substr(i, 1) + L".png");

	ReadFile();
}

void Rank::Update(float deltaTime)
{
	if (initial.size() < 3)
	{
		for (char c = 'A'; c <= 'Z'; ++c)
		{
			if (Input::GetInstance().KeyDown(c))
			{
				initial.push_back(c);
				break;
			}
		}

		int size = initial.size();
		font.resize(size);

		for (int i = 0; i < size; ++i)
			font[i].LoadAll(L"Assets/Sprites/UI/Font/Rank/" + initial.substr(i, 1) + L".png");
	}
	else
		WriteFile();

	if (!initial.empty())
	{
		if (Input::GetInstance().KeyDown(VK_BACK))
			initial.pop_back();
	}
}

void Rank::Render()
{
	bck.Render(RenderInfo{});

	int xCnt = 0;
	for (auto& spr : curScore)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-200 + xCnt * 70, 250), D3DXVECTOR2(1.5, 1.5)});
		xCnt++;
	}

	xCnt = 0;

	for (auto& spr : font)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-400 + xCnt * 400, 20) });
		xCnt++;
	}

	int yCnt = 0;
	for (int i = 0; i < 3; ++i)
	{
		xCnt = 0;
		for (auto& spr : word[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-350 + xCnt * 100, -225 - yCnt * 85), D3DXVECTOR2(0.4, 0.4) });
			xCnt++;
		}

		xCnt = 0;
		for (auto& spr : scores[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(50 + xCnt * 50, -225 - yCnt * 85) });
			xCnt++;
		}

		yCnt++;
	}
}

void Rank::ReadFile()
{
	std::wifstream file(L"Assets/RankData.txt");

	rank.resize(3);
	
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
		scores[i].resize(6);

		for (int j = 0; j < 6; ++j)
		{
			if(j < 3)
				word[i][j].LoadAll(L"Assets/Sprites/UI/Font/Rank/" + rank[i].initial.substr(j, 1) + L".png");

			scores[i][j].LoadAll(L"Assets/Sprites/UI/Font/Score/" + rank[i].score.substr(j, 1) + L".png");
		}
	}
}

void Rank::WriteFile()
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		std::wofstream file(L"Assets/RankData.txt");

		RankInfo temp;

		temp.initial = initial;

		WCHAR tempStr[10];
		wsprintf(tempStr, L"%06d", (int)nowScene->score);
		temp.score = tempStr;

		rank.push_back(temp);
		std::sort(rank.begin(), rank.end(), [](const RankInfo& lhs, const RankInfo& rhs) {return std::stoi(lhs.score) > std::stoi(rhs.score); });

		rank.erase(rank.end() - 1);

		for (int i = 0; i < 3; ++i)
		{
			file << rank[i].initial << std::endl;
			file << rank[i].score << std::endl;
		}

		Game::GetInstance().ChangeScene(new MainScene());
	}
}
