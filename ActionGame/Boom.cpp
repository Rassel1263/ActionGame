#include "DXUT.h"
#include "Boom.h"

Boom::Boom(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float timer)
{
	this->pos = pos;
	this->z = pos.y;
	this->timer = timer;
	ri.scale = scale;

	spr.LoadAll(L"Assets/Sprites/Item/Boom");

	Collider::AABB aabb;
	aabb.min = D3DXVECTOR2(-100, -20);
	aabb.max = D3DXVECTOR2(100, 80);

	bodies.push_back(Collider(this, L"boom", &aabb, 0));
}

void Boom::Update(float deltaTime)
{
	timer -= deltaTime;

	if (timer <= 0.0f)
	{
		ignition = true;
	}

	pos.x += ri.scale.x * timer * 100 * deltaTime;

	spr.Update(deltaTime);
}

void Boom::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Boom::OnCollision(Collider& other)
{
	if (other.tag == L"enemy" && ignition)
	{
		static_cast<Enemy*>(other.obj)->bHit = true;
		destroy = true;
	}
}
