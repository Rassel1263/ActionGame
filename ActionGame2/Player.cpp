#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	spr.LoadAll(L"a");
}

void Player::Update(float deltaTime)
{
}

void Player::Render()
{
	spr.Render(RenderInfo{ pos });
}
