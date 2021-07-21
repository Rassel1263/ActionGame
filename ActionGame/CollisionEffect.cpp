#include "DXUT.h"
#include "CollisionEffect.h"

CollisionEffect::CollisionEffect(Units* obj, std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 min, D3DXVECTOR2 max, float visibleTime, float hitTimer)
	:IEffect(pos, D3DXVECTOR2(1, 1), visibleTime)
{
	owner = obj;
	this->hitTimer = hitTimer;

	spr.LoadAll(L"Assets/Sprites/Effect/" + eftName, 0.1f, false);

	Collider::AABB aabb;
	aabb.min = min;
	aabb.max = max;

	bodies.push_back(Collider(this, owner->tag + L"Effect", &aabb, 0));
}

void CollisionEffect::Update(float deltaTime)
{
	timer += deltaTime;

	if (timer >= hitTimer)
	{
		timer = 0.0f;
		hit = true;
	}

	IEffect::Update(deltaTime);
}

void CollisionEffect::Render()
{
	IEffect::Render();

	Object::Render();
}

void CollisionEffect::OnCollision(Collider& other)
{
	if (owner->tag == other.tag) return;

	if (other.tag == L"enemy" && hit)
	{
		hit = false;
		static_cast<Units*>(other.obj)->bHit = true;
		static_cast<Units*>(other.obj)->damage = 50;
	}
}
