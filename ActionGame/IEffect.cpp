#include "DXUT.h"
#include "IEffect.h"

IEffect::IEffect(D3DXVECTOR2 pos,  D3DXVECTOR2 scale, float visibleTime)
{
	ri.scale = scale;
	this->pos = pos;
	this->visibleTime = visibleTime;

	if (this->visibleTime > 0.0f)
		spectrum = true;
}

void IEffect::Update(float deltaTime)
{
	if (spectrum)
	{
		timer += deltaTime;

		spr.color.a = (visibleTime - timer) / visibleTime;

		if (spr.color.a <= 0.0f)
			destroy = true;
	}
	else
	{
		std::cout << spr.scene << std::endl;

		if (!spr.bAnimation)
			destroy = true;
	}

	spr.Update(deltaTime);
}

void IEffect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
