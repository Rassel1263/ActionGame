#include "DXUT.h"
#include "Effect.h"

Effect::Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float aniMaxTime, float visibleTime)
	:IEffect(pos, scale, visibleTime)
{
	spr.LoadAll(L"Assets/Sprites/Effect/" + eftName, aniMaxTime, false);
}

void Effect::Update(float deltaTime)
{
	IEffect::Update(deltaTime);
}

void Effect::Render()
{
	IEffect::Render();
}
