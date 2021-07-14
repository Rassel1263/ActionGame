#include "DXUT.h"
#include "EnemyState.h"

void EnemyIdle::EnterState(Enemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderer = UnitState::IDLE;
}

void EnemyIdle::UpdateState(Enemy* obj, float deltaTime)
{
	if (obj->CheckPlayer(50))
	{
		EnemyAttack::instance->EnterState(obj);
		return;
	}

	if (obj->Move(deltaTime))
	{
		EnemyWalk::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		EnemyHit::instance->EnterState(obj);
		return;
	}
}

void EnemyIdle::ExitState(Enemy* obj)
{
}

void EnemyWalk::EnterState(Enemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::WALK;
}

void EnemyWalk::UpdateState(Enemy* obj, float deltaTime)
{
	if (!obj->Move(deltaTime))
	{
		EnemyIdle::instance->EnterState(obj);
		return;
	}


	if (obj->CheckPlayer(50))
	{
		EnemyAttack::instance->EnterState(obj);
		return;
	}
}

void EnemyWalk::ExitState(Enemy* obj)
{
}

void EnemyAttack::EnterState(Enemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::LATTACK;
	obj->spr[obj->renderer].Reset();
}

void EnemyAttack::UpdateState(Enemy* obj, float deltaTime)
{
	if (!obj->spr[obj->renderer].bAnimation)
	{
		EnemyIdle::instance->EnterState(obj);
		return;
	}
}

void EnemyAttack::ExitState(Enemy* obj)
{
}

void EnemyHit::EnterState(Enemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::HIT;
	obj->spr[obj->renderer].Reset();

}

void EnemyHit::UpdateState(Enemy* obj, float deltaTime)
{
	if (!obj->spr[obj->renderer].bAnimation)
	{
		EnemyIdle::instance->EnterState(obj);
		return;
	}
}

void EnemyHit::ExitState(Enemy* obj)
{
	obj->bHit = false;
}
