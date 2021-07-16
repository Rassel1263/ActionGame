#include "DXUT.h"
#include "Background.h"

Background::Background(int stage)
{
	spr.LoadAll(L"Assets/Sprites/Stage/stage1-" + std::to_wstring(stage) + L".png");

	pos = { 0, 130 };
}

void Background::Update(float deltaTime)
{
}

void Background::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}
