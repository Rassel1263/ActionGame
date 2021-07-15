#include "DXUT.h"
#include "PlayerState.h"

void PlayerIdle::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderer = UnitState::IDLE;
}

void PlayerIdle::UpdateState(Player* obj, float deltaTime)
{
	if (Input::GetInstance().KeyDown('Z'))
	{
		if (obj->SpecialIndex() != -1)
			PlayerLSAttack::instance->EnterState(obj);
		else
			PlayerLAttack::instance->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		if (obj->SpecialIndex() != -1)
			PlayerHSAttack::instance->EnterState(obj);
		else
			PlayerHAttack::instance->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyDown('S'))
	{
		PlayerJump::instance->EnterState(obj);
		return;
	}

	if (obj->Move(deltaTime))
	{
		PlayerWalk::instance->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyDown('D'))
	{
		PlayerDown::instance->EnterState(obj);
		return;
	}

	if (obj->bind)
	{
		PlayerBind::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		PlayerHit::instance->EnterState(obj);
		return;
	}
}

void PlayerIdle::ExitState(Player* obj)
{

}

void PlayerDown::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::DOWN;
}

void PlayerDown::UpdateState(Player* obj, float deltaTime)
{
	if (Input::GetInstance().KeyUp('D'))
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
}

void PlayerDown::ExitState(Player* obj)
{
}


void PlayerWalk::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::WALK;

	if (obj->SpecialIndex() == 0 && obj->specialGaze >= 30)
	{
		obj->specialGaze -= 30;
		obj->velocity.x = 1500 * obj->ri.scale.x;
	}
}

void PlayerWalk::UpdateState(Player* obj, float deltaTime)
{
	if (Input::GetInstance().KeyDown('Z'))
	{
		if (obj->SpecialIndex() != -1)
			PlayerLSAttack::instance->EnterState(obj);
		else
			PlayerLAttack::instance->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		if (obj->SpecialIndex() != -1)
			PlayerHSAttack::instance->EnterState(obj);
		else
			PlayerHAttack::instance->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyDown('S'))
	{
		PlayerJump::instance->EnterState(obj);
		return;
	}

	if (!obj->Move(deltaTime))
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyDown('D'))
	{
		PlayerDown::instance->EnterState(obj);
		return;
	}

	if (obj->bind)
	{
		PlayerBind::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		PlayerHit::instance->EnterState(obj);
		return;
	}

	
}

void PlayerWalk::ExitState(Player* obj)
{
}

void PlayerJump::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::JUMP;
	obj->spr[obj->renderer].Reset();

	obj->velocity.y = 800;
}

void PlayerJump::UpdateState(Player* obj, float deltaTime)
{
	if (obj->velocity.y > 0)
	{
		PlayerFall::instance->EnterState(obj);
		return;
	}

	if (obj->bGround)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}

	obj->Move(deltaTime);
}

void PlayerJump::ExitState(Player* obj)
{
}


void PlayerFall::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::FALL;
	obj->spr[obj->renderer].Reset();
}

void PlayerFall::UpdateState(Player* obj, float deltaTime)
{
	if (obj->bGround)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}

	obj->Move(deltaTime);
}

void PlayerFall::ExitState(Player* obj)
{
}


void PlayerLAttack::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::LATTACK;
	obj->spr[obj->renderer].Reset();

	obj->SetAttackInfo(D3DXVECTOR2(obj->ri.scale.x * 50, 40), { 1, 0 }, 5, 1);
}

void PlayerLAttack::UpdateState(Player* obj, float deltaTime)
{
	if (obj->aniTimer <= 0.0f)
	{
		obj->Attack();
		obj->aniTimer = 999.0f;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}

	if (obj->bind)
	{
		PlayerBind::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		PlayerHit::instance->EnterState(obj);
		return;
	}

	obj->aniTimer -= deltaTime;
}

void PlayerLAttack::ExitState(Player* obj)
{
}

void PlayerHAttack::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::HATTACK;
	obj->spr[obj->renderer].Reset();

	obj->SetAttackInfo(D3DXVECTOR2(obj->ri.scale.x * 50, 40), { 1, -0.2 }, 6, 4);
}

