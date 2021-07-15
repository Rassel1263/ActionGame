#include "DXUT.h"
#include "pGaze.h"

PGaze::PGaze(Player* player)
{
	this->player = player;
	this->pos = pos;

	gaze.resize(4);

	gaze[0].LoadAll(L"Assets/Sprites/UI/Gaze/pInGaze.png");
	gaze[1].LoadAll(L"Assets/Sprites/UI/Gaze/pGaze.png");

	gaze[0].bCamera = false;
	gaze[1].bCamera = false;

	gaze[2].LoadAll(L"Assets/Sprites/UI/Gaze/hInGaze.png");
	gaze[3].LoadAll(L"Assets/Sprites/UI/Gaze/hGaze.png");

	gaze[2].bCamera = false;
	gaze[3].bCamera = false;

	pRI.pos = D3DXVECTOR2(200, -160);
	hRI.pos = D3DXVECTOR2(-200, -160);
}

void PGaze::Update(float deltaTime)
{
	gaze[0].widthRatio = nowScene->player->specialGaze / nowScene->player->specialMaxGaze;
	gaze[2].widthRatio = nowScene->player->ability.hp / nowScene->player->ability.maxHp;
}

void PGaze::Render()
{
	gaze[0].Render(pRI);
	gaze[1].Render(pRI);
	
	gaze[2].Render(hRI);
	gaze[3].Render(hRI);
}
