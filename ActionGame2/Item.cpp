#include "DXUT.h"
#include "Item.h"

Item::Item(D3DXVECTOR2 pos, int index)
{
	this->pos = pos;
	ri.pivot = { 0.5, 0.0f };

	if (index == 1)
		spr.LoadAll(L"Assets/Sprites/Item/ATKup");
	else if (index == 2)
		spr.LoadAll(L"Assets/Sprites/Item/Grenade");

	CreateCollider(D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 100), L"item");
}

void Item::Update(float deltaTime)
{
	spr.Update(deltaTime);
}

void Item::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Item::OnCollision(Collider& coli)
{
	if (coli.tag == L"player")
		destroy = true;
}
