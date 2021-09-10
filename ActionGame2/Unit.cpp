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
	layer = 1080 - (groundPos + 540);

	if (hit)
	{
		hitTimer += deltaTime;

		if (hitTimer >= hitTime)
			hit = false;

		if (!hit) hitTimer = 0.0f;
	}

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
	if (!superArmor)
	{
		this->force.x += addForce.x;
		this->velocity.y = addForce.y;
	}

	hit = true;
	this->ability.hp -= damage;

	if (ability.hp <= 0) ability.hp = 0;
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
