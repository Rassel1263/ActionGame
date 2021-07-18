#pragma once
class RankPage : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	std::vector<RankInfo> rank;

	std::vector<std::vector<Sprite>> score;
	std::vector<std::vector<Sprite>> initial;

	RankPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

