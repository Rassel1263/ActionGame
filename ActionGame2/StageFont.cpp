#include "DXUT.h"
#include "StageFont.h"

StageFont::StageFont(Type type)
{
	this->type = type;

	bck.LoadAll(L"Assets/Sprites/effect/bck.png");
	if (type == Type::START)
	{
		spr.LoadAll(L"Assets/Sprites/effect/StageStart/" + std::to_wstring(nowScene->curStage), 0.05f, false);
		bck.color.a = 1.0f;
	}
	else if (type == Type::CLEAR)
		spr.LoadAll(L"Assets/Sprites/effect/StageClear", 0.05f, false);
	else if (type == Type::FAIL)
	{
		spr.LoadAll(L"Assets/Sprites/effect/StageFail", 0.05f, false);
		bck.color.a = 0.0f;
	}

	spr.bCamera = false;
	bck.bCamera = false;
}

void StageFont::Update(float deltaTime)
{
	if (type == Type::START)
	{
		if (!spr.bAnimation)
		{
			bck.color.a -= deltaTime * 2;

			if (bck.color.a <= 0.0f)
				destroy = true;
		}
	}

	else if (type == Type::CLEAR)
	{
	}

	else if (type == Type::FAIL)
	{
		if (!spr.bAnimation)
		{
			bck.color.a += deltaTime * 0.5f;
			spr.color.a -= deltaTime * 0.5f;

			if (bck.color.a >= 1.0f)
				destroy = true;
		}
	}

	spr.Update(deltaTime);
}

void StageFont::Render()
{
	bck.Render(RenderInfo{});

	ri.pos = pos;
	spr.Render(ri);
}
