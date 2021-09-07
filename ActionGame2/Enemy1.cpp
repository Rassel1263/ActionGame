#include "DXUT.h"
#include "Enemy1.h"

Enemy1::Enemy1(D3DXVECTOR2 pos) : CEnemy(pos)
{
	SetImages();
	SetCollider(-60, 0, 60, 300, L"enemy");

	SetState(EnemyIdle::GetInstance());
}

void Enemy1::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void Enemy1::Render()
{
	CEnemy::Render();
}

void Enemy1::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Player/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"stay", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.1f, false);
}
