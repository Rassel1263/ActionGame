#include "DXUT.h"
#include "Enemy1.h"

Enemy1::Enemy1(D3DXVECTOR2 pos) : CEnemy(pos)
{
	SetImages();
	SetCollider(-60, 0, 60, 300, team);
	ability.SetAbility(50, 100);
	SetRange(100, 100);

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

	std::wstring filePath = L"Assets/Sprites/Unit/Enemy/Type1/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::ATTACK).LoadAll(filePath + L"Attack", 0.05f, false);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);
}

void Enemy1::Attack(float deltaTime)
{
	if ( GetSprite(Images::ATTACK).scene == 8 && !onAttack)
	{
		onAttack = true;

		Collider::AABB aabb;
		aabb.min = { -100, 0 };
		aabb.max = { 100, 400 };
		nowScene->obm.AddObject(new AttackCollider(team, pos, D3DXVECTOR2(100 * ri.scale.x, 0), aabb, 5, 50, 0, 0.05f));
	}
}
