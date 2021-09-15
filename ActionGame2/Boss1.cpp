#include "DXUT.h"
#include "Boss1.h"

Boss1::Boss1()
{
	hitTime = 0.1f;
	ability.SetAbility(100, 100);
	SetImages();

	CreateCollider(D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 300), L"enemy");
	nowScene->obm.AddObject(detectRange = new Range(this, L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-700, -400), D3DXVECTOR2(700, 400), D3DCOLOR_ARGB(255, 0, 0, 255)));

	SetState(BossIdle::GetInstance());
}

void Boss1::Update(float deltaTime)
{
	CBoss::Update(deltaTime);
}

void Boss1::Render()
{
	CBoss::Render();
}

void Boss1::OnCollision(Collider& coli)
{
	CBoss::OnCollision(coli);
}

void Boss1::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Boss/Type1/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::ATTACK1).LoadAll(filePath + L"Attack1", 0.05f, false);
	GetSprite(Images::ATTACK2).LoadAll(filePath + L"Attack2", 0.05f, false);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::STUN).LoadAll(filePath + L"stun", 0.025f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);

	GetSprite(Images::SHADOW).LoadAll(L"Assets/Sprites/effect/shadow");
}

bool Boss1::Pattern1(float deltaTime)
{
	if (!GetNowSprite().bAnimation)
		return false;

	if (GetNowSprite().scene == 12 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new Bullet(team, pos + D3DXVECTOR2(ri.scale.x * 50, 170), D3DXVECTOR2(ri.scale.x, 0), 1200, 10, groundPos, Bullet::Type::GOLDROCK));
	}

	return true;
}

bool Boss1::Pattern2(float deltaTime)
{
	if (!GetNowSprite().bAnimation)
		return false;

	if (GetNowSprite().scene == 8 && !onAttack)
	{
		onAttack = true;

		D3DXVECTOR2 playerPos = D3DXVECTOR2(nowScene->player->pos.x, nowScene->player->groundPos);
		auto lambda = [=] {
			nowScene->obm.AddObject(new AttackCollider(L"enemy", playerPos, D3DXVECTOR2(0, 0), { D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 200) }, 10, D3DXVECTOR2(0, 100), 0.1f, 0.05f, playerPos.y)); };

		nowScene->obm.AddObject(new Effect(L"enemy/magic", playerPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.1), 0.05f, 6, true, lambda));
	}

	return true;
}

bool Boss1::Pattern3(float deltaTime)
{
	return false;
}
