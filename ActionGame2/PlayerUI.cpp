#include "DXUT.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI(Player* player)
{
	this->player = player;

	Load(L"base1.png", base);

	Load(L"hpBck.png", hpBck);
	Load(L"hp.png", hp);

	Load(L"mpBck.png", mpBck);
	Load(L"mp.png", mp);

	Load(L"healBck.png", healBck);
	Load(L"heal.png", heal);

	Load(L"comboFont.png", comboFont);

	Load(L"comboBck.png", comboBck);
	Load(L"combo.png", comboGauge);

	hpRI.pos = { -800, -400 };
	mpRI.pos = { -560, -445 };
	comboRI.pos = { 800, 50 };
}

void PlayerUI::Update(float deltaTime)
{
	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;
	mp.heightRatio = 1 - player->mp / player->maxMp;
	comboGauge.widthRatio = 1 - player->comboInterval / 0.5f;

	UpdateCombo();
}

void PlayerUI::Render()
{
	base.Render(RenderInfo());

	hpBck.Render(hpRI);
	hp.Render(RenderInfo{ D3DXVECTOR2(hpRI.pos.x, hpRI.pos.y + 5) });

	mpBck.Render(mpRI);
	mp.Render(RenderInfo{ D3DXVECTOR2(mpRI.pos.x, mpRI.pos.y + 4) });

	comboFont.Render(RenderInfo{ D3DXVECTOR2(800, 200) });

	if (player->combo > 0)
	{
		comboBck.Render(comboRI);
		comboGauge.Render(RenderInfo{ D3DXVECTOR2(comboRI.pos.x - 5, comboRI.pos.y - 4) });

		int i = 0;
		for (auto& c : combo)
		{
			c.Render(RenderInfo{ D3DXVECTOR2(800 + i * 50, 100) });
			i++;
		}
	}
}

void PlayerUI::UpdateCombo()
{
	if (player->prevCombo != player->combo)
	{

		std::wstring str = std::to_wstring(player->combo);
		combo.resize(str.size());

		int i = 0;
		for (auto& c : combo)
		{
			c.LoadAll(L"Assets/Sprites/UI/Font/Combo/" + str.substr(i, 1) + L".png");
			c.bCamera = false;

			if(player->combo != 0)
				nowScene->obm.AddObject(new AfterImage(c, RenderInfo{ D3DXVECTOR2(800 + i * 50, 100) }, D3DXVECTOR2(1.5, 1.5), D3DCOLOR_ARGB(70, 255, 255, 255), 1100, false));

			i++;
		}

		player->prevCombo = player->combo;
	}
}

void PlayerUI::Load(std::wstring image, Sprite& spr)
{
	spr.LoadAll(L"Assets/Sprites/UI/Player/" + image);
	spr.bCamera = false;
}
