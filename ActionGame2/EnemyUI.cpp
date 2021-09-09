#include "DXUT.h"
#include "EnemyUI.h"

EnemyUI::EnemyUI(CEnemy* enemy)
{
	std::wstring filePath = L"Assets/Sprites/UI/Enemy/";

	hpBck.LoadAll(filePath + L"enemyHpBck.png");
	hp.LoadAll(filePath + L"enemyHp.png");

	this->enemy = enemy;
}

void EnemyUI::Update(float deltaTime)
{
	hpRI.pos = enemy->pos + D3DXVECTOR2(0, -20);
	hp.widthRatio = enemy->ability.hp / enemy->ability.maxHp;
}

void EnemyUI::Render()
{
	hpBck.Render(RenderInfo{D3DXVECTOR2(hpRI.pos.x + 5, hpRI.pos.y + 4)});
	hp.Render(hpRI);
}

