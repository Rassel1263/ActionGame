#pragma once
class EnemyManager
{
public:
	std::vector<CEnemy*> enemyVec;

	void SpawnEnemy(D3DXVECTOR2 pos, int enemyType);

	void SortEnemy(CEnemy* enemy);
};

