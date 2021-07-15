#include "DXUT.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(D3DXVECTOR2 pos)
{
	this->pos = pos;
}

void EnemySpawner::Update(float deltaTime)
{
	if (pos.x - nowScene->player->pos.x < 100 && !spawnEnemy)
	{
		spawnEnemy = true;
		nowScene->player->limitLeft = pos.x - 100;
		nowScene->player->limitRight = pos.x + 100;

		Enemy* enemy;
		for (int i = 0; i < 3; ++i)
		{
			D3DXVECTOR2 randPos;
			randPos.x = (rand() % 2) ? 400 : -400;
			randPos.y = rand() % 50;

			nowScene->obm.AddObject(enemy = new Enemy(nowScene->player->pos + randPos, EnemyType::Speedy));
			enemyVecs.push_back(enemy);
		}
	}

	if (spawnEnemy)
	{
		if (enemyVecs.size() <= 0)
		{
			nowScene->player->limitLeft = -700;
			nowScene->player->limitRight = 700;
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
