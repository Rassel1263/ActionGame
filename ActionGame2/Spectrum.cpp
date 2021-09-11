#include "DXUT.h"
#include "Spectrum.h"

Spectrum::Spectrum(Sprite spr, RenderInfo ri, float time, D3DXCOLOR color, int layer)
{
	this->spr = spr;
	this->ri = ri;
	this->color = { color.r, color.g, color.b, color.a };
	colorShader = new ColorShader();

	this->layer = layer - 1;
	attackNum = 0;
}

Spectrum::Spectrum(Sprite spr, RenderInfo ri, float time, D3DXCOLOR color, int layer, float curAniTimer, float maxAniTime, int attackNum)
{
	this->spr = spr;
	this->ri = ri;
	this->color = { color.r, color.g, color.b, color.a };
	this->attackTime = curAniTimer;
	this->maxAttackTime = maxAniTime;
	colorShader = new ColorShader();


	this->layer = layer - 1;
	this->attackNum = attackNum;
}

void Spectrum::Update(float deltaTime)
{
	if (attackNum == 4)
	{
		attackTime -= deltaTime;

		if ((spr.scene <= 23))
			if (attackTime <= 0.0f)
			{
				nowScene->obm.AddObject(new Effect(L"Player/fire1", ri.pos + D3DXVECTOR2(230 * ri.scale.x, 200), ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));
				nowScene->obm.AddObject(new Bullet(L"player", ri.pos + D3DXVECTOR2(230 * ri.scale.x, 220), D3DXVECTOR2(ri.scale.x, 0), 1500, 10, ri.pos.y, Bullet::Type::MACHINEGUN));
				attackTime = maxAttackTime;
			}
	}
	if (attackNum == 5)
	{
		attackTime -= deltaTime;

		if (attackTime <= 0.0f)
		{
			nowScene->obm.AddObject(new Effect(L"Player/fire1", ri.pos + D3DXVECTOR2(250 * ri.scale.x, 150), ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));
			nowScene->obm.AddObject(new Bullet(L"player", ri.pos + D3DXVECTOR2(250 * ri.scale.x, 170), D3DXVECTOR2(ri.scale.x, 0), 2500, 30, ri.pos.y, Bullet::Type::SNIPER));
			attackTime = maxAttackTime;
		}
	}

	if (!spr.bAnimation)
		destroy = true;

	spr.Update(deltaTime);
}

void Spectrum::Render()
{
	colorShader->Render(colorShader, spr, ri, color);
}
