#include "DXUT.h"
#include "Enemy.h"

EnemyIdle* EnemyIdle::instance = new EnemyIdle;
EnemyWalk* EnemyWalk::instance = new EnemyWalk;
EnemyAttack* EnemyAttack::instance = new EnemyAttack;
EnemySAttack* EnemySAttack::instance = new EnemySAttack;
EnemyHit* EnemyHit::instance = new EnemyHit;
EnemyDie* EnemyDie::instance = new EnemyDie;


Enemy::Enemy(D3DXVECTOR2 pos, EnemyType type) : Units(pos)
{
	this->type = type;
	this->z = pos.y;
	tag = L"enemy";

	SetInfo();

	EnemyIdle::instance->EnterState(this);
	renderer = UnitState::IDLE;

	ri.scale.x = -ri.scale.x;
}

void Enemy::Update(float deltaTime)
{
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Units::Update(deltaTime);
}

void Enemy::Render()
{
	Units::Render();
}

bool Enemy::Move(float deltaTime)
{
	if (CheckDistance(400))
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
	}

	return false;
}

void Enemy::SetInfo()
{
	int index = (int)type;

	switch (type)
	{
	case EnemyType::Speedy:
		SetAbility(50, 200, 10, 0.5f);
		SetCollider(-30, -50, 30, 50);
		SetAttackRange({ -50, -50 }, { 50, 50 });
		break;
	case EnemyType::Power:
		SetAbility(100, 100, 20, 0.2f);
		SetCollider(-50, -50, 50, 50);
		SetAttackRange({ -50, -50 }, { 50, 50 });
		break;
	case EnemyType::Bind:
		SetAbility(50, 200, 10, 0.3f);
		SetCollider(-50, -50, 50, 50);
		SetAttackRange({ -50, -50 }, { 50, 50 });
		break;
	case EnemyType::Range:
		break;
	}

	spr[UnitState::IDLE].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Idle");
	spr[UnitState::WALK].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Walk");
	spr[UnitState::LATTACK].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Attack", ability.atkSpeed, false);
	spr[UnitState::LSATTACK1].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/SpecialAttack", 0.2f, false);
	spr[UnitState::HIT].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Hit", 0.1f, false);
	spr[UnitState::DIE].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Die", 0.1f, false);
}

void Enemy::SetAttackRange(D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	enemyRange = new EnemyRange(this, min, max);
	nowScene->obm.AddObject(enemyRange);
}

