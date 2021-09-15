#include "DXUT.h"
#include "EnemyManager.h"

void EnemyManager::SpawnEnemy(D3DXVECTOR2 pos, int enemyType)
{
	CEnemy* enemy;

	if(enemyType == 1)
		nowScene->obm.AddObject(enemy = new Enemy1(pos));
	else if(enemyType == 2)
		nowScene->obm.AddObject(enemy = new Enemy2(pos));
	else if(enemyType == 2)
		nowScene->obm.AddObject(enemy = new Enemy3(pos));
	else if(enemyType == 4)
		nowScene->obm.AddObject(enemy = new Enemy4(pos));

	enemyVec.push_back(enemy);
}

void EnemyManager::SortEnemy(CEnemy* enemy)
{
	enemyVec.erase(std::find(enemyVec.begin(), enemyVec.end(), enemy));
}
