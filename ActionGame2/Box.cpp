#include "DXUT.h"
#include "Box.h"

Box::Box(D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/box", 0.1f, false);

	ri.pivot = { 0.5, 0.0f };

	Collider::AABB aabb;
	aabb.min = {-50, 0};
	aabb.max = { 50, 150 };

	bodies.push_back(Collider(this, L"box", &aabb));

	this->pos = pos;
	this->groundPos = pos.y;

	layer = 1080 - (groundPos + 540);
}

void Box::Update(float deltaTime)
{
	if (hit)
		spr.Update(deltaTime);

	if (!spr.bAnimation)
	{
		nowScene->obm.AddObject(new Item(pos, nowScene->GetRandomNum(1, 2)));

		destroy = true;
	}
}

void Box::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Box::OnCollision(Collider& coli)
{
	if (coli.tag == L"playerbullet" || coli.tag == L"playeratkCollider")
	{
		if (!hit)
		{
			SoundManager::GetInstance().Play(L"Box");
			bCollider = false;
			hit = true;
		}
	}
}
