#include "DXUT.h"
#include "EnemyRange.h"

EnemyRange::EnemyRange(Enemy* obj, D3DXVECTOR2 min, D3DXVECTOR2 max)
{
	enemy = obj;

	Collider::AABB aabb;
	aabb.min = min;
	aabb.max = max;
	bodies.push_back(Collider(this, L"enemyRange", &aabb, 0, D3DCOLOR_ARGB(255, 255, 255, 0)));

	layer = 2000;
}

void EnemyRange::Update(float deltaTime)
{
	findTarget = false;

	pos = enemy->pos;
}

void EnemyRange::Render()
{
	Object::Render();
}

void EnemyRange::OnCollision(Collider& coll)
{
	if (coll.tag == L"player")
	{
		if (abs(enemy->z - nowScene->player->z) < 5)
		{
			intro = true;
			findTarget = true;
		}
	}
}
