#include "DXUT.h"
#include "AfterImage.h"

AfterImage::AfterImage(Sprite spr, RenderInfo ri, float visibleTime, D3DXCOLOR color, int layer)
{
	this->spr = spr;
	this->ri = ri;
	this->spr.color = color;

	this->maxVisibleTime = visibleTime;
	this->visibleTime = visibleTime;

	colorShader = new ColorShader();

	this->layer = layer - 1;

	effectNum = 1;
}

AfterImage::AfterImage(Sprite spr, RenderInfo ri, D3DXVECTOR2 destScale, D3DXCOLOR color, int layer, bool skill)
{
	this->spr = spr;
	this->ri = ri;
	this->ri.scale = destScale;
	this->spr.color = color;
	this->skill = skill;

	colorShader = new ColorShader();

	this->layer = layer - 1;
	effectNum = 2;
}

void AfterImage::Update(float deltaTime)
{
	if (effectNum == 1)
	{
		visibleTime -= deltaTime;
		spr.color.a = visibleTime / maxVisibleTime;

		if (spr.color.a <= 0.0f) destroy = true;
	}
	else if (effectNum == 2)
	{
		D3DXVec2Lerp(&ri.scale, &ri.scale, &destScale, 0.05f);

		if (abs(ri.scale.x) <= 1.0f || ri.scale.y <= 1.0f)
			destroy = true;
	}
	
}

void AfterImage::Render()
{
	if(skill)
		ri.pos = nowScene->player->pos;

	colorShader->Render(colorShader, spr, ri, D3DXVECTOR4(spr.color.r, spr.color.g, spr.color.b, spr.color.a));
}