void PlayerHAttack::UpdateState(Player* obj, float deltaTime)
{
	if (obj->aniTimer <= 0.0f)
	{
		obj->Attack();
		obj->aniTimer = 999.0f;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}

	if (obj->bind)
	{
		PlayerBind::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		PlayerHit::instance->EnterState(obj);
		return;
	}

	obj->aniTimer -= deltaTime;
}

void PlayerHAttack::ExitState(Player* obj)
{
}

void PlayerLSAttack::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	switch (obj->specialIndex)
	{
	case 0:
		if (obj->specialGaze >= 10)
		{
			bAttack = true;
			obj->specialGaze -= 10;
			obj->renderer = UnitState::LSATTACK1;
			obj->SetAttackInfo(D3DXVECTOR2(obj->ri.scale.x * 50, 10), { 1, 0 }, 6, 3);
		}
		break;
	case 1:
		if (obj->specialGaze >= 20)
		{
			bAttack = true;
			obj->specialGaze -= 20;
			obj->renderer = UnitState::LSATTACK2;
			break;
		}
	}
	obj->spr[obj->renderer].Reset();
}

void PlayerLSAttack::UpdateState(Player* obj, float deltaTime)
{
	if (obj->aniTimer <= 0.0f)
	{
		obj->Attack();
		obj->aniTimer = 999.0f;
	}

	if (!obj->spr[obj->renderer].bAnimation || !bAttack)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}

	if (obj->bind)
	{
		PlayerBind::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		PlayerHit::instance->EnterState(obj);
		return;
	}

	obj->aniTimer -= deltaTime;
}

void PlayerLSAttack::ExitState(Player* obj)
{
	bAttack = false;
	obj->specialIndex = -1;
}

void PlayerHSAttack::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	switch (obj->specialIndex)
	{
	case 0:
		if (obj->specialGaze >= 25)
		{
			bAttack = true;
			obj->specialGaze -= 25;
			obj->renderer = UnitState::HSATTACK1;
			obj->SetAttackInfo(D3DXVECTOR2(obj->ri.scale.x * 60, 10), { 1, 0.2 }, 7, 7);
		}
		break;
	case 1:
		if (obj->specialGaze >= 35)
		{
			bAttack = true;
			obj->specialGaze -= 35;
			obj->renderer = UnitState::HSATTACK2;
		}
		break;
	}

	obj->spr[obj->renderer].Reset();
}

void PlayerHSAttack::UpdateState(Player* obj, float deltaTime)
{
	if (obj->aniTimer <= 0.0f)
	{
		obj->Attack();
		obj->aniTimer = 999.0f;
	}

	if (!obj->spr[obj->renderer].bAnimation && !bAttack)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}

	if (obj->bind)
	{
		PlayerBind::instance->EnterState(obj);
		return;
	}

	if (obj->bHit)
	{
		PlayerHit::instance->EnterState(obj);
		return;
	}

	obj->aniTimer -= deltaTime;
}

void PlayerHSAttack::ExitState(Player* obj)
{
	bAttack = true;
	obj->specialIndex = -1;
}

void PlayerBind::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::BIND;
	obj->spr[obj->renderer].Reset();
}

void PlayerBind::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->bind)
	{
		PlayerHit::instance->EnterState(obj);
		return;
	}
}

void PlayerBind::ExitState(Player* obj)
{
}


void PlayerHit::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::HIT;
	obj->spr[obj->renderer].Reset();

	obj->ability.hp--;
}

void PlayerHit::UpdateState(Player* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		PlayerDie::instance->EnterState(obj);
		return;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
}

void PlayerHit::ExitState(Player* obj)
{
	obj->bHit = false;
}

void PlayerDie::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::DIE;
	obj->spr[obj->renderer].Reset();
}

void PlayerDie::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->spr[obj->renderer].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
}

void PlayerDie::ExitState(Player* obj)
{
	obj->ability.hp = 5;
	obj->bHit = false;
}

