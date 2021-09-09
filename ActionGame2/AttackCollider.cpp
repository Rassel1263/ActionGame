#include "DXUT.h"
#include "AttackCollider.h"

AttackCollider::AttackCollider(std::wstring team, D3DXVECTOR2 pos, D3DXVECTOR2 offset, Collider::AABB aabb, float damage, D3DXVECTOR2 attackPower, float yVec, float collisionTime)
{
	this->tag = team;

	this->pos = pos + offset;
	this->ownerPos = pos;
	this->yVec = yVec;
	this->damage = damage;
	this->attackPower = attackPower;
	this->collisionTime = collisionTime;
	
	bodies.push_back(Collider(this, tag + L"atkCollider", &aabb));
}

AttackCollider::AttackCollider(std::wstring team, D3DXVECTOR2* pos, D3DXVECTOR2 offset, Collider::AABB aabb, float damage, D3DXVECTOR2 attackPower, float yVec, float collisionTime)
{
	this->tag = team;

	this->pos = *pos + offset;
	this->fallowPos = pos;
	this->ownerPos = *pos;
	this->offset = offset;
	this->yVec = yVec;
	this->damage = damage;
	this->attackPower = attackPower;
	this->collisionTime = collisionTime;

	bodies.push_back(Collider(this, tag + L"atkCollider", &aabb));
}

void AttackCollider::Update(float deltaTime)
{
	if (fallowPos)
		pos = *fallowPos + offset;

	collisionTime -= deltaTime;
	
	if(collisionTime <= 0.0f)
		destroy = true;
}

void AttackCollider::Render()
{
	Object::Render();
}

void AttackCollider::OnCollision(Collider& coli)
{
	if (tag == coli.tag) return;

	if (coli.tag == L"enemy" || coli.tag == L"player")
	{
		D3DXVECTOR2 dir = { (ownerPos.x - coli.obj->pos.x > 0) ? -1.0f: 1.0f, yVec };
		D3DXVec2Normalize(&dir, &dir);
		if (coli.obj->bGround)
			static_cast<Unit*>(coli.obj)->Hit(damage, D3DXVECTOR2(dir.x * attackPower.x, dir.y * attackPower.y));
		else
		{
			dir.y = 0;
			static_cast<Unit*>(coli.obj)->Hit(damage, D3DXVECTOR2(dir.x * attackPower.x, dir.y * attackPower.y));
		}
	}
}

