#include "DXUT.h"
#include "Boss2.h"

Boss2::Boss2()
{
	hitTime = 0.1f;
	ability.SetAbility(1000, 100);
	SetImages();

	CreateCollider(D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 300), L"enemy");
	nowScene->obm.AddObject(detectRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-700, -400), D3DXVECTOR2(700, 400), D3DCOLOR_ARGB(255, 0, 0, 255)));

	SetState(BossIdle::GetInstance());
}

void Boss2::Update(float deltaTime)
{
	CBoss::Update(deltaTime);
}

void Boss2::Render()
{
	CBoss::Render();
}

void Boss2::OnCollision(Collider& coli)
{
	CBoss::OnCollision(coli);
}

void Boss2::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Boss/Type2/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::ATTACK1).LoadAll(filePath + L"Attack1", 0.05f, false);

	GetSprite(Images::ATTACKREADY).LoadAll(filePath + L"AttackReady", 0.05f, false);
	GetSprite(Images::ATTACK2).LoadAll(filePath + L"Attack2", 0.02f, false);
	GetSprite(Images::ATTACKEND).LoadAll(filePath + L"AttackEnd", 0.05f, false);

	GetSprite(Images::ATTACK3).LoadAll(filePath + L"Attack3", 0.01f, false);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::STUN).LoadAll(filePath + L"stun", 0.025f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);

	GetSprite(Images::SHADOW).LoadAll(L"Assets/Sprites/effect/shadow");
}

bool Boss2::Pattern1(float deltaTime)
{
	if (!GetNowSprite().bAnimation) return false;

	if (GetNowSprite().scene == 18 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new AttackCollider(L"enemy", pos, D3DXVECTOR2(300 * ri.scale.x, 20), { D3DXVECTOR2(-300, 0), D3DXVECTOR2(50, 300) }, 10, D3DXVECTOR2(0, 0), 0.0f, 0.1f, groundPos));
	}
	else if (GetNowSprite().scene == 25 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new AttackCollider(L"enemy", pos, D3DXVECTOR2(300 * ri.scale.x, 20), { D3DXVECTOR2(-300, 0), D3DXVECTOR2(50, 300) }, 10, D3DXVECTOR2(0, 0), 0.0f, 0.1f, groundPos));
	}
	else if (GetNowSprite().scene == 34 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new AttackCollider(L"enemy", pos, D3DXVECTOR2(300 * ri.scale.x, 20), { D3DXVECTOR2(-300, 0), D3DXVECTOR2(50, 300) }, 10, D3DXVECTOR2(0, 0), 0.0f, 0.1f, groundPos));
	}
	else
		onAttack = false;

	return true;
}

bool Boss2::Pattern2(float deltaTime)
{
	if (!GetSprite(Images::ATTACKEND).bAnimation)
	{
		GetNowSprite().Reset();
		return false;
	}

	if (renderNum == IntEnum(Images::ATTACK2))
	{
		if (!onAttack)
		{
			onAttack = true;
			nowScene->obm.AddObject(new AttackCollider(L"enemy", &pos, D3DXVECTOR2(100, 20), { D3DXVECTOR2(-200, 0), D3DXVECTOR2(200, 300) }, 10, D3DXVECTOR2(0, 0), 0.0f, 0.9f, groundPos));
		}

		pos.x += ri.scale.x * 1000 * deltaTime;
		pos.y += (nowScene->player->pos.y - pos.y > pos.y) ? 1 : -1 * 200 * deltaTime;
	}

	if (!GetNowSprite().bAnimation)
		SetAni(PlusEnum(Images, Images::ATTACKREADY, ++rushIndex));

	return true;
}

bool Boss2::Pattern3(float deltaTime)
{
	if (!GetNowSprite().bAnimation) return false;

	nowScene->obm.AddObject(new AttackCollider(L"enemy", pos, D3DXVECTOR2(0, 0), { D3DXVECTOR2(-400, -100), D3DXVECTOR2(400, 400) },1, D3DXVECTOR2(0, 0), 0.0f, 0.98f, groundPos));

	return true;
}

int Boss2::ChoosePattern()
{
	return nowScene->GetRandomNum(1, 3);
}
