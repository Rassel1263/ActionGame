#include "DXUT.h"
#include "Player.h"

PlayerIdle* PlayerIdle::instance = new PlayerIdle;
PlayerDown* PlayerDown::instance = new PlayerDown;
PlayerWalk* PlayerWalk::instance = new PlayerWalk;

Player::Player() : Units(D3DXVECTOR2(0, 0))
{
	spr[UnitState::IDLE].LoadAll(L"Assets/Sprites/Units/Player/Idle");
	spr[UnitState::DOWN].LoadAll(L"Assets/Sprites/Units/Player/Down");
	spr[UnitState::WALK].LoadAll(L"Assets/Sprites/Units/Player/Walk");

	PlayerIdle::instance->EnterState(this);

	renderNum = 0;

	SetAbility(5, 300, 1, 1);
}

void Player::Update(float deltaTime)
{
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Units::Update(deltaTime);
}

void Player::Render()
{
	Units::Render();
}

bool Player::Move(float deltaTime)
{
	D3DXVECTOR2 vMove(0, 0);

	if (Input::GetInstance().KeyPress(VK_LEFT))
		vMove.x = -1;
	else if (Input::GetInstance().KeyPress(VK_RIGHT))
		vMove.x = 1;
	else
		return false;

	ri.scale.x = -vMove.x;

	pos += vMove * ability.speed * deltaTime;

	return true;
}
