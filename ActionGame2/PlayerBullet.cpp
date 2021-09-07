#include "DXUT.h"
#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed, float damage)
{
	this->pos = pos;
	this->speed = speed;

	if (damage < 10)
		spr.LoadAll(L"Assets/Sprites/bullet/playerBullet");
	else
		spr.LoadAll(L"Assets/Sprites/bullet/playerBullet2");

	ri.scale.x = dir.x;

	D3DXVec2Normalize(&this->dir, &dir);

	Collider::AABB aabb;
	aabb.min = { -50, -15 };
	aabb.max = { 80, 15 };
	bodies.push_back(Collider(this, L"playerBullet", &aabb));
}

void PlayerBullet::Update(float deltaTime)
{
	if (pos.x < Camera::GetInstance().cameraPos.x - 960 || pos.x > Camera::GetInstance().cameraPos.x + 960)
		destroy = true;

	pos += dir * speed * deltaTime;
}

void PlayerBullet::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}
