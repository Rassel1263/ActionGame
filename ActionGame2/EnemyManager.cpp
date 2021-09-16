#include "DXUT.h"
#include "EnemyManager.h"

void EnemyManager::SetEnemyPos(int curStage)
{
	std::wifstream file(L"Assets/EnemyPos/stage" + std::to_wstring(curStage) + L".txt");

	if (file.is_open())
	{
		while (!file.eof())
		{
			EnemyInfo temp;

			file >> temp.pos.x >> temp.pos.y >> temp.enemyType;

			info.push_back(temp);
		}
	}

}

void EnemyManager::SpawnEnemy()
{
	CEnemy* enemy;

	if (infoIndex < info.size() - 1)
	{
		if (nowScene->player->pos.x + 900 > info[infoIndex].pos.x)
		{
			if (info[infoIndex].enemyType == 1)
				nowScene->obm.AddObject(enemy = new Enemy1(info[infoIndex].pos));
			else if (info[infoIndex].enemyType == 2)
				nowScene->obm.AddObject(enemy = new Enemy2(info[infoIndex].pos));
			else if (info[infoIndex].enemyType == 3)
				nowScene->obm.AddObject(enemy = new Enemy3(info[infoIndex].pos));
			else if (info[infoIndex].enemyType == 4)
				nowScene->obm.AddObject(enemy = new Enemy4(info[infoIndex].pos));

			enemyVec.push_back(enemy);
			++infoIndex;
		}
	}

}

void EnemyManager::SortEnemy(CEnemy* enemy)
{
	enemyVec.erase(std::find(enemyVec.begin(), enemyVec.end(), enemy));
}
