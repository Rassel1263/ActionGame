#include "DXUT.h"
#include "AttackCollider.h"

AttackCollider::AttackCollider(Units* obj, D3DXVECTOR2 offset, D3DXVECTOR2 attackVec)
{
	spr.LoadAll(L"Assets/Sprites/Pixel.png");

	this->obj = obj;
	pos = obj->pos + offset;
	this->attackVec = attackVec;

	Collider::AABB aabb;
	aabb.min = { -5, -5 };
	aabb.max = { 5, 5 };

	bodies.push_back(Collider(this, obj->tag + L"Attack", &aabb, 0));
}

void AttackCollider::Update(float deltaTime)
{
	visibleTime -= deltaTime;

	if (visibleTime <= 0.0f)
		destroy = true;
}

void AttackCollider::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void AttackCollider::OnCollision(Collider& other)
{
	if (obj->tag == other.tag) return;
	if (obj->tag == L"enemy" && other.tag == L"enemyRange") return;
	if (obj->tag == L"boss" && other.tag == L"enemyRange") return;

	if (other.tag == L"enemy")
	{
		nowScene->player->target = static_cast<Enemy*>(other.obj);
	}

	nowScene->obm.AddObject(new Effect(L"Hit", pos, D3DXVECTOR2(0.2, 0.2)));

	D3DXVECTOR2 vtemp = attackVec;

	vtemp.x *= obj->ri.scale.x;
	D3DXVec2Normalize(&vtemp, &vtemp);

	if (!other.obj->bGround)
	{
		other.obj->force.x += vtemp.x * obj->ability.atkPower * 10.0f;
		other.obj->velocity.y = vtemp.y * obj->ability.atkPower * 100.0f;
	}
	else
	{
		other.obj->force += vtemp * obj->ability.atkPower * 10.0f;
	}

	static_cast<Units*>(other.obj)->bHit = true;
	static_cast<Units*>(other.obj)->damage = obj->ability.atkPower;
}

