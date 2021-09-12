#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet(std::wstring team, D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed, float damage, float groundPos, Type type)
{
	this->team = team;
	this->pos = pos;
	this->speed = speed;
	this->type = type;
	this->groundPos = groundPos;
	this->damage = damage;
	this->layer = 1080 - (groundPos + 540);

	ri.rotate = D3DXToDegree(-atan2(dir.y, dir.x));
	D3DXVec2Normalize(&this->dir, &dir);

	Collider::AABB aabb;

	if (team == L"player")
	{
		dir.y = 0.0f;

		if (type == Type::BASIC)
			spr.LoadAll(L"Assets/Sprites/bullet/playerBullet");
		else if (type == Type::AIRSHOT)
		{
			spr.LoadAll(L"Assets/Sprites/bullet/playerBullet2");
			dir.y = 1.0f;
		}
		else if (type == Type::MACHINEGUN)
			spr.LoadAll(L"Assets/Sprites/bullet/playerBullet3");
		else if (type == Type::SNIPER)
			spr.LoadAll(L"Assets/Sprites/bullet/playerBullet4");

		aabb.min = { -50, -15 };
		aabb.max = { 80, 15 };
	}
	else
	{
		if(type == Type::ROCK)
			spr.LoadAll(L"Assets/Sprites/bullet/enemyBullet");
		else if (type == Type::GOLDROCK)
			spr.LoadAll(L"Assets/Sprites/bullet/EnemybossRock");

		aabb.min = { -10, -10 };
		aabb.max= { 10, 10 };
	}

	attackVector = { dir.x * 30, dir.y * 1000 };


	bodies.push_back(Collider(this, team + L"bullet", &aabb));
}

void Bullet::Update(float deltaTime)
{
	if (pos.y <= groundPos)
	{
		nowScene->obm.AddObject(new Effect(L"Player/Hit1", pos, D3DXVECTOR2(0.7, 0.7), D3DXVECTOR2(0.5, 0.5), 0.05f));
		destroy = true;
	}

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
		if (abs(groundPos - coli.obj->groundPos) >= 100) return;

		if (type != Type::SNIPER)
		{
			D3DXVECTOR2 randPos = D3DXVECTOR2(nowScene->GetRandomNum(-50, 50), nowScene->GetRandomNum(-50, 50));
			nowScene->obm.AddObject(new Effect(L"Player/Hit1", coli.obj->pos + randPos + D3DXVECTOR2(0, 120), D3DXVECTOR2(1.5, 1.5), D3DXVECTOR2(0.5, 0.5), 0.05f));
			destroy = true;
		}
	}
}
