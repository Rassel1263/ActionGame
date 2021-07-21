#pragma once

struct RankInfo
{
	int score = 0;
	std::wstring initial = L"NONE";
};

class Ranking : public Object
{
public:
	std::wstring initial;
	std::vector<Sprite> fonts;
	std::vector<RankInfo> rank;
	
	Sprite spr;
	RenderInfo ri;

	Ranking();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void WriteFile();
};

