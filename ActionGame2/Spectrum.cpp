#include "DXUT.h"
#include "Spectrum.h"

Spectrum::Spectrum(Sprite spr, RenderInfo ri, float time, D3DXCOLOR color, int layer)
{
	this->spr = spr;
	this->ri = ri;
	this->color = {color.r, color.g, color.b, color.a};
	colorShader = new ColorShader();

	this->layer = layer - 1;
}

void Spectrum::Update(float deltaTime)
{
	if (!spr.bAnimation)
		destroy = true;

	spr.Update(deltaTime);
}

void Spectrum::Render()
{
	colorShader->Render(colorShader, spr, ri, color);
}
