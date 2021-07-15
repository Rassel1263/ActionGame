#include "DXUT.h"
#include "Item.h"

Item::Item(D3DXVECTOR2 pos, int index)
{
	this->pos = pos;
	this->z = pos.y - 50;
	this->index = index;

	spr.LoadAll(L"Assets/Sprites/Item/" + std::to_wstring(index) + L".png");

	Collider::AABB aabb; 
	aabb.min = { -5,  -5 };
	aabb.max = { 5,  5 };

	bodies.push_back(Collider(this, L"item", &aabb, 0));
}

void Item::Update(float deltaTime)
{	
	Object::Update(deltaTime);
}

void Item::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Item::OnCollision(Collider& other)
{
	if (other.tag == L"player")
	{
		if (other.obj->z - 50 == z)
		{
			nowScene->player->SetItemEffect(index);
			destroy = true;
		}
	}
}
