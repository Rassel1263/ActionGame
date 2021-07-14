#include "DXUT.h"
#include "Effect.h"

Effect::Effect(Sprite spr, D3DXVECTOR2 scale,  D3DXVECTOR2 pos, float visibleTime)
{
	this->spr = spr;
	ri.scale = scale;
	this->pos = pos;
	this->visibleTime = visibleTime;
}

void Effect::Update(float deltaTime)
{
	timer += deltaTime;

	spr.color.a = (visibleTime - timer) / visibleTime;

	if (spr.color.a <= 0.0f)
		destroy = true;
}

void Effect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
