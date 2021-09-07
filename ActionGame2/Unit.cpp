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

	Object::Render();
}

void Unit::Hit(float damage)
{
	hit = true;
	this->hitDamage = damage;
}

void Unit::SetCollider(float left, float bottom, float right, float top, std::wstring tag)
{
	Collider::AABB aabb;
	aabb.min = { left, bottom };
	aabb.max = { right, top };
	bodies.push_back(Collider(this, tag, &aabb));
}

Sprite& Unit::GetNowSprite()
{
	return sprites[renderNum];
}
