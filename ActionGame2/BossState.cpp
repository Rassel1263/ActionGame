#include "DXUT.h"

BossIdle* BossIdle::GetInstance()
{
	static BossIdle instance;
	return &instance;
}

void BossIdle::EnterState(Boss1* obj)
{
	obj->SetAni(Boss1::Images::IDLE);
}

void BossIdle::UpdateState(Boss1* obj, float deltaTime)
{
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

void BossIdle::ExitState(Boss1* obj)
{
}

BossMove* BossMove::GetInstance()
{
	static BossMove instance;
	return &instance;
}

void BossMove::EnterState(Boss1* obj)
{
	obj->SetAni(Boss1::Images::MOVE);
}

void BossMove::UpdateState(Boss1* obj, float deltaTime)
{
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

void BossMove::ExitState(Boss1* obj)
{
}

BossHit* BossHit::GetInstance()
{
	static BossHit instance;
	return &instance;
}

void BossHit::EnterState(Boss1* obj)
{
	obj->SetAni(Boss1::Images::HIT);
}

void BossHit::UpdateState(Boss1* obj, float deltaTime)
{
	if (!obj->GetNowSprite().bAnimation)
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossHit::ExitState(Boss1* obj)
{
	obj->hit = false;
}

BossPattern1* BossPattern1::GetInstance()
{
	static BossPattern1 instance;
	return &instance;
}

void BossPattern1::EnterState(Boss1* obj)
{
	obj->SetAni(Boss1::Images::ATTACK1);
}

void BossPattern1::UpdateState(Boss1* obj, float deltaTime)
{
	if (!obj->Pattern1(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern1::ExitState(Boss1* obj)
{
	obj->ResetPattern();
}

BossPattern2* BossPattern2::GetInstance()
{
	static BossPattern2 instance;
	return &instance;
}

void BossPattern2::EnterState(Boss1* obj)
{
	obj->SetAni(Boss1::Images::ATTACK2);
}

void BossPattern2::UpdateState(Boss1* obj, float deltaTime)
{
	if (!obj->Pattern2(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern2::ExitState(Boss1* obj)
{
	obj->ResetPattern();
}

BossPattern3* BossPattern3::GetInstance()
{
	static BossPattern3 instance;
	return &instance;
}

void BossPattern3::EnterState(Boss1* obj)
{
}

void BossPattern3::UpdateState(Boss1* obj, float deltaTime)
{
	if (!obj->Pattern3(deltaTime))
	{
		obj->SetState(BossIdle::GetInstance());
		return;
	}
}

void BossPattern3::ExitState(Boss1* obj)
{
	obj->ResetPattern();
}

BossDie* BossDie::GetInstance()
{
	static BossDie instance;
	return &instance;
}

void BossDie::EnterState(Boss1* obj)
{
}

void BossDie::UpdateState(Boss1* obj, float deltaTime)
{
}

void BossDie::ExitState(Boss1* obj)
{
}

