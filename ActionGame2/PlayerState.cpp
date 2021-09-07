#include "DXUT.h"
#include "PlayerState.h"

///////////////////////////
// Move
///////////////////////////

PlayerIdle* PlayerIdle::GetInstance()
{
	static PlayerIdle instance;
	return &instance;
}

void PlayerIdle::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::IDLE);
}

void PlayerIdle::UpdateState(Player* obj, float deltaTime)
{
	if (obj->Move(deltaTime))
	{
		obj->SetState(PlayerMove::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('C'))
	{
		obj->SetState(PlayerJump::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		obj->SetState(PlayerWeakAttack::GetInstance());
		return;
	}
}

void PlayerIdle::ExitState(Player* obj)
{
}

///////////////////////////
// Move
///////////////////////////

PlayerMove* PlayerMove::GetInstance()
{
	static PlayerMove instance;
	return &instance;
}

void PlayerMove::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::MOVE);
}

void PlayerMove::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->Move(deltaTime))
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('C'))
	{
		obj->SetState(PlayerJump::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		obj->SetState(PlayerWeakAttack::GetInstance());
		return;
	}
}

void PlayerMove::ExitState(Player* obj)
{
}

///////////////////////////
// Jump
///////////////////////////

PlayerJump* PlayerJump::GetInstance()
{
	static PlayerJump instance;
	return &instance;;
}

void PlayerJump::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::JUMP);

	obj->velocity.y = 1200;
}

void PlayerJump::UpdateState(Player* obj, float deltaTime)
{
	if (obj->velocity.y < 0.0f)
	{
		obj->SetState(PlayerFall::GetInstance());
		return;
	}

	obj->Move(deltaTime);
}

void PlayerJump::ExitState(Player* obj)
{
}

///////////////////////////
// Fall
///////////////////////////

PlayerFall* PlayerFall::GetInstance()
{
	static PlayerFall instance;
	return &instance;
}

void PlayerFall::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::FALL);
}

void PlayerFall::UpdateState(Player* obj, float deltaTime)
{
	if (obj->bGround)
	{
		obj->SetState(PlayerLanding::GetInstance());
		return;
	}

	obj->Move(deltaTime);
}

void PlayerFall::ExitState(Player* obj)
{
}

///////////////////////////
// Landing
///////////////////////////

PlayerLanding* PlayerLanding::GetInstance()
{
	static PlayerLanding instance;
	return &instance;
}

void PlayerLanding::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::LANDING);
}

void PlayerLanding::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerLanding::ExitState(Player* obj)
{
}

///////////////////////////
// Slide
///////////////////////////

PlayerSliding* PlayerSliding::GetInstance()
{
	static PlayerSliding instance;
	return &instance;
}

void PlayerSliding::EnterState(Player* obj)
{
}

void PlayerSliding::UpdateState(Player* obj, float deltaTime)
{
}

void PlayerSliding::ExitState(Player* obj)
{
}

///////////////////////////
// WeakAttack
///////////////////////////

PlayerWeakAttack* PlayerWeakAttack::GetInstance()
{
	static PlayerWeakAttack instance;
	return &instance;
}


void PlayerWeakAttack::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::WEAKATTACK1);

	combo = 0;
	comboInput = 0;
	timer = 0;
	onAttack = false;
}

