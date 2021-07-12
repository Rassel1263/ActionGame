#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	spr.LoadAll(L"As");
}

void Player::Update(float deltaTime)
{
	Game::GetInstance().destCameraPos = pos - Game::GetInstance().ScreenSize();

	if (Input::GetInstance().KeyPress(VK_LEFT))
		pos.x -= 100 * deltaTime;

	if (Input::GetInstance().KeyPress(VK_RIGHT))
		pos.x += 100 * deltaTime;

	if (Input::GetInstance().KeyPress(VK_UP))
		pos.y -= 100 * deltaTime;

	if (Input::GetInstance().KeyPress(VK_DOWN))
		pos.y += 100 * deltaTime;
;}

void Player::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
