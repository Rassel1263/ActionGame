#include "DXUT.h"
#include "Effect.h"

Effect::Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float visibleTime)
	:IEffect(pos, scale, visibleTime)
{
	spr.LoadAll(L"Assets/Sprites/Effect/" + eftName, 0.1f, false);
}

void Effect::Update(float deltaTime)
{
	IEffect::Update(deltaTime);
}

void Effect::Render()
{
	IEffect::Render();
}
