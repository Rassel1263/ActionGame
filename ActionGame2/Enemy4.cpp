#include "DXUT.h"
#include "Enemy4.h"

Enemy4::Enemy4(D3DXVECTOR2 pos) : CEnemy(pos)
{
	enemyType = 4;
	hitTime = 0.1f;

	SetImages();
	SetCollider(-60, 0, 60, 300, team);
	CreateAttackRange(L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 200));
	CreateDetectRange(L"player", D3DXVECTOR2(0, 0), D3DXVECTOR2(-300, 0), D3DXVECTOR2(300, 300));
	ability.SetAbility(300, 100);


	SetState(EnemyIdle::GetInstance());
}

void Enemy4::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown('H'))
		ability.hp = ability.maxHp;

	CEnemy::Update(deltaTime);
}

void Enemy4::Render()
{
	CEnemy::Render();
}

void Enemy4::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Enemy/Type4/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);

	GetSprite(Images::ATTACKREADY).LoadAll(filePath + L"ready", 0.02f, false);
	GetSprite(Images::ATTACK).LoadAll(filePath + L"Attack", 0.02f, false);
	GetSprite(Images::ATTACKEND).LoadAll(filePath + L"end", 0.02f, false);

	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);
}

void Enemy4::Attack(float deltaTime)
{
	if (!onAttack)
	{
		nowScene->obm.AddObject(new AttackCollider(L"enemy", &pos, D3DXVECTOR2(0, 0), { D3DXVECTOR2(-100, 0), D3DXVECTOR2(100, 200) }, 10, D3DXVECTOR2(200, 100), 0.1f, 1.5f, groundPos));
		onAttack = true;
	}

	pos.x += ri.scale.x * 1000 * deltaTime;
}
