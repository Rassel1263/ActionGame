#pragma once

struct RankInfo
{
	std::wstring initial = L"";
	std::wstring score = L"";
};

class Rank : public Object
{
public:
	Sprite bck;

	std::vector<RankInfo> rank;

	std::vector<Sprite> word[3];
	std::vector<Sprite> scores[3];

	std::wstring initial;
	std::vector<Sprite> font;
	std::vector<Sprite> curScore;

	RenderInfo ri;

	Rank();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ReadFile();
	void WriteFile();
};

