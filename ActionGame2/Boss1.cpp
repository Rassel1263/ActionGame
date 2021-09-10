#include "DXUT.h"
#include "Boss1.h"

Boss1::Boss1()
{
	team = L"enemy";

	this->pos = D3DXVECTOR2(1500, 0);

	Camera::GetInstance().destCameraPos.x = pos.x;

	SetImages();
	SetRigid(1);

	nowScene->obm.AddObject(new BossIntro());
}

void Boss1::Update(float deltaTime)
{
	Unit::Update(deltaTime);
}

void Boss1::Render()
{
	Unit::Render();
}

void Boss1::SetImages()
{
	Resize(Images::END);

	std::wstring filePath = L"Assets/Sprites/Unit/Boss/Type1/";

	GetSprite(Images::IDLE).LoadAll(filePath + L"Idle", 0.05f);
	GetSprite(Images::MOVE).LoadAll(filePath + L"move", 0.05f);
	GetSprite(Images::ATTACK).LoadAll(filePath + L"Attack1", 0.05f, false);
	GetSprite(Images::HIT).LoadAll(filePath + L"hit", 0.025f, false);
	GetSprite(Images::DIE).LoadAll(filePath + L"Die", 0.05f, false);
}
