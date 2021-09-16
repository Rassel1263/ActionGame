#include "DXUT.h"
#include "UIAfterImage.h"

UIAfterImage::UIAfterImage(Sprite spr, RenderInfo ri, float visibleTime, D3DXCOLOR color, int layer)
{
	this->spr = spr;
	this->ri = ri;
	this->spr.color = color;

	this->maxVisibleTime = visibleTime;
	this->visibleTime = visibleTime;

	colorShader = new ColorShader();

	this->layer = layer;
}

void UIAfterImage::Update(float deltaTime)
{
	visibleTime -= deltaTime;

	spr.color.a = visibleTime / maxVisibleTime;

	ri.scale += D3DXVECTOR2(0.01f, 0.01f) * 2;

	if (visibleTime <= 0.0f)
		destroy = true;
}

void UIAfterImage::Render()
{
	spr.Render(ri);
	//colorShader->Render(colorShader, spr, ri, D3DXVECTOR4(spr.color.r, spr.color.g, spr.color.b, spr.color.a));
}
