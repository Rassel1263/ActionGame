#include "DXUT.h"
#include "Units.h"

Units::Units(D3DXVECTOR2 pos)
{
    this->pos = pos;
}

void Units::Update(float deltaTime)
{
    spr[(UnitState)renderNum].Update(deltaTime);
}

void Units::Render()
{
    ri.pos = pos;
    spr[(UnitState)renderNum].Render(ri);

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
