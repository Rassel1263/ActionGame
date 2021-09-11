#include "DXUT.h"
#include "Effect.h"

Effect::Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float aniTime, int atkScene, std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/effect/" + eftName, aniTime, false);
	this->pos = pos;
	ri.scale = scale;
	ri.pivot = pivot;
	this->atkScene = atkScene;
	this->func = func;
	
	effectNum = 0;

	layer = 1100;
}

Effect::Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float visibleTime, bool bCamera, std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/effect/" + eftName);
	this->pos = pos;
	ri.scale = scale;
	ri.pivot = pivot;
	this->visibleTime = visibleTime;
	this->maxVisibleTime = visibleTime;
	spr.bCamera = bCamera;
	this->func = func;

	effectNum = 1;

	layer = 1100;
}
Effect::Effect(std::wstring eftName, D3DXVECTOR2* pos, D3DXVECTOR2 scale, D3DXVECTOR2 offset, float visibleTime, std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/effect/" + eftName);
	this->fallowPos = pos;
	ri.scale = scale;
	this->visibleTime = visibleTime;
	this->offset = offset;
	this->maxVisibleTime = visibleTime;
	this->func = func;	

	effectNum = 2;

	layer = 1100;
}


void Effect::Update(float deltaTime)
{
	if (effectNum == 0)
	{
		if (atkScene > 0 && spr.scene == atkScene)
			if (func) func();

		if (!spr.bAnimation)
		{
			if (func) func();
			destroy = true;
		}
	}
	else if (effectNum == 1)
	{
		spr.color.a = visibleTime / maxVisibleTime;

		if (spr.color.a <= 0.0f)
		{
			if (func) func();
			destroy = true;
		}

		visibleTime -= deltaTime;
	}
	else if (effectNum == 2)
	{
		this->pos = *fallowPos + offset;
		spr.color.a = visibleTime / maxVisibleTime;

		if (spr.color.a <= 0.0f)
		{
			if (func) func();
			destroy = true;
		}

		visibleTime -= deltaTime;
	}
	spr.Update(deltaTime);
}

void Effect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
