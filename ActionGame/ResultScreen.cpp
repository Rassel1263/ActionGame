#include "DXUT.h"
#include "ResultScreen.h"

ResultScreen::ResultScreen()
{
	fade.LoadAll(L"Assets/Sprites/UI/fade.png");
	fade.color.a = 0.0f;
}

void ResultScreen::Update(float deltaTime)
{
	fade.color.a += deltaTime * 0.1f;
}

void ResultScreen::Render()
{
	ri.pos = pos;
	fade.Render(ri);
}
