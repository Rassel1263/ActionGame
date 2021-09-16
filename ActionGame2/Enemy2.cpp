#include "DXUT.h"
#include "Enemy2.h"

Enemy2::Enemy2(D3DXVECTOR2 pos) : CEnemy(pos)
{
	enemyType = 2;
	hitTime = 0.1f;
	restTime = 1.0f;

	SetImages();
	SetCollider(-60, 0, 60, 300, team);
	CreateAttackRange(L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-500, 0), D3DXVECTOR2(500, 200), 100);
	CreateDetectRange(L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-800, 0), D3DXVECTOR2(800, 300), 300);
	ability.SetAbility(120, 100);

	SetState(EnemyIdle::GetInstance());
}

void Enemy2::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void Enemy2::Render()
{
	CEnemy::Render();
}

void Enemy2::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Enemy/Type2/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::ATTACK).LoadAll(filePath + L"Attack", 0.05f, false);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::STUN).LoadAll(filePath + L"stun", 0.05f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);

	GetSprite(Images::SHADOW).LoadAll(L"Assets/Sprites/effect/shadow");
}

void Enemy2::Attack(float deltaTime)
{
	if (GetSprite(Images::ATTACK).scene == 13 && !onAttack)
	{
		onAttack = true;
		nowScene->obm.AddObject(new Bullet(team, pos + D3DXVECTOR2(ri.scale.x * 50, 150), D3DXVECTOR2(ri.scale.x, 0), 1000, 5, groundPos, Bullet::Type::ROCK));
	}
}
