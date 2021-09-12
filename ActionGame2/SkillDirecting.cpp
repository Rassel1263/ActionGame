#include "DXUT.h"
#include "SkillDirecting.h"

SkillDirecting::SkillDirecting(float timer, int skillNum)
{
	if (skillNum != 2)
	{
		spr.LoadAll(L"Assets/Sprites/Effect/Player/skill.png");
		layer = -5;
	}
	else
	{
		spr.LoadAll(L"Assets/Sprites/Effect/Player/skill2.png");
		layer = 1100;
	}

	spr.bCamera = false;

	this->visibleTime = timer;
	this->maxVisibleTime = timer;

	spr.color.a = 0.0f;


	this->skillNum = skillNum;
}


void SkillDirecting::Update(float deltaTime)
{
	if (skillNum != 1)
	{
		if (fill)
		{
			if (visibleTime <= 0.0f)
				spr.color.a -= deltaTime * 2;

			if (spr.color.a <= 0.0f)
				destroy = true;
		}
		else
		{
			spr.color.a += deltaTime * 2;

			if (spr.color.a >= 1.0f)
				fill = true;
		}
	}
	else
	{
		if (nowScene->player->nuclear)
			spr.color.a += deltaTime * 2;
		else
		{
			spr.color.a -= deltaTime * 2;

			if (spr.color.a <= 0.0f)
				destroy = true;
		}
	}

	visibleTime -= deltaTime;
	spr.color.a = std::clamp(spr.color.a, 0.0f, 1.0f);

}

void SkillDirecting::Render()
{
	spr.Render(RenderInfo{});
}
