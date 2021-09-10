#include "DXUT.h"
#include "SkillDirecting.h"

SkillDirecting::SkillDirecting(float timer)
{
	spr.LoadAll(L"Assets/Sprites/Effect/Player/skill.png");
	spr.bCamera = false;

	this->visibleTime = timer;
	this->maxVisibleTime = timer;

	spr.color.a = 0.0f;

	layer = -5;
}

void SkillDirecting::Update(float deltaTime)
{
	if (fill)
	{
		if(visibleTime <= 0.0f)
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

	visibleTime -= deltaTime;

}

void SkillDirecting::Render()
{
	spr.Render(RenderInfo{});
}