void PlayerWeakAttack::UpdateState(Player* obj, float deltaTime)
{
	if (obj->GetSprite(Player::Images::WEAKATTACK1).scene == 4 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new Effect(L"Player/fire1", obj->pos + D3DXVECTOR2(200 * obj->ri.scale.x, 240), obj->ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));
		nowScene->obm.AddObject(new PlayerBullet(obj->pos + D3DXVECTOR2(200 * obj->ri.scale.x, 260), D3DXVECTOR2(obj->ri.scale.x, 0), 1000, 5));
	}
	else if (obj->renderNum != IntEnum(Player::Images::WEAKATTACK1) && obj->GetNowSprite().scene == 1 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new Effect(L"Player/fire1", obj->pos + D3DXVECTOR2(200 * obj->ri.scale.x, 240), obj->ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));
		nowScene->obm.AddObject(new PlayerBullet(obj->pos + D3DXVECTOR2(200 * obj->ri.scale.x, 260), D3DXVECTOR2(obj->ri.scale.x, 0), 1000, 5));
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		if (comboInput < 3)
			comboInput++;
	}

	if (!obj->GetNowSprite().bAnimation && combo < comboInput)
	{
		combo++;
		onAttack = false;
		timer = 0;

		if (combo == 3)
		{
			obj->attackNum = 0;
			obj->SetState(PlayerSpecialAttack::GetInstance());
			return;
		}
		else
		{
			obj->SetAni(PluseEnum(Player::Images, Player::Images::WEAKATTACK1, combo));
		}
	}

	if (timer > 0.2f && !obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerStopWeakAttack::GetInstance());
		return;
	}

	timer += deltaTime;
}

void PlayerWeakAttack::ExitState(Player* obj)
{
}

PlayerStopWeakAttack* PlayerStopWeakAttack::GetInstance()
{
	static PlayerStopWeakAttack instance;
	return &instance;
}

void PlayerStopWeakAttack::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::WEAKTATCKEND);
}

void PlayerStopWeakAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerStopWeakAttack::ExitState(Player* obj)
{
}

PlayerSpecialAttack* PlayerSpecialAttack::GetInstance()
{
	static PlayerSpecialAttack instance;
	return &instance;
}

void PlayerSpecialAttack::EnterState(Player* obj)
{
	timer = 0.0f;
	afterImage = false;

	switch (obj->attackNum)
	{
	case 0:
		obj->SetAni(Player::Images::WEAKATTACK4);
		break;
	case 1:
		obj->SetAni(Player::Images::SLIDE);
		obj->velocity.x += obj->ri.scale.x * 3000;
		break;
	case 2:
		obj->SetAni(Player::Images::GUNKATA);
		nowScene->obm.AddObject(new Effect(L"Player/fire_gunkata", obj->pos + D3DXVECTOR2(0, 240), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 0.04f));
		obj->CreateAfterImage(0, 0.0f, D3DCOLOR_ARGB(125, 255, 255, 255));
		SetAfterImage(0.1f);
		break;
	case 3:
		obj->SetAni(Player::Images::MOVESHOOT);
		obj->CreateAfterImage(3, 0.0f, D3DCOLOR_ARGB(125, 255, 255, 255));
		SetAfterImage(0.15f);
		break;
	}
}

void PlayerSpecialAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}

	if (obj->attackNum == 0)
	{
	}
	else if (obj->attackNum == 3) // MoveShot ÁßÀÏ ¶§
	{
		obj->Move(deltaTime);

		static bool change = false;
		attackTimer += deltaTime;

		if ((obj->GetNowSprite().scene >= 2 && obj->GetNowSprite().scene <= 13) || 
			obj->GetNowSprite().scene >= 18 && obj->GetNowSprite().scene <= 29)
		{

			if (attackTimer >= 0.08f)
			{
				D3DXVECTOR2 fixedPos = obj->pos + D3DXVECTOR2(250 * obj->ri.scale.x, 240);

				(change) ? fixedPos.y += 10 : fixedPos.y -= 10;

				nowScene->obm.AddObject(new Effect(L"Player/fire1", fixedPos, obj->ri.scale, D3DXVECTOR2(0.5f, 0.5f), 0.05f));
				fixedPos.y += 20;
				nowScene->obm.AddObject(new PlayerBullet(fixedPos, D3DXVECTOR2(obj->ri.scale.x, 0), 1000, 5));

				change = !change;

				attackTimer = 0.0f;
			}
		}
	}

	if (afterImage)
	{
		if (timer >= afterImageTime)
		{
			obj->CreateAfterImage(0, 0.5f, D3DCOLOR_ARGB(70, 70, 0, 0));
			timer = 0.0f;
		}
		timer += deltaTime;
	}
}

void PlayerSpecialAttack::ExitState(Player* obj)
{
}

