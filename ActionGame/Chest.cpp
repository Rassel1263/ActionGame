#include "DXUT.h"
#include "Chest.h"

Chest::Chest(D3DXVECTOR2 pos)
{
	this->pos = pos;

	spr.resize(2);

	spr[0].LoadAll(L"Assets/Sprites/Item/ChestIdle");
	spr[1].LoadAll(L"Assets/Sprites/Item/ChestOpen");

	Collider::AABB aabb;
	aabb.min = D3DXVECTOR2(-30, -50);
	aabb.max = D3DXVECTOR2(30, 30);

	bodies.push_back(Collider(this, L"chest", &aabb, 0));
}

void Chest::Update(float deltaTime)
{
	if (!spr[1].bAnimation)
	{
		spr[1].color.a -= deltaTime;

		if (spr[1].color.a <= 0.0f)
			destroy = true;
	}

	spr[renderNum].Update(deltaTime);
}

void Chest::Render()
{
	ri.pos = pos;
	spr[renderNum].Render(ri);

	Object::Render();
}

void Chest::OnCollision(Collider& other)
{
	if (other.tag == L"playerAttack")
	{
		if (renderNum == 0)
		{
			nowScene->obm.AddObject(new Item(pos, 2));
			renderNum = 1;
		}
		spr[renderNum].bAniLoop = false;
	}
}
