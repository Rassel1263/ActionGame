#include "DXUT.h"
#include "Unit.h"

Unit::Unit()
{
	ri.pivot = { 0.5, 0.0f };

	layer = 2;
}

void Unit::Update(float deltaTime)
{
	Object::Update(deltaTime);

	GetNowSprite().Update(deltaTime);
}

void Unit::Render()
{
	ri.pos = pos;
	GetNowSprite().Render(ri);
}

Sprite& Unit::GetNowSprite()
{
	return sprites[renderNum];
}
