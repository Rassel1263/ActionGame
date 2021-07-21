#include "DXUT.h"
#include "EGaze.h"

EGaze::EGaze(Enemy* enemy)
{
	this->enemy = enemy;

	spr[0].LoadAll(L"Assets/Sprites/UI/Gaze/eGaze.png");
	spr[1].LoadAll(L"Assets/Sprites/UI/Gaze/eInGaze.png");
}

void EGaze::Update(float deltaTime)
{
	this->pos = enemy->pos + D3DXVECTOR2(0, -50);

	float hp = enemy->ability.hp;
	float maxHp = enemy->ability.maxHp;

	if (hp <= 0)
		hp = 0;

	spr[1].widthRatio = hp / maxHp;

	if (enemy->destroy)
		destroy = true;
}

void EGaze::Render()
{
	ri.pos = pos;

	for (int i = 0; i < 2; ++i)
		spr[i].Render(ri);
}
