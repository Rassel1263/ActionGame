#pragma once
class EnemySpawner : public Object
{
public:
	bool spawnEnemy = false;

	std::vector<Enemy*> enemyVecs;

	EnemySpawner(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

