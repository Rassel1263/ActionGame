#include "DXUT.h"
#include "Background.h"

Background::Background()
{
	spr.LoadAll(L"Assets/Sprites/Stage");

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
