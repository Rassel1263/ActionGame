#include "DXUT.h"
#include "BossState.h"

void BossIdle::EnterState(Boss* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderer = UnitState::IDLE;

	pattern = rand() % 2;
}

void BossIdle::UpdateState(Boss* obj, float deltaTime)
{
	if (restTime <= 0.0f)
	{
		switch (pattern)
		{
		case 0:
			if (obj->Move(deltaTime))
			{
				BossWalk::instance->EnterState(obj);
				return;
			}
			break;
		case 1:
			if (!obj->CheckDistance(100))
			{
				BossDash::instance->EnterState(obj);
				return;
			}
			else
				pattern = 1;
		}
	}

	if (obj->bHit)
	{
		BossHit::instance->EnterState(obj);
		return;
	}

	restTime -= deltaTime;
}

void BossIdle::ExitState(Boss* obj)
{
	restTime = 0.3f;
}

void BossBack::EnterState(Boss* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::DOWN;
	obj->spr[obj->renderer].Reset();

	obj->velocity.y = 100;
	obj->velocity.x = 800 * obj->ri.scale.x;
}

void BossBack::UpdateState(Boss* obj, float deltaTime)
{
	if (!obj->spr[obj->renderer].bAnimation)
	{
		BossIdle::instance->EnterState(obj);
		return;
	}

	if (eftTimer >= 0.02f)
	{
		nowScene->obm.AddObject(new Spectrum(obj->spr[obj->renderer], obj->pos, obj->ri.scale, 0.2f));
		eftTimer = 0.0f;
	}

	eftTimer += deltaTime;
}

void BossBack::ExitState(Boss* obj)
{
	eftTimer = 0.0f;
}

void BossWalk::EnterState(Boss* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderer = UnitState::WALK;
}

void BossWalk::UpdateState(Boss* obj, float deltaTime)
{
	if (!obj->Move(deltaTime))
	{
		BossLAttack::instance->EnterState(obj);
		return;
	}
}

void BossWalk::ExitState(Boss* obj)
{

}

void BossDash::EnterState(Boss* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderer = UnitState::JUMP;

	obj->spr[obj->renderer].Reset();
	obj->ability.speed = 400;
}

void BossDash::UpdateState(Boss* obj, float deltaTime)
{
	if (!obj->Move(deltaTime))
	{
		BossHAttack::instance->EnterState(obj);
		return;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		BossIdle::instance->EnterState(obj);
		return;
	}

	if (eftTimer >= 0.02f)
	{
		nowScene->obm.AddObject(new Spectrum(obj->spr[obj->renderer], obj->pos, obj->ri.scale, 0.2f));
		eftTimer = 0.0f;
	}

	eftTimer += deltaTime;
}

void BossDash::ExitState(Boss* obj)
{
	obj->ability.speed = 150;
	eftTimer = 0.0f;
}

void BossLAttack::EnterState(Boss* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderer = UnitState::LATTACK;
	obj->spr[obj->renderer].Reset();

	obj->SetAttackInfo(D3DXVECTOR2(60 * -obj->ri.scale.x, 30), D3DXVECTOR2(-1, 0.3), 5, 3);
}

void BossLAttack::UpdateState(Boss* obj, float deltaTime)
{
	if (obj->aniTimer <= 0.0f)
	{
		obj->Attack();
		obj->aniTimer = 999.0f;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		BossIdle::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		BossHit::instance->EnterState(obj);
		return;
	}

	obj->aniTimer -= deltaTime;
}

void BossLAttack::ExitState(Boss* obj)
{
}

void BossHAttack::EnterState(Boss* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderer = UnitState::HATTACK;
	obj->spr[obj->renderer].Reset();

	obj->SetAttackInfo(D3DXVECTOR2(60 * -obj->ri.scale.x, 30), D3DXVECTOR2(-1, 0.3), 10, 3);
}

void BossHAttack::UpdateState(Boss* obj, float deltaTime)
{
	if (obj->aniTimer <= 0.0f)
	{
		obj->Attack();
		obj->aniTimer = 999.0f;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		BossIdle::instance->EnterState(obj);
		return;
	}

	obj->aniTimer -= deltaTime;
}

void BossHAttack::ExitState(Boss* obj)
{
}

void BossHit::EnterState(Boss* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	miss = rand() % 4;

	obj->renderer = UnitState::HIT;
	obj->spr[obj->renderer].Reset();
}

void BossHit::UpdateState(Boss* obj, float deltaTime)
{
	if (!miss)
	{
		BossBack::instance->EnterState(obj);
		return;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		BossIdle::instance->EnterState(obj);
		return;
	}
}

void BossHit::ExitState(Boss* obj)
{
	obj->bHit = false;
}

void BossDie::EnterState(Boss* obj)
{
}

void BossDie::UpdateState(Boss* obj, float deltaTime)
{
}

void BossDie::ExitState(Boss* obj)
{
}

