#include "DXUT.h"
#include "Boom.h"

Boom::Boom(Units* obj, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float timer)
{
	this->owner = obj;
	this->pos = pos;
	this->z = pos.y;
	this->timer = timer;
	ri.scale = scale;

	spr.LoadAll(L"Assets/Sprites/Item/Boom");
}

void Boom::Update(float deltaTime)
{
	timer -= deltaTime;

	if (timer <= 0.0f)
	{
		timer = 0.0f;

		nowScene->obm.AddObject(new CollisionEffect(owner, L"Boom", pos + D3DXVECTOR2(0, 30), D3DXVECTOR2(-100, -20), D3DXVECTOR2(100, 80)));
		destroy = true;
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

