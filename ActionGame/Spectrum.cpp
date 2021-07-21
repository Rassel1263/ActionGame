#include "DXUT.h"
#include "Spectrum.h"

Spectrum::Spectrum(Sprite spr, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float visibleTime) : IEffect(pos, scale, visibleTime)
{
	this->spr = spr;
}

void Spectrum::Update(float deltaTime)
{
	IEffect::Update(deltaTime);
}

void Spectrum::Render()
{
	IEffect::Render();
}
