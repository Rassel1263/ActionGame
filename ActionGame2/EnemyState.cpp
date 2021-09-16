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
	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(EnemyHit::GetInstance());
		return;
	}

	if (obj->Move(deltaTime))
	{
		obj->SetState(EnemyMove::GetInstance());
		return;
	}

	obj->restTimer += deltaTime;
	if (obj->restTimer >= obj->restTime)
	{
		if (obj->AttackColliderTarget())
		{
			if (obj->enemyType != 4)
				obj->SetState(EnemyAttack::GetInstance());
			else
				obj->SetState(EnemyAttackReady::GetInstance());
			return;
		}
	}
}

void EnemyIdle::ExitState(CEnemy* obj)
{
	obj->restTimer = 0.0f;
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
	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(EnemyHit::GetInstance());
		return;
	}


	if (!obj->Move(deltaTime))
	{
		obj->SetState(EnemyIdle::GetInstance());
		return;
	}

	obj->restTimer += deltaTime;
	if (obj->restTimer >= obj->restTime)
	{
		if (obj->AttackColliderTarget())
		{
			if (obj->enemyType != 4)
				obj->SetState(EnemyAttack::GetInstance());
			else
				obj->SetState(EnemyAttackReady::GetInstance());
			return;
		}
	}
}

void EnemyMove::ExitState(CEnemy* obj)
{
}

EnemyAttackReady* EnemyAttackReady::GetInstance()
{
	static EnemyAttackReady instance;
	return &instance;
}

void EnemyAttackReady::EnterState(CEnemy* obj)
{
	obj->SetAni(CEnemy::Images::ATTACKREADY);
	nowScene->obm.AddObject(new Effect(L"Enemy/Warning", D3DXVECTOR2(obj->pos.x, obj->groundPos), D3DXVECTOR2(obj->ri.scale.x, 1), D3DXVECTOR2(0, 0.5), 0.062f));
	obj->superArmor = true;
}

void EnemyAttackReady::UpdateState(CEnemy* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(EnemyDie::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(EnemyAttack::GetInstance());
		return;
	}
}

void EnemyAttackReady::ExitState(CEnemy* obj)
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

	if (obj->ability.hp <= 0)
	{
		obj->SetState(EnemyDie::GetInstance());
		return;
	}

	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(EnemyHit::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		if (obj->enemyType != 4)
			obj->SetState(EnemyIdle::GetInstance());
		else
			obj->SetState(EnemyAttackEnd::GetInstance());

		return;
	}
}

void EnemyAttack::ExitState(CEnemy* obj)
{
	obj->attackTimer = 0.0f;
	obj->superArmor = false;
	obj->onAttack = false;
	obj->attackRange->bHit = false;
	obj->detectRange->bHit = false;
}

EnemyAttackEnd* EnemyAttackEnd::GetInstance()
{
	static EnemyAttackEnd instance;
	return &instance;
}

void EnemyAttackEnd::EnterState(CEnemy* obj)
{
	obj->SetAni(CEnemy::Images::ATTACKEND);
}

void EnemyAttackEnd::UpdateState(CEnemy* obj, float deltaTime)
{
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

void EnemyAttackEnd::ExitState(CEnemy* obj)
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
}

void EnemyHit::UpdateState(CEnemy* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(EnemyDie::GetInstance());
		return;
	}

	if (abs(obj->velocity.y) > 0.0f)
	{
		obj->SetState(EnemyStun::GetInstance());
		return;
	}

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


EnemyStun* EnemyStun::GetInstance()
{
	static EnemyStun instance;
	return &instance;
}

void EnemyStun::EnterState(CEnemy* obj)
{
	obj->SetAni(CEnemy::Images::STUN);
}

void EnemyStun::UpdateState(CEnemy* obj, float deltaTime)
{
	if (obj->hit)
	{
		obj->SetState(EnemyStun::GetInstance());
		return;
	}

	if (obj->bGround)
	{
		obj->SetState(EnemyIdle::GetInstance());
		return;
	}
}

void EnemyStun::ExitState(CEnemy* obj)
{
}


EnemyDie* EnemyDie::GetInstance()
{
	static EnemyDie instance;
	return &instance;
}

void EnemyDie::EnterState(CEnemy* obj)
{
	obj->SetAni(CEnemy::Images::DIE);
	obj->bCollider = false;
}

void EnemyDie::UpdateState(CEnemy* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		if (!obj->Blink(deltaTime, 5))
			obj->Destroy();
	}
}

void EnemyDie::ExitState(CEnemy* obj)
{
}
