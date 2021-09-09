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

	Load(L"combo.png", combo);

	hpRI.pos = { -800, -400};
	mpRI.pos = { -560, -445};
}

void PlayerUI::Update(float deltaTime)
{
	hp.heightRatio = 1 - player->ability.hp / player->ability.maxHp;
	mp.heightRatio = 1 - player->mp / player->maxMp;
}

void PlayerUI::Render()
{
	base.Render(RenderInfo());

	hpBck.Render(hpRI);
	hp.Render(RenderInfo{D3DXVECTOR2(hpRI.pos.x, hpRI.pos.y + 5)});

	mpBck.Render(mpRI);
	mp.Render(RenderInfo{ D3DXVECTOR2(mpRI.pos.x, mpRI.pos.y + 4)});

	combo.Render(RenderInfo{D3DXVECTOR2(800, 200)});
}

void PlayerUI::Load(std::wstring image, Sprite& spr)
{
	spr.LoadAll(L"Assets/Sprites/UI/Player/" + image);
	spr.bCamera = false;
}
