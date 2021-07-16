#include "DXUT.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(D3DXVECTOR2 pos, EnemyType type)
{
	this->pos = pos;
	this->type = type;
}

void EnemySpawner::Update(float deltaTime)
{
	if (pos.x - nowScene->player->pos.x < 50 && !spawnEnemy)
	{
		spawnEnemy = true;
		nowScene->player->limitLeft = pos.x - 80;
		nowScene->player->limitRight = pos.x + 80;

		Enemy* enemy;
		for (int i = 0; i < 3; ++i)
		{
			D3DXVECTOR2 randPos;
			randPos.x = (rand() % 2) ? 400 : -400;
			randPos.y = rand() % 50;

			nowScene->obm.AddObject(enemy = new Enemy(nowScene->player->pos + randPos, type));
			enemyVecs.push_back(enemy);
		}
	}

	if (spawnEnemy)
	{
		if (enemyVecs.size() <= 0)
		{
			nowScene->player->limitLeft = -700;
			nowScene->player->limitRight = 700;

			nowScene->wave--;
			destroy = true;
		}

		for (auto it = enemyVecs.begin(); it != enemyVecs.end();)
		{
			if ((*it)->destroy)
				it = enemyVecs.erase(it);
			else
				++it;
		}
	}
}

void EnemySpawner::Render()
{
}
