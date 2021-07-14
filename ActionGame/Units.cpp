#include "DXUT.h"
#include "Units.h"

Units::Units(D3DXVECTOR2 pos)
{
    this->pos = pos;
}

void Units::Update(float deltaTime)
{
    spr[renderer].Update(deltaTime);

    Object::Update(deltaTime);
}

void Units::Render()
{
    ri.pos = pos;
    spr[renderer].Render(ri);

    Object::Render();
}

bool Units::Move(float deltaTime)
{
    return false;
}

void Units::SetAbility(float hp, float speed, float atkPower, float atkSpeed)
{
    ability.hp = hp;
    ability.speed = speed;
    ability.atkPower = atkPower;
    ability.atkSpeed = atkSpeed;

}

void Units::SetCollider(float left, float top, float right, float bottom, D3DXCOLOR color)
{
    Collider::AABB aabb;
    aabb.min = { left, top };
    aabb.max = { right, bottom };

    bodies.push_back(Collider(this, tag, &aabb, 0, color));
}

void Units::SetAttackInfo(D3DXVECTOR2 offset, D3DXVECTOR2 attackVec, float atkPower, float timer)
{
    this->offset = offset;
    this->attackVec = attackVec;
    ability.atkPower = atkPower;
    this->aniTimer = spr[renderer].aniMaxTime * timer;
}

void Units::Attack()
{
    nowScene->obm.AddObject(new AttackCollider(this, offset, attackVec));
}
