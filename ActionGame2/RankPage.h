#pragma once
#include "Rank.h"

class RankPage : public Object
{
public:
	Sprite panel;
	Sprite bck;

	std::vector<RankInfo> rank;

	std::vector<Sprite> word[3];
	std::vector<Sprite> score[3];

	RankPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void ReadFile();
};

