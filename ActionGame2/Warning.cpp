#include "DXUT.h"
#include "Warning.h"

Warning::Warning(std::wstring name, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float timer)
{
	std::wstring filePath = L"Assets/Sprites/effect/Enemy/";

	bck.LoadAll(filePath + name);
	bck.color.a = 0.2f;	  
						  
	spr.LoadAll(filePath + name);
	spr.color.a = 0.5f;
	ri.scale = scale;
	ri.pivot = pivot;
	ri.pos = pos;

	this->maxTimer = timer;
}

void Warning::Update(float deltaTime)
{
	timer += deltaTime;
	spr.widthRatio = timer / maxTimer;

	if (timer >= maxTimer)
		destroy = true;
}

void Warning::Render()
{
	bck.Render(ri);
	spr.Render(ri);
}
