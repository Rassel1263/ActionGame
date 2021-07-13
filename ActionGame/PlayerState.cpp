#include "DXUT.h"
#include "PlayerState.h"

void PlayerIdle::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderNum = 0;
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

	obj->renderNum = 1;
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

	obj->renderNum = 2;
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

	obj->renderNum = 3;
	obj->spr[(UnitState)obj->renderNum].Reset();

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

	obj->renderNum = 4;
	obj->spr[(UnitState)obj->renderNum].Reset();
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

	obj->renderNum = 5;
	obj->spr[(UnitState)obj->renderNum].Reset();
}

void PlayerLAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->spr[(UnitState)obj->renderNum].bAnimation)
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

	obj->renderNum = 6;
	obj->spr[(UnitState)obj->renderNum].Reset();
}

void PlayerHAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->spr[(UnitState)obj->renderNum].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
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
		obj->renderNum = 7;
		break;
	case 1:
		obj->renderNum = 8;
		break;
	}
	obj->spr[(UnitState)obj->renderNum].Reset();
}

void PlayerLSAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->spr[(UnitState)obj->renderNum].bAnimation)
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
		obj->renderNum = 9;
		break;
	case 1:
		obj->renderNum = 10;
		break;
	}

	obj->spr[(UnitState)obj->renderNum].Reset();
}

void PlayerHSAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->spr[(UnitState)obj->renderNum].bAnimation)
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
}

void PlayerHSAttack::ExitState(Player* obj)
{
	obj->specialIndex = -1;
}
