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

	if (obj->Move(deltaTime))
	{
		obj->SetState(EnemyMove::GetInstance());
		return;
	}

	if (obj->CheckRange(obj->detectionRange, obj->GetDistanceFromTarget(nowScene->player->pos)))
	{
		obj->SetState(EnemyAttack::GetInstance());
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
	if (obj->hit)
	{
		obj->SetState(EnemyHit::GetInstance());
		return;
	}

	if (!obj->Move(deltaTime))
	{
		obj->SetState(EnemyIdle::GetInstance());
		return;
	}

	if (obj->CheckRange(obj->detectionRange, obj->GetDistanceFromTarget(nowScene->player->pos)))
	{
		obj->SetState(EnemyAttack::GetInstance());
		return;
	}
}

void EnemyMove::ExitState(CEnemy* obj)
{
}


EnemyAttack* EnemyAttack::GetInstance()
{
	static EnemyAttack instance;
	return &instance;
}

void EnemyAttack::EnterState(CEnemy* obj)
{
	obj->SetAni(CEnemy::Images::ATTACK);
} 

void EnemyAttack::UpdateState(CEnemy* obj, float deltaTime)
{
	obj->Attack(deltaTime);

	if (obj->hit)
	{
		obj->SetState(EnemyHit::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(EnemyIdle::GetInstance());
		return;
	}
}

void EnemyAttack::ExitState(CEnemy* obj)
{
	obj->attackTimer = 0.0f;
	obj->onAttack = false;
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


EnemyDie* EnemyDie::GetInstance()
{
	static EnemyDie instance;
	return &instance;
}

void EnemyDie::EnterState(CEnemy* obj)
{
}

void EnemyDie::UpdateState(CEnemy* obj, float deltaTime)
{
}

void EnemyDie::ExitState(CEnemy* obj)
{
}
