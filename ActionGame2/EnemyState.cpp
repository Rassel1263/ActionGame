#include "DXUT.h"
#include "EnemyState.h"

EnemyIdle* EnemyIdle::GetInstance()
{
	static EnemyIdle instance;
	return &instance;
}

void EnemyIdle::EnterState(CEnemy* obj)
{
	obj->SetAni(CEnemy::Images::IDLE);
}

void EnemyIdle::UpdateState(CEnemy* obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(EnemyHit::GetInstance());
		return;
	}
}

void EnemyIdle::ExitState(CEnemy* obj)
{
}

EnemyMove* EnemyMove::GetInstance()
{
	static EnemyMove instance;
	return &instance;
}

void EnemyMove::EnterState(CEnemy* obj)
{
	obj->SetAni(CEnemy::Images::MOVE);
}

void EnemyMove::UpdateState(CEnemy* obj, float deltaTime)
{
}

void EnemyMove::ExitState(CEnemy* obj)
{
}

EnemyHit* EnemyHit::GetInstance()
{
	static EnemyHit instance;
	return &instance;
}

void EnemyHit::EnterState(CEnemy* obj)
{
	obj->SetAni(CEnemy::Images::HIT);
	obj->ability.hp -= obj->hitDamage;
}

void EnemyHit::UpdateState(CEnemy* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(EnemyIdle::GetInstance());
		return;
	}
}

void EnemyHit::ExitState(CEnemy* obj)
{
	obj->hit = false;
}
