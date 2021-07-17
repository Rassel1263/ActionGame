#include "DXUT.h"
#include "PlayerState.h"

void PlayerIntro::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;
	obj->renderer = UnitState::WALK;
}

void PlayerIntro::UpdateState(Player* obj, float deltaTime)
{
	if (obj->pos.x <= -800)
		obj->pos.x += 150 * deltaTime;
	else
	{
		PlayerIdle::instance->EnterState(obj);
		return;
	}
}

void PlayerIntro::ExitState(Player* obj)
{
}


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

	if (nowScene->wave <= 0)
	{
		PlayerCereMony::instance->EnterState(obj);
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

	if (obj->boom)
	{
		nowScene->obm.AddObject(new Boom(obj, obj->pos, obj->ri.scale, 3.0f));
		obj->boom = false;
	}
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

}

void PlayerWalk::UpdateState(Player* obj, float deltaTime)
{
	if (Input::GetInstance().KeyDown('A'))
	{
		if (obj->specialGaze >= 30)
		{
			obj->specialGaze -= 30;
			obj->velocity.x = 1500 * obj->ri.scale.x;
		}
	}

	if (Input::GetInstance().KeyDown('Z'))
	{
		if (obj->CheckSpecialGaze(1))
			PlayerLSAttack::instance->EnterState(obj);
		else
			PlayerLAttack::instance->EnterState(obj);
		return;
	}

	if (Input::GetInstance().KeyDown('X'))
	{
		if (obj->CheckSpecialGaze(2))
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

	obj->SetAttackInfo(D3DXVECTOR2(obj->ri.scale.x * 50, 40), { 1, 0 }, 300, 5, 1);
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

	obj->SetAttackInfo(D3DXVECTOR2(obj->ri.scale.x * 50, 40), { 1, -0.2 }, 500, 7, 4);
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
		obj->renderer = UnitState::LSATTACK1;
		obj->spr[obj->renderer].Reset();
		obj->SetAttackInfo(D3DXVECTOR2(obj->ri.scale.x * 50, 10), { 1, 0 }, 700, 15, 3);
		break;
	case 1:
		obj->renderer = UnitState::LSATTACK2;
		obj->spr[obj->renderer].Reset();
		break;
	}
}

void PlayerLSAttack::UpdateState(Player* obj, float deltaTime)
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
		obj->spr[obj->renderer].Reset();
		obj->SetAttackInfo(D3DXVECTOR2(obj->ri.scale.x * 60, 10), { 1, 0.2 }, 1000 ,20, 7);
		break;
	case 1:
		obj->renderer = UnitState::HSATTACK2;
		obj->spr[obj->renderer].Reset();
		break;
	}

}

void PlayerHSAttack::UpdateState(Player* obj, float deltaTime)
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

void PlayerHSAttack::ExitState(Player* obj)
{
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

void PlayerCereMony::EnterState(Player* obj)
{
	if (obj->nowState)
		obj->nowState->ExitState(obj);

	obj->nowState = this;

	obj->renderer = UnitState::CEREMONY;
	obj->spr[obj->renderer].Reset();
}

void PlayerCereMony::UpdateState(Player* obj, float deltaTime)
{
	if (obj->spr[obj->renderer].scene >= obj->spr[obj->renderer].szScene)
	{
		obj->spr[obj->renderer].scene = 8;
		nowScene->obm.AddObject(new ResultScreen());
		//Game::GetInstance().ChangeScene(new GameScene2());
	}
}

void PlayerCereMony::ExitState(Player* obj)
{
}

