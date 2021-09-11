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

	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
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

	if (Input::GetInstance().KeyDown('S'))
	{
		obj->SetState(PlayerStrongAttack::GetInstance());
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

	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
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

	if (Input::GetInstance().KeyDown('S'))
	{
		obj->SetState(PlayerStrongAttack::GetInstance());
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

	if (Input::GetInstance().KeyDown('X') && !obj->jumpAttack)
	{
		obj->SetState(PlayerJumpAttack::GetInstance());
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

	if (Input::GetInstance().KeyDown('X') && !obj->jumpAttack)
	{
		obj->SetState(PlayerJumpAttack::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyPress('C'))
		obj->velocity.y -= 200;

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
	if (!obj->GetNowSprite().bAnimation || Input::GetInstance().KeyPress('C'))
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerLanding::ExitState(Player* obj)
{
	obj->jumpAttack = false;

}

///////////////////////////
// WeakAttack
///////////////////////////

PlayerJumpAttack* PlayerJumpAttack::GetInstance()
{
	static PlayerJumpAttack instance;
	return &instance;
}

void PlayerJumpAttack::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::JUMPATTACK1);
	
	obj->jumpAttack = true;

	combo = 0;
	comboInput = 0;
	timer = 0;

	obj->velocity.y = 0.0f;
	obj->gravity = 3.0f;
}

void PlayerJumpAttack::UpdateState(Player* obj, float deltaTime)
{
	if (obj->bGround)
	{
		obj->SetState(PlayerLanding::GetInstance());
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
		if (comboInput < 3) comboInput++;

	if (obj->GetNowSprite().scene == 0 && !obj->onAttack)
	{
		obj->onAttack = true;
		obj->CreateBullet(D3DXVECTOR2(170, 100), 1000, 5, Bullet::Type::BASIC, true);
	}

	if (!obj->GetNowSprite().bAnimation && combo < comboInput)
	{
		combo++;
		obj->onAttack = false;
		timer = 0;

		if (combo == 3)
		{
			obj->attackNum = 0;
			obj->SetState(PlayerFall::GetInstance());
			return;
		}
		else
			obj->SetAni(PluseEnum(Player::Images, Player::Images::JUMPATTACK1, combo));
	}

	if (timer > 0.2f && !obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerFall::GetInstance());
		return;
	}

	obj->Move(deltaTime, true);

	timer += deltaTime;
}

void PlayerJumpAttack::ExitState(Player* obj)
{
	obj->gravity = 9.8f;
	obj->onAttack = false;
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
	if (obj->hit)
	{
		obj->SetState(PlayerHit::GetInstance());
		return;
	}

	if (obj->GetSprite(Player::Images::WEAKATTACK1).scene == 4 && !onAttack)
	{
		onAttack = true;
		obj->CreateBullet(D3DXVECTOR2(200, 240), 1000, 5, Bullet::Type::BASIC);
	}
	else if (obj->renderNum != IntEnum(Player::Images::WEAKATTACK1) && obj->GetNowSprite().scene == 1 && !onAttack)
	{
		onAttack = true;
		obj->CreateBullet(D3DXVECTOR2(200, 240), 1000, 5, Bullet::Type::BASIC);
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

///////////////////////////
// StrongAttack
///////////////////////////

PlayerStrongAttack* PlayerStrongAttack::GetInstance()
{
	static PlayerStrongAttack instance;
	return &instance;
}

void PlayerStrongAttack::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::STRONGATTACK);
}

void PlayerStrongAttack::UpdateState(Player* obj, float deltaTime)
{
	obj->CreateAttackCollider(3, D3DXVECTOR2(100, 0), D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 300), 10, D3DXVECTOR2(100, 0), 0.05f, 0.1f);

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerStrongAttack::ExitState(Player* obj)
{
	obj->onAttack = false;
}


PlayerSpecialAttack* PlayerSpecialAttack::GetInstance()
{
	static PlayerSpecialAttack instance;
	return &instance;
}

void PlayerSpecialAttack::EnterState(Player* obj)
{
	timer = 0.0f;
	obj->superArmor = true;

	obj->SpecialAttackCancel();

	if (obj->attackNum == 0)	  obj->SetSpecialAttack(Player::Images::WEAKATTACK4, 8, 0.0f, 0);
	else if (obj->attackNum == 1) obj->SetSpecialAttack(Player::Images::SLIDE, 0, 0.0f, 10);
	else if (obj->attackNum == 2) obj->SetSpecialAttack(Player::Images::GUNKATA, 23, 0.1f, 20);
	else if (obj->attackNum == 3) obj->SetSpecialAttack(Player::Images::MOVESHOOT, 3, 0.15f, 20);
	else if (obj->attackNum == 4) obj->SetSpecialAttack(Player::Images::MACHINEGUN, 7, 0.0f, 10);
	else if (obj->attackNum == 5) obj->SetSpecialAttack(Player::Images::SNIPER, 10, 0.1f, 30);
	else if (obj->attackNum == 6) obj->SetSpecialAttack(Player::Images::NUCLEAR, 0, 0.1f, 30);
}

void PlayerSpecialAttack::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		obj->attackNum = 0;
		return;
	}

	obj->attackTimer -= deltaTime;

	if (obj->attackNum == 0) // 기본 공격 끝났을 때
	{
		if (obj->attackTimer <= 0.0f && !obj->onAttack)
		{
			obj->onAttack = true;
			obj->CreateBullet(D3DXVECTOR2(250, 210), 1000, 5, Bullet::Type::AIRSHOT);
		}
	}
	else if (obj->attackNum == 1)
		obj->CreateAttackCollider(0, D3DXVECTOR2(100, 0), D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 100), 10, D3DXVECTOR2(100, 0), 0.1f, 0.1f, true);
	else if (obj->attackNum == 2)
		Camera::GetInstance().cameraQuaken = { 2, 2 };
	else if (obj->attackNum == 3)
	{
		obj->Move(deltaTime, true);

		static bool change = false;

		if ((obj->GetNowSprite().scene >= 2 && obj->GetNowSprite().scene <= 13) ||
			obj->GetNowSprite().scene >= 18 && obj->GetNowSprite().scene <= 29)
		{

			if (obj->attackTimer <= 0.0f)
			{
				D3DXVECTOR2 offset = D3DXVECTOR2(250, 240);
				(change) ? offset.y += 10 : offset.y -= 10;
				obj->CreateBullet(offset, 1000, 5, Bullet::Type::BASIC);
				change = !change;

				obj->attackTimer = obj->maxAttackTimer;
			}
		}
	}
	else if (obj->attackNum == 4)
	{
		if ((obj->GetNowSprite().scene <= 23))
			if (obj->attackTimer <= 0.0f)
			{
				obj->CreateBullet(D3DXVECTOR2(230, 200), 1500, 10, Bullet::Type::MACHINEGUN);
				obj->attackTimer = obj->maxAttackTimer;
			}
	}
	else if (obj->attackNum == 5)
	{
		if (obj->attackTimer <= 0.0f && !obj->onAttack)
		{
			obj->onAttack = true;
			obj->CreateBullet(D3DXVECTOR2(250, 150), 2500, 30, Bullet::Type::SNIPER);

		}
	}	if(obj->afterImage)
	{
		if (timer >= obj->afterImageTime)
		{
			obj->CreateAfterImage(0, 0.5f, D3DCOLOR_ARGB(70, 0, 0, 0));
			timer = 0.0f;
		}
		timer += deltaTime;
	}
}

void PlayerSpecialAttack::ExitState(Player* obj)
{
	obj->afterImage = false;
	obj->superArmor = false;
	obj->onAttack = false;
}

PlayerHit* PlayerHit::GetInstance()
{
	static PlayerHit instance;
	return &instance;
}

void PlayerHit::EnterState(Player* obj)
{
	obj->SetAni(Player::Images::HIT);
}

void PlayerHit::UpdateState(Player* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(PlayerIdle::GetInstance());
		return;
	}
}

void PlayerHit::ExitState(Player* obj)
{
	obj->hit = false;
}
