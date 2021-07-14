#include "DXUT.h"
#include "Enemy.h"

EnemyIdle* EnemyIdle::instance = new EnemyIdle;
EnemyWalk* EnemyWalk::instance = new EnemyWalk;
EnemyAttack* EnemyAttack::instance = new EnemyAttack;
EnemyHit* EnemyHit::instance = new EnemyHit;


Enemy::Enemy(D3DXVECTOR2 pos, EnemyType type) : Units(pos)
{
	SetInfo();

	EnemyIdle::instance->EnterState(this);
	renderer = UnitState::IDLE;

	tag = L"enemy";

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
	if (CheckPlayer(500))
	{
		D3DXVECTOR2 distanceVec = nowScene->player->pos - pos;

		if (distanceVec.x < 0)
			ri.scale.x = 1;
		else
			ri.scale.x = -1;

		float distance = pow(distanceVec.x, 2) + pow(distanceVec.y, 2);
		D3DXVec2Normalize(&distanceVec, &distanceVec);

		pos.x += distanceVec.x * ability.speed * deltaTime;
		pos.y += distanceVec.y * ability.speed * deltaTime / 2;

		return true;
	}

	return false;
}

void Enemy::SetInfo()
{
	int index = (int)type;

	switch (type)
	{
	case EnemyType::Speedy:
		SetAbility(5, 200, 10, 0.5f);
		SetCollider(-30, -50, 30, 50);
		break;
	case EnemyType::Power:
		break;
	case EnemyType::Range:
		break;
	case EnemyType::Bind:
		break;
	}

	spr[UnitState::IDLE].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Idle");
	spr[UnitState::WALK].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Walk");
	spr[UnitState::LATTACK].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Attack", 0.1f, false);
	spr[UnitState::HIT].LoadAll(L"Assets/Sprites/Units/Enemy/" + std::to_wstring(index) + L"/Hit", 0.1f, false);
}

bool Enemy::CheckPlayer(float distance)
{
	D3DXVECTOR2 distanceVec = nowScene->player->pos - pos;
	float dis = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));

	if (dis < distance) return true;

	return false;
}
