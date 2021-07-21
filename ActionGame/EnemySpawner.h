#pragma once
class EnemySpawner : public Object
{
public:
	bool spawnEnemy = false;

	std::vector<Enemy*> enemyVecs;
	EnemyType type;

	EnemySpawner(D3DXVECTOR2 pos, EnemyType type);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

