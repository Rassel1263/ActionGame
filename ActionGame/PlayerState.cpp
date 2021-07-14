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

	if (obj->SpecialIndex() == 0)
		obj->velocity.x = 1500 * obj->ri.scale.x;
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

	obj->velocity.y = -800;
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

	obj->ability.atkPower = 500;
	obj->Attack(D3DXVECTOR2(obj->ri.scale.x * 50, -40), D3DXVECTOR2(1, 0));
}

void PlayerLAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->spr[obj->renderer].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}

	//obj->Move(deltaTime);
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

	obj->ability.atkPower = 600;
	obj->aniTimer = obj->spr[obj->renderer].aniMaxTime * 4;
}

void PlayerHAttack::UpdateState(Player* obj, float deltaTime)
{
	if (obj->aniTimer <= 0.0f)
	{
		obj->Attack(D3DXVECTOR2(obj->ri.scale.x * 50, -40), D3DXVECTOR2(1, -0.2));
		obj->aniTimer = 999.0f;
	}

	if (!obj->spr[obj->renderer].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
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
		obj->renderer = UnitState::LSATTACK1;
		break;
	case 1:
		obj->renderer = UnitState::LSATTACK2;
		break;
	}
	obj->spr[obj->renderer].Reset();
}

void PlayerLSAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->spr[obj->renderer].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
}

void PlayerLSAttack::ExitState(Player* obj)
{
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
		obj->renderer = UnitState::HSATTACK1;
		break;
	case 1:
		obj->renderer = UnitState::HSATTACK2;
		break;
	}

	obj->spr[obj->renderer].Reset();
}

void PlayerHSAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->spr[obj->renderer].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
}

void PlayerHSAttack::ExitState(Player* obj)
{
	obj->specialIndex = -1;
}
