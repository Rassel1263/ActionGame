#include "DXUT.h"
#include "CalcPage.h"

CalcPage::CalcPage()
{
	spr.LoadAll(L"Assets/Sprites/UI/calcBck.png");
	spr.bCamera = false;

	this->hp = nowScene->player->ability.hp;
	this->time = nowScene->gameTime;
	this->totalScore = nowScene->score + nowScene->destScore;
	this->combo = 0;

	layer = 3;

	nowScene->obm.AddObject(new Font(L"Font/Combo/", hp, D3DXVECTOR2(500, 200), D3DXVECTOR2(1, 1), 100, 0, layer + 1));
}

void CalcPage::Update(float deltaTime)
{
}

void CalcPage::Render()
{
}

void CalcPage::CalcNum(float& num, float deltaTime, float speed)
{
}
