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
	GetSprite(Images::ATTACK2).LoadAll(filePath + L"Attack2", 0.05f, false);
	GetSprite(Images::ATTACK3).LoadAll(filePath + L"Attack3", 0.05f, false);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);

	GetSprite(Images::SHADOW).LoadAll(L"Assets/Sprites/effect/shadow");
}

bool Boss2::Pattern1(float deltaTime)
{
	return false;
}

bool Boss2::Pattern2(float deltaTime)
{
	return false;
}

bool Boss2::Pattern3(float deltaTime)
{
	return false;
}
