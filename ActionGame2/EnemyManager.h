#pragma once
class EnemyManager
{
public:
	struct EnemyInfo
	{
		D3DXVECTOR2 pos;
		int enemyType;
	};

	std::vector<CEnemy*> enemyVec;
	std::vector<EnemyInfo> info;

	int infoIndex = 0;

	void SetEnemyPos(int curStage);

	void SpawnEnemy();
	void SortEnemy(CEnemy* enemy);
};

