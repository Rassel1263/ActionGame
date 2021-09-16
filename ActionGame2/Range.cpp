#include "DXUT.h"
#include "Range.h"

Range::Range(Unit* unit, std::wstring targetName, D3DXVECTOR2 addPos, D3DXVECTOR2 min, D3DXVECTOR2 max, D3DXCOLOR color, float detectGroundPos)
	: my(unit), targetName(targetName), addPos(addPos)
{
	CreateCollider(min, max, L"detectRange", color);
	this->detectGroundPos = detectGroundPos;
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
		if (abs(my->groundPos - coll.obj->groundPos) >= detectGroundPos) return;

		bHit = true;
		target = nowScene->player;
	}
}