#include "DXUT.h"

BossIdle* BossIdle::GetInstance()
{
	static BossIdle instance;
	return &instance;
}

void BossIdle::EnterState(CBoss* obj)
{
	obj->SetAni(CBoss::Images::IDLE);
}

void BossIdle::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (obj->pattern == 1)
	{
		obj->SetState(BossPattern1::GetInstance());
		return;
	}

	if (obj->pattern == 2)
	{
		obj->SetState(BossPattern2::GetInstance());
		return;
	}

	if (obj->pattern == 3)
	{
		obj->SetState(BossPattern3::GetInstance());
		return;
	}

	if (obj->Move(deltaTime))
	{
		obj->SetState(BossMove::GetInstance());
		return;
	}
}

void BossIdle::ExitState(CBoss* obj)
{
}

BossMove* BossMove::GetInstance()
{
	static BossMove instance;
	return &instance;
}

void BossMove::EnterState(CBoss* obj)
{
	obj->SetAni(CBoss::Images::MOVE);
}

void BossMove::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (obj->pattern == 1)
	{
		obj->SetState(BossPattern1::GetInstance());
		return;
	}

	if (obj->pattern == 2)
	{
		obj->SetState(BossPattern2::GetInstance());
		return;
	}

	if (obj->pattern == 3)
	{
		obj->SetState(BossPattern3::GetInstance());
		return;
	}

	if (!obj->Move(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossMove::ExitState(CBoss* obj)
{
}

BossHit* BossHit::GetInstance()
{
	static BossHit instance;
	return &instance;
}

void BossHit::EnterState(CBoss* obj)
{
	obj->SetAni(CBoss::Images::HIT);
}

void BossHit::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (abs(obj->velocity.y) > 100)
	{
		obj->SetState(BossStun::GetInstance());
		return;
	}

	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossHit::ExitState(CBoss* obj)
{
	obj->hit = false;
}

BossStun* BossStun::GetInstance()
{
	static BossStun instance;
	return &instance;
}

void BossStun::EnterState(CBoss* obj)
{
	obj->SetAni(CBoss::Images::STUN);
}

void BossStun::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(BossStun::GetInstance());
		return;
	}

	if (obj->bGround)
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossStun::ExitState(CBoss* obj)
{
}

BossPattern1* BossPattern1::GetInstance()
{
	static BossPattern1 instance;
	return &instance;
}

void BossPattern1::EnterState(CBoss* obj)
{
	obj->SetAni(CBoss::Images::ATTACK1);
}

void BossPattern1::UpdateState(CBoss* obj, float deltaTime)
{

	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (!obj->Pattern1(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern1::ExitState(CBoss* obj)
{
	obj->ResetPattern();
}

BossPattern2* BossPattern2::GetInstance()
{
	static BossPattern2 instance;
	return &instance;
}

void BossPattern2::EnterState(CBoss* obj)
{
	obj->SetAni(CBoss::Images::ATTACK2);
}

void BossPattern2::UpdateState(CBoss* obj, float deltaTime)
{

	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (!obj->Pattern2(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern2::ExitState(CBoss* obj)
{
	obj->ResetPattern();
}

BossPattern3* BossPattern3::GetInstance()
{
	static BossPattern3 instance;
	return &instance;
}

void BossPattern3::EnterState(CBoss* obj)
{
	obj->SetAni(CBoss::Images::ATTACK3);
}

void BossPattern3::UpdateState(CBoss* obj, float deltaTime)
{
	if (obj->ability.hp <= 0)
	{
		obj->SetState(BossDie::GetInstance());
		return;
	}

	if (obj->hit && !obj->superArmor)
	{
		obj->SetState(BossHit::GetInstance());
		return;
	}

	if (!obj->Pattern3(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern3::ExitState(CBoss* obj)
{
	obj->ResetPattern();
}

BossDie* BossDie::GetInstance()
{
	static BossDie instance;
	return &instance;
}

void BossDie::EnterState(CBoss* obj)
{
	obj->SetAni(CBoss::Images::DIE);
	obj->bCollider = false;
	restoration = false;
	nowScene->stopTime = true;

	nowScene->player->fallowCamera = false;
	Camera::GetInstance().destCameraPos.x = obj->pos.x;
	Camera::GetInstance().destCameraPos.y = obj->pos.y + 150;
	Camera::GetInstance().destDivideProj = 1.5;
	std::cout << Camera::GetInstance().destCameraPos.x << std::endl;

	Game::GetInstance().timeScale = 0.1f;
}

void BossDie::UpdateState(CBoss* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation && !restoration)
	{
		restoration = true;

		nowScene->obm.AddObject(new StageFont(StageFont::Type::CLEAR));
		nowScene->player->fallowCamera = true;
		Camera::GetInstance().destCameraScale = { 1, 1 };
		Camera::GetInstance().destCameraPos.y = 0.0f;
		Game::GetInstance().timeScale = 1.0f;
		Camera::GetInstance().destDivideProj = 1;
	}
}

void BossDie::ExitState(CBoss* obj)
{
}

