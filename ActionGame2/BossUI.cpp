#include "DXUT.h"
#include "BossUI.h"

BossUI::BossUI(CBoss* boss)
{
	this->boss = boss;

	std::wstring filePath = L"Assets/Sprites/UI/Enemy/";

	hpBck.LoadAll(filePath + L"bossHpBck.png");
	hp.LoadAll(filePath + L"bossHp.png");

	hpBck.color.a = 0.0f;
	hpBck.bCamera = false;
	hp.widthRatio = 0.0f;
	hp.bCamera = false;

	hpRI.pos = D3DXVECTOR2(0, 400);
	
	this->boss = boss;
}

void BossUI::Update(float deltaTime)
{
	if (!start)
	{
		if(hpBck.color.a < 1.0f)
			hpBck.color.a += deltaTime;
		else
		{
			if (hp.widthRatio < 1.0f)
				hp.widthRatio += deltaTime;
			else
				start = true;
		}
	}
	else
		hp.widthRatio = boss->ability.hp / boss->ability.maxHp;

}

void BossUI::Render()
{

	hpBck.Render(RenderInfo{ D3DXVECTOR2(hpRI.pos.x + 20, hpRI.pos.y + 8) });
	hp.Render(hpRI);
}
