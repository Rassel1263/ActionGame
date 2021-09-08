#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet(std::wstring team, D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed, float damage, bool airShot)
{
	this->team = team;
	this->pos = pos;
	this->speed = speed;

	ri.scale.x = dir.x;
	D3DXVec2Normalize(&this->dir, &dir);

	Collider::AABB aabb;

	if (team == L"player")
	{
		if (airShot)
		{
			spr.LoadAll(L"Assets/Sprites/bullet/playerBullet2");
			dir.y = 1.0f;
		}
		else
			spr.LoadAll(L"Assets/Sprites/bullet/playerBullet");

		aabb.min = { -50, -15 };
		aabb.max = { 80, 15 };
	}
	else
	{
		spr.LoadAll(L"Assets/Sprites/bullet/enemyBullet");

		aabb.min = { -10, -10 };
		aabb.max= { 10, 10 };
	}
	

	attackVector = { dir.x * 30, dir.y * 10};


	bodies.push_back(Collider(this, team + L"bullet", &aabb));
}

void Bullet::Update(float deltaTime)
{
	if (pos.x < Camera::GetInstance().cameraPos.x - 960 || pos.x > Camera::GetInstance().cameraPos.x + 960)
		destroy = true;

	pos += dir * speed * deltaTime;
}

void Bullet::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Bullet::OnCollision(Collider& coli)
{
	if (coli.tag == team) return;

	if (coli.tag == L"enemy" || coli.tag == L"player")
	{
		nowScene->obm.AddObject(new Effect(L"Player/Hit1", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 0.05f));
		destroy = true;
	}
}
