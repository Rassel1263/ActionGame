#include "DXUT.h"
#include "FireBall.h"

FireBall::FireBall(std::wstring name, D3DXVECTOR2 pos, D3DXVECTOR2 dir, float damage, float z)
{
	this->name = name;
	spr.LoadAll(L"Assets/Sprites/Units/FireBall/" + name);

	this->z = z;
	std::cout << z << std::endl;

	this->pos = pos;
	ri.scale = dir;
	this->damage = damage;

	Collider::AABB aabb;
	aabb.min = { -20, -20 };
	aabb.max = { 20, 20 };

	bodies.push_back(Collider(this, name + L"fireball", &aabb, 0));
}

void FireBall::Update(float deltaTime)
{
	pos.x += ri.scale.x * 200 * deltaTime;

	if (pos.x < Game::GetInstance().destCameraPos.x - 360 || pos.x > Game::GetInstance().destCameraPos.x + 360)
		destroy = true;

	spr.Update(deltaTime);
}

void FireBall::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

void FireBall::OnCollision(Collider& other)
{
	if (name == L"Enemy")
	{
		if (other.tag == L"player" && abs(other.obj->z - z) < 10)
		{
			destroy = true;

			static_cast<Player*>(other.obj)->bHit = true;
			static_cast<Player*>(other.obj)->damage = damage;

			nowScene->obm.AddObject(new Effect(L"FireBall/" + name, pos, ri.scale, 0.05f));
		}
	}
	else
	{
		if (other.tag == L"enemy" || other.tag == L"boss" && abs(other.obj->z - z) < 10)
		{
			destroy = true;

			static_cast<Enemy*>(other.obj)->bHit = true;
			static_cast<Enemy*>(other.obj)->damage = damage;

			SoundManager::GetInstance().Play(L"Assets/Sound/Explosion.mp3");
			nowScene->obm.AddObject(new Effect(L"FireBall/" + name, pos, ri.scale, 0.05f));
		}
	}
}
