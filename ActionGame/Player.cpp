#include "DXUT.h"
#include "Player.h"

PlayerIntro* PlayerIntro::instance = new PlayerIntro;
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
PlayerCereMony* PlayerCereMony::instance = new PlayerCereMony;

Player::Player() : Units(D3DXVECTOR2(-1300, 0))
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
	spr[UnitState::CEREMONY].LoadAll(L"Assets/Sprites/Units/Player/Ceremony", 0.1f, false);

	PlayerIntro::instance->EnterState(this);

	renderer = UnitState::WALK;

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

	if (abs(velocity.x) > 0 && !bHit)
	{
		if (eftTimer >= 0.02f)
		{
			nowScene->obm.AddObject(new Spectrum(spr[renderer], pos, ri.scale, 0.2f));
			eftTimer = 0.0f;
		}

		eftTimer += deltaTime;
	}

	if (bPowerUp)
	{
		abilityTimer += deltaTime;
		if (abilityTimer >= 3.0f)
		{
			bPowerUp = false;
			abilityTimer = 0.0f;
		}
	}

	if (hpGaze >= hpMaxGaze)
	{
		if (Input::GetInstance().KeyDown(VK_SPACE))
		{
			hpGaze = 0;
			ability.hp++;
		}
	}

	shaderTimer += deltaTime * 2;

	while (shaderTimer >= 2.0f)
		shaderTimer -= 3.0f;

	if (nowState)
		nowState->UpdateState(this, deltaTime);

	Units::Update(deltaTime);
}

void Player::Render()
{
	Units::Render();

	if (bPowerUp)
		simpleShader->Render(simpleShader, spr[renderer].GetNowScene(), spr[renderer], ri, D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.8f, 0.8f, 0.8f, 1.0f), shaderTimer);
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

	if(hpGaze < hpMaxGaze)
		hpGaze += 10 * deltaTime;

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

bool Player::CheckSpecialGaze(int amount)
{
	int specialIndex = SpecialIndex();

	if (specialIndex == -1) return false;

	switch (specialIndex)
	{
	case 0:
		if (specialGaze >= 20 * amount)
		{
			specialGaze -= 20 * amount;
			return true;
		}
		break;
	case 1:
		if (specialGaze >= 20 * amount)
		{
			specialGaze -= 20 * amount;
			return true;
		}
		break;
	}

	return false;
}

void Player::PlusSpecialGaze(int amount)
{
	specialGaze += amount;

	if (specialGaze > specialMaxGaze)
		specialGaze = 100;

}

void Player::SetItemEffect(int index)
{
	switch (index)
	{
	case 0:
		bPowerUp = true;
		break;

	case 1:
		boom = true;
		break;

	case 2:
		ability.hp += 2;
		if (ability.hp >= ability.maxHp)
			ability.hp = ability.maxHp;
		break;

	}
}
