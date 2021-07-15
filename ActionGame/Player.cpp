#include "DXUT.h"
#include "Player.h"

PlayerIdle* PlayerIdle::instance = new PlayerIdle;
PlayerDown* PlayerDown::instance = new PlayerDown;
PlayerWalk* PlayerWalk::instance = new PlayerWalk;
PlayerJump* PlayerJump::instance = new PlayerJump;
PlayerFall* PlayerFall::instance = new PlayerFall;
PlayerLAttack* PlayerLAttack::instance = new PlayerLAttack;
PlayerHAttack* PlayerHAttack::instance = new PlayerHAttack;
PlayerLSAttack* PlayerLSAttack::instance = new PlayerLSAttack;
PlayerHSAttack* PlayerHSAttack::instance = new PlayerHSAttack;
PlayerBind* PlayerBind::instance = new PlayerBind;
PlayerHit* PlayerHit::instance = new PlayerHit;
PlayerDie* PlayerDie::instance = new PlayerDie;

Player::Player() : Units(D3DXVECTOR2(-800, 0))
{
	spr[UnitState::IDLE].LoadAll(L"Assets/Sprites/Units/Player/Idle");
	spr[UnitState::DOWN].LoadAll(L"Assets/Sprites/Units/Player/Down");
	spr[UnitState::WALK].LoadAll(L"Assets/Sprites/Units/Player/Walk");
	spr[UnitState::JUMP].LoadAll(L"Assets/Sprites/Units/Player/Jump", 0.1f, false);
	spr[UnitState::FALL].LoadAll(L"Assets/Sprites/Units/Player/Fall", 0.1f, false);
	spr[UnitState::LATTACK].LoadAll(L"Assets/Sprites/Units/Player/LightAttack", 0.05f, false);
	spr[UnitState::HATTACK].LoadAll(L"Assets/Sprites/Units/Player/HeavyAttack", 0.08f, false);
	spr[UnitState::LSATTACK1].LoadAll(L"Assets/Sprites/Units/Player/SpecialAttack/L1", 0.05f, false);
	spr[UnitState::LSATTACK2].LoadAll(L"Assets/Sprites/Units/Player/SpecialAttack/L2", 0.05f, false);
	spr[UnitState::HSATTACK1].LoadAll(L"Assets/Sprites/Units/Player/SpecialAttack/H1", 0.08f, false);
	spr[UnitState::HSATTACK2].LoadAll(L"Assets/Sprites/Units/Player/SpecialAttack/H2", 0.08f, false);
	spr[UnitState::BIND].LoadAll(L"Assets/Sprites/Units/Player/Bind", 0.08f, false);
	spr[UnitState::HIT].LoadAll(L"Assets/Sprites/Units/Player/Hit", 0.08f, false);
	spr[UnitState::DIE].LoadAll(L"Assets/Sprites/Units/Player/Die", 0.08f, false);

	PlayerIdle::instance->EnterState(this);

	renderer = UnitState::IDLE;

	tag = L"player";

	SetAbility(5, 200, 1, 1);
	SetCollider(-30, -50, 30, 50);

	Game::GetInstance().destCameraPos = { -699, 120 };
	Game::GetInstance().cameraPos = { -699, 120 };
}

void Player::Update(float deltaTime)
{
	if (pos.x > limitLeft && pos.x < limitRight)
		Game::GetInstance().destCameraPos.x = pos.x;

	//std::cout << Input::GetInstance().mousePos.x << std::endl;
	std::cout << pos.x << std::endl;

	inputTimer += deltaTime;
	for (int i = 0; i < 4; ++i)
	{
		if (Input::GetInstance().KeyDown(VK_LEFT + i))
		{
			inputTimer = 0;
			prevInput = nowInput;
			nowInput = i;
		}
	}

	if (inputTimer > 0.2f)
	{
		prevInput = -1;
		nowInput = -1;
	}

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	if (abs(velocity.x) > 0 && !bHit)
	{
		if (eftTimer >= 0.02f)
		{
			nowScene->obm.AddObject(new Spectrum(spr[renderer], pos, ri.scale , 0.2f));
			eftTimer = 0.0f;
		}

		eftTimer += deltaTime;
	}

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
	{
		vMove.x = -1;
		ri.scale.x = vMove.x;
	}
	else if (Input::GetInstance().KeyPress(VK_RIGHT))
	{
		vMove.x = 1;
		ri.scale.x = vMove.x;
	}

	if (bGround)
	{
		if (Input::GetInstance().KeyPress(VK_UP))
		{
			vMove.y = 1;

			if (z < 100)
				z += 2;
		}
		else if (Input::GetInstance().KeyPress(VK_DOWN))
		{
			vMove.y = -1;

			if (z > -20)
				z -= 2;
		}
	} 
	
	if (vMove.x == 0 && vMove.y == 0)
		return false;

	if (pos.x + vMove.x < limitLeft - 300 || pos.x + vMove.x > limitRight + 300)
	{
		velocity.x = 0;
		return false;
	}

	pos.x += vMove.x * ability.speed * deltaTime;

	return true;
}

int Player::SpecialIndex()
{
	specialIndex = -1;

	switch (prevInput)
	{
	case 0: // LEFT
	case 2: // RIGHT
		if (nowInput == prevInput)
		{
			specialIndex = 0;
		}
		break;
	case 1: // UP
		break;

	case 3: // DOWN
		if (nowInput == 0 || nowInput == 2)
			specialIndex = 1;
	}

	return specialIndex;
}

void Player::PlusSpecialGaze(int amount)
{
	specialGaze += amount;

	if (specialGaze > specialMaxGaze)
		specialGaze = 100;

}
