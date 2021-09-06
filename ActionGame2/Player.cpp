#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	groundPos = -100;

	Resize(Images::END);

	GetSprite(Images::IDLE).LoadAll(L"Assets/Sprites/Unit/Player/stay", 0.05f);
	GetSprite(Images::MOVE).LoadAll(L"Assets/Sprites/Unit/Player/move", 0.05f);
	GetSprite(Images::JUMP).LoadAll(L"Assets/Sprites/Unit/Player/jump", 0.05f, false);
	GetSprite(Images::SHADOW).LoadAll(L"Assets/Sprites/effect/Player/shadow");

	GetSprite(Images::GUNKATA).LoadAll(L"Assets/Sprites/Unit/Player/Skillgunkata", 0.04f, false);

	ability.SetAbility(100, 50);

	SetState(PlayerIdle::GetInstance());
}

void Player::Update(float deltaTime)
{
	Camera::GetInstance().destCameraPos.x = pos.x;

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Unit::Update(deltaTime);
}

void Player::Render()
{
	GetSprite(Images::SHADOW).Render(RenderInfo{ D3DXVECTOR2(ri.pos.x, ri.pos.y) });
	Unit::Render();
}

void Player::SetState(CState<Player>* nextState)
{
	if (nowState)
		nowState->ExitState(this);

	nowState = nextState;
	nowState->EnterState(this);
}

void Player::SetAni(Images nextState)
{
	renderNum = IntEnum(nextState);
	GetNowSprite().Reset();
}

bool Player::Move(float deltaTime)
{
	D3DXVECTOR2 moveDir = { 0, 0 };

	if (Input::GetInstance().KeyPress(VK_RIGHT))
		moveDir.x = 1;

	if (Input::GetInstance().KeyPress(VK_LEFT))
		moveDir.x = -1;

	if (Input::GetInstance().KeyPress(VK_UP))
		moveDir.y = 1;

	if (Input::GetInstance().KeyPress(VK_DOWN))
		moveDir.y = -1;

	if(moveDir.x != 0)
		ri.scale.x = moveDir.x;
	if (moveDir == D3DXVECTOR2(0, 0))
		return false;

	pos.x += moveDir.x * deltaTime * 500;
	groundPos += moveDir.y * deltaTime * 250;


	return true;
}
