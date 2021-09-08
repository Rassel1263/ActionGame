#include "DXUT.h"
#include "Unit.h"

D3DXVECTOR2 Unit::GetDistanceFromTarget(D3DXVECTOR2 targetPos)
{
	return targetPos - pos;
}

Unit::Unit()
{
	ri.pivot = { 0.5, 0.0f };

	layer = 2;
}

void Unit::Update(float deltaTime)
{
	GetNowSprite().Update(deltaTime);

	Object::Update(deltaTime);
}

void Unit::Render()
{
	ri.pos = pos;
	GetNowSprite().Render(ri);

	Object::Render();
}

void Unit::Hit(float damage, D3DXVECTOR2 addForce)
{
	if (hit) return;

	hit = true;
	this->hitDamage = damage;
	this->force.x += addForce.x;
	this->velocity.y = addForce.y * 100;
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
