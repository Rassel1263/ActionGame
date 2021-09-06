#include "DXUT.h"
#include "AfterImage.h"

AfterImage::AfterImage(Sprite spr, RenderInfo ri, D3DXVECTOR2 pos, float visibleTime, D3DXCOLOR color)
{
	this->spr = spr;
	this->pos = pos;
	this->ri = ri;
	this->spr.color = color;

	this->maxVisibleTime = visibleTime;
	this->visibleTime = visibleTime;

	layer = 1;
}

void AfterImage::Update(float deltaTime)
{
	visibleTime -= deltaTime;

	spr.color.a = visibleTime / maxVisibleTime;
}

void AfterImage::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
