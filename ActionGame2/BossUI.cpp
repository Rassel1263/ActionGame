#include "DXUT.h"
#include "BossUI.h"

BossUI::BossUI(CBoss* boss)
{
	this->boss = boss;

	std::wstring filePath = L"Assets/Sprites/UI/Enemy/";

	SetSprite(L"bossHpBck.png", hpBck);
	SetSprite(L"bossHp.png", hp);

	hpBck.color.a = 0.0f;
	hp.widthRatio = 0.0f;
	hpRI.pos = D3DXVECTOR2(0, 400);

	SetSprite(L"superArmorBck.png", spBck);
	SetSprite(L"superArmor.png", sp);

	spBck.color.a = 0.0f;
	sp.widthRatio = 0.0f;
	spRI.pos = D3DXVECTOR2(0, 360);
	
	this->boss = boss;
}

void BossUI::Update(float deltaTime)
{
	if (!start)
	{
		if (hpBck.color.a < 1.0f)
			hpBck.color.a += deltaTime;
		else
		{
			if (hp.widthRatio < 1.0f)
				hp.widthRatio += deltaTime;
			else
				start = true;
		}

		spBck.color.a = hpBck.color.a;
		sp.widthRatio = hpBck.widthRatio;
	}
	else
	{
		hp.widthRatio = boss->ability.hp / boss->ability.maxHp;
		sp.widthRatio = boss->spAmount / boss->spMaxAmout;
	}

}

void BossUI::Render()
{
	spBck.Render(RenderInfo{spRI});
	sp.Render(spRI);

	hpBck.Render(RenderInfo{ D3DXVECTOR2(hpRI.pos.x + 20, hpRI.pos.y + 8) });
	hp.Render(hpRI);
}

void BossUI::SetSprite(std::wstring name, Sprite& spr)
{
	std::wstring filePath = L"Assets/Sprites/UI/Enemy/";

	spr.LoadAll(filePath + name);
	spr.bCamera = false;
}
