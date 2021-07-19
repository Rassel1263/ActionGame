#include "DXUT.h"
#include "Boss2.h"

Boss2::Boss2(D3DXVECTOR2 pos) : Boss(pos)
{
	bossIndex = 2;

	spr[UnitState::IDLE].LoadAll(L"Assets/Sprites/Units/Boss2/Idle");
	spr[UnitState::DOWN].LoadAll(L"Assets/Sprites/Units/Boss2/Back", 0.02f, false);
	spr[UnitState::WALK].LoadAll(L"Assets/Sprites/Units/Boss2/WALK");
	spr[UnitState::JUMP].LoadAll(L"Assets/Sprites/Units/Boss2/Dash", 0.1f, false);
	spr[UnitState::LATTACK].LoadAll(L"Assets/Sprites/Units/Boss2/LAttack", 0.1f, false);
	spr[UnitState::LSATTACK1].LoadAll(L"Assets/Sprites/Units/Boss2/LSAttack", 0.05f, false);
	spr[UnitState::HATTACK].LoadAll(L"Assets/Sprites/Units/Boss2/HAttack", 0.1f, false);
	spr[UnitState::HSATTACK1].LoadAll(L"Assets/Sprites/Units/Boss2/HSAttack", 0.1f, false);
	spr[UnitState::HIT].LoadAll(L"Assets/Sprites/Units/Boss2/Hit", 0.08f, false);
	spr[UnitState::DIE].LoadAll(L"Assets/Sprites/Units/Boss2/Die", 0.1f, false);
}

void Boss2::Update(float deltaTime)
{
	Boss::Update(deltaTime);
}

void Boss2::Render()
{
	Boss::Render();
}
