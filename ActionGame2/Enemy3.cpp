#include "DXUT.h"
#include "Enemy3.h"

Enemy3::Enemy3(D3DXVECTOR2 pos) : CEnemy(pos)
{
	enemyType = 3;
	hitTime = 0.1f;

	SetImages();
	SetCollider(-60, 0, 60, 300, team);
	ability.SetAbility(50, 100);
	SetRange(500, 500);

	SetState(EnemyIdle::GetInstance());
}

void Enemy3::Update(float deltaTime)
{
	if (nowState)
		nowState->UpdateState(this, deltaTime);

	CEnemy::Update(deltaTime);
}

void Enemy3::Render()
{
	CEnemy::Render();
}

void Enemy3::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Enemy/Type3/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::ATTACK).LoadAll(filePath + L"Attack", 0.05f, false);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);
}

void Enemy3::Attack(float deltaTime)
{
	if (GetSprite(Images::ATTACK).scene == 8 && !onAttack)
	{
		onAttack = true;
		D3DXVECTOR2 playerPos = nowScene->player->pos;
		auto lambda = [=] {nowScene->obm.AddObject(new AttackCollider(L"enemy", playerPos, D3DXVECTOR2(0, 0), { D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 200) }, 10, D3DXVECTOR2(0, 100), 0.1f, 0.05f)); };

		nowScene->obm.AddObject(new Effect(L"enemy/", nowScene->player->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.1), 0.1f, 6, lambda));
	};
}
