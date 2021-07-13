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
	if (obj->Move(deltaTime))
	{
		PlayerWalk::instance->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyDown(VK_DOWN))
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
	if (Input::GetInstance().KeyUp(VK_DOWN))
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
	if (!obj->Move(deltaTime))
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
}

void PlayerWalk::ExitState(Player* obj)
{
}
