#include "DXUT.h"
#include "Item.h"

Item::Item(D3DXVECTOR2 pos, int index)
{
	this->pos = pos;
	this->index = index;

	spr.LoadAll(L"Assets/Sprites/Item/" + std::to_wstring(index) + L".png");
}

void Item::Update(float deltaTime)
{
}

void Item::Render()
{
}
