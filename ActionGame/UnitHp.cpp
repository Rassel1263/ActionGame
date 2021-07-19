#include "DXUT.h"
#include "UnitHp.h"

UnitHp::UnitHp()
{
	hp.resize(6);
	eUpper.resize(4);
	bUpper.resize(2);

	// 플레이어 UI
	hp[0].LoadAll(L"Assets/Sprites/UI/Hp/pHp.png");
	hp[1].LoadAll(L"Assets/Sprites/UI/Hp/pInHp.png");
	hp[2].LoadAll(L"Assets/Sprites/UI/Hp/Upper/player.png");

	// 적 UI
	hp[3].LoadAll(L"Assets/Sprites/UI/Hp/eHp.png");
	hp[4].LoadAll(L"Assets/Sprites/UI/Hp/pInHp.png");

	eUpper[0].LoadAll(L"Assets/Sprites/UI/Hp/Upper/speedy.png");
	eUpper[1].LoadAll(L"Assets/Sprites/UI/Hp/Upper/power.png");
	eUpper[2].LoadAll(L"Assets/Sprites/UI/Hp/Upper/bind.png");
	eUpper[3].LoadAll(L"Assets/Sprites/UI/Hp/Upper/range.png");

	bUpper[0].LoadAll(L"Assets/Sprites/UI/Hp/Upper/boss1.png");
	bUpper[1].LoadAll(L"Assets/Sprites/UI/Hp/Upper/boss2.png");

	pRI.pos = D3DXVECTOR2(-190, 150);

	eRI.pos = D3DXVECTOR2(190, 150);

	for (int i = 0; i < 6; ++i)
		hp[i].bCamera = false;

	for (int i = 0; i < 4; ++i)
		eUpper[i].bCamera = false;

	for (int i = 0; i < 2; ++i)
		bUpper[i].bCamera = false;
}

void UnitHp::Update(float deltaTime)
{
	hp[1].widthRatio = nowScene->player->ability.hp / nowScene->player->ability.maxHp;

	if(nowScene->player->target)
		hp[4].widthRatio = nowScene->player->target->ability.hp / nowScene->player->target->ability.maxHp;

	if (nowScene->boss)
		hp[4].widthRatio = nowScene->boss->ability.hp / nowScene->boss->ability.maxHp;
}

void UnitHp::Render()
{
	hp[0].Render(pRI);
	hp[1].Render(RenderInfo{pRI.pos + D3DXVECTOR2(18, -3.3)});
	hp[2].Render(RenderInfo{pRI.pos + D3DXVECTOR2(-100, 0)});

	if (nowScene->boss)
	{
		hp[3].Render(eRI);
		hp[4].Render(RenderInfo{ eRI.pos + D3DXVECTOR2(-18, -3.3), D3DXVECTOR2(-1, 1) });
		int index = nowScene->boss->bossIndex - 1;
		bUpper[index].Render(RenderInfo{ eRI.pos + D3DXVECTOR2(100, 0 )});
	}

	if (nowScene->player->target && !nowScene->boss)
	{
		hp[3].Render(eRI);
		hp[4].Render(RenderInfo{ eRI.pos + D3DXVECTOR2(-18, -3.3), D3DXVECTOR2(-1, 1)});
		eUpper[(int)nowScene->player->target->type].Render(RenderInfo{ eRI.pos + D3DXVECTOR2(100, 0)});
	}
}
