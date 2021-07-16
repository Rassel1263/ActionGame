#include "DXUT.h"
#include "Boss.h"

BossIdle* BossIdle::instance = new BossIdle;
BossBack* BossBack::instance = new BossBack;
BossWalk* BossWalk::instance = new BossWalk;
BossDash* BossDash::instance = new BossDash;
BossLAttack* BossLAttack::instance = new BossLAttack;
BossHAttack* BossHAttack::instance = new BossHAttack;
BossHit* BossHit::instance = new BossHit;
BossDie* BossDie::instance = new BossDie;


Boss::Boss(D3DXVECTOR2 pos) : Units(pos)
{
	spr[UnitState::IDLE].LoadAll(L"Assets/Sprites/Units/Boss/Idle");
	spr[UnitState::DOWN].LoadAll(L"Assets/Sprites/Units/Boss/Back", 0.1f, false);
	spr[UnitState::WALK].LoadAll(L"Assets/Sprites/Units/Boss/WALK");
	spr[UnitState::JUMP].LoadAll(L"Assets/Sprites/Units/Boss/Dash", 0.1f, false);
	spr[UnitState::LATTACK].LoadAll(L"Assets/Sprites/Units/Boss/LAttack", 0.1f, false);
	spr[UnitState::HATTACK].LoadAll(L"Assets/Sprites/Units/Boss/HAttack", 0.1f, false);
	spr[UnitState::HIT].LoadAll(L"Assets/Sprites/Units/Boss/Hit", 0.08f, false);
	spr[UnitState::DIE].LoadAll(L"Assets/Sprites/Units/Boss/Die", 0.1f, false);

	BossIdle::instance->EnterState(this);

	renderer = UnitState::IDLE;

	tag = L"boss";

	SetAbility(100, 100, 10, 1);
	SetCollider(-30, -50, 30, 50);

	enemyRange = new EnemyRange(this, D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50));
	nowScene->obm.AddObject(enemyRange);
}

void Boss::Update(float deltaTime)
{
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Units::Update(deltaTime);
}

void Boss::Render()
{
	Units::Render();
}

bool Boss::Move(float deltaTime)
{
	D3DXVECTOR2 distanceVec = nowScene->player->pos - pos;

	if (distanceVec.x < 0)
		ri.scale.x = 1;
	else
		ri.scale.x = -1;

	float distance = pow(distanceVec.x, 2) + pow(distanceVec.y, 2);
	D3DXVec2Normalize(&distanceVec, &distanceVec);

	if (!enemyRange->findTarget)
	{
		pos.x += distanceVec.x * ability.speed * deltaTime;
		pos.y += distanceVec.y * ability.speed * deltaTime / 2;
		z += distanceVec.y * ability.speed * deltaTime / 2;

		return true;
	}

	return false;
}
