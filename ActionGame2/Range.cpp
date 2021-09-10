#include "DXUT.h"
#include "Range.h"

Range::Range(Unit* unit, std::wstring targetName, D3DXVECTOR2 addPos, D3DXVECTOR2 min, D3DXVECTOR2 max, D3DXCOLOR color)
	: my(unit), targetName(targetName), addPos(addPos)
{
	CreateCollider(min, max, L"detectRange", color);
}

void Range::Update(float deltaTime)
{
	pos = my->pos + addPos;
}

void Range::Render()
{
	Object::Render();
}

void Range::OnCollision(Collider& coll)
{
	if (coll.tag == L"player")
	{
		bHit = true;
		target = nowScene->player;
	}
}