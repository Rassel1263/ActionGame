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
	if (obj->Move(deltaTime))
	{
		EnemyWalk::instance->EnterState(obj);
		return;
	}

	if (obj->enemyRange->findTarget)
	{
		EnemyAttack::instance->EnterState(obj);
		return;
	}

	if (obj->ability.hp <= 0)
	{
		EnemyDie::instance->EnterState(obj);
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

	randNum = rand() % 5;
}

void EnemyWalk::UpdateState(Enemy* obj, float deltaTime)
{
	if (obj->type == EnemyType::Bind)
	{
		if (obj->enemyRange->findTarget && randNum == 1)
		{
			EnemySAttack::instance->EnterState(obj);
			return;
		}
	}

	if (obj->enemyRange->findTarget)
	{
		EnemyAttack::instance->EnterState(obj);
		return;
	}

	if (obj->type == EnemyType::Range)
	{
		if (obj->CheckDistance(250))
		{
			EnemySAttack::instance->EnterState(obj);
			return;
		}
	}


	if (!obj->Move(deltaTime))
	{
		EnemyIdle::instance->EnterState(obj);
		return;
	}

	if (obj->ability.hp <= 0)
	{
		EnemyDie::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		EnemyHit::instance->EnterState(obj);
		return;
	}
}

void EnemyWalk::ExitState(Enemy* obj)
{
	randNum = 0;
}

void EnemyAttack::EnterState(Enemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::LATTACK;
	obj->spr[obj->renderer].Reset();

	switch (obj->type)
	{
	case EnemyType::Speedy:
		obj->SetAttackInfo(D3DXVECTOR2(40 * -obj->ri.scale.x, 30), D3DXVECTOR2(-1, 0), 300 ,5, 2);
		break;
	case EnemyType::Power:
		obj->SetAttackInfo(D3DXVECTOR2(80 * -obj->ri.scale.x, 30), D3DXVECTOR2(-1, 0), 600 ,7, 3);
		break;
	case EnemyType::Bind:
		obj->SetAttackInfo(D3DXVECTOR2(60 * -obj->ri.scale.x, 30), D3DXVECTOR2(-1, 0), 400, 5, 1);
		break;
	}
	//obj->Attack(D3DXVECTOR2(20 * -obj->ri.scale.x, -30), D3DXVECTOR2(-1, 0));
}

void EnemyAttack::UpdateState(Enemy* obj, float deltaTime)
{
	if (obj->aniTimer <= 0.0f)
	{
		obj->Attack();
		obj->aniTimer = 999.0f;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		EnemyIdle::instance->EnterState(obj);
		return;
	}

	if (obj->ability.hp <= 0)
	{
		EnemyDie::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		EnemyHit::instance->EnterState(obj);
		return;
	}

	obj->aniTimer -= deltaTime;
}

void EnemyAttack::ExitState(Enemy* obj)
{
}

void EnemySAttack::EnterState(Enemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::LSATTACK1;
	obj->spr[obj->renderer].Reset();

	if (obj->type == EnemyType::Bind)
	{
		obj->velocity.x = 700 * -obj->ri.scale.x;
		obj->velocity.y = 500;
	}
}

void EnemySAttack::UpdateState(Enemy* obj, float deltaTime)
{
	if (obj->type == EnemyType::Bind)
	{
		if (nowScene->player->bind)
		{
			timer += deltaTime;

			if (timer >= 2.0f)
			{
				obj->velocity.x = 700 * obj->ri.scale.x;
				EnemyIdle::instance->EnterState(obj);
				return;
			}
		}
		// ?????? ???? ?????????? ?????? ??????????????????
		if (obj->CheckDistance(30) && !nowScene->player->bind && !nowScene->player->invincibility)
		{
			obj->pos = nowScene->player->pos + D3DXVECTOR2(30 * obj->ri.scale.x, 50);
			obj->bRigid = false;
			nowScene->player->bind = true;
		}

		if (obj->bGround)
		{
			EnemyIdle::instance->EnterState(obj);
			return;
		}
	}

	if (obj->type == EnemyType::Range)
	{
		timer += deltaTime;

		if (timer >= obj->spr[obj->renderer].aniMaxTime * 8)
		{
			nowScene->obm.AddObject(new FireBall(L"Enemy", obj->pos + D3DXVECTOR2(-obj->ri.scale.x * 40, 20), -obj->ri.scale, 10, obj->z));
			timer = 0.0f;
		}

		if (!obj->spr[obj->renderer].bAnimation)
		{
			EnemyIdle::instance->EnterState(obj);
			return;
		}
	}

	if (obj->bHit)
	{
		EnemyHit::instance->EnterState(obj);
		return;
	}
}

void EnemySAttack::ExitState(Enemy* obj)
{
	timer = 0.0f;
	obj->bRigid = true;
	nowScene->player->bind = false;
}


void EnemyHit::EnterState(Enemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::HIT;
	obj->spr[obj->renderer].Reset();

	nowScene->player->PlusSpecialGaze(obj->damage / 2);
	obj->ability.hp -= obj->damage;
}

void EnemyHit::UpdateState(Enemy* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		EnemyDie::instance->EnterState(obj);
		return;
	}

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

void EnemyDie::EnterState(Enemy* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::DIE;
	obj->spr[obj->renderer].Reset();
}

void EnemyDie::UpdateState(Enemy* obj, float deltaTime)
{
	if (!obj->spr[obj->renderer].bAnimation)
	{
		switch (obj->type)
		{
		case EnemyType::Speedy:
			nowScene->GetScore(1000 * (1 + abs(obj->ability.hp)));
			break;
		case EnemyType::Power:
			nowScene->GetScore(1500 * (1 + abs(obj->ability.hp)));
			break;
		case EnemyType::Bind:
			nowScene->GetScore(2000 * (1 + abs(obj->ability.hp)));
			break;
		case EnemyType::Range:
			nowScene->GetScore(3000);
			break;
		}

		if (nowScene->player->target == obj)
			nowScene->player->target = NULL;

		obj->destroy = true;
		return;
	}
}

void EnemyDie::ExitState(Enemy* obj)
{
}
