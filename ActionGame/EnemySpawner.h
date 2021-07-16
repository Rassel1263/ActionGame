#pragma once
class EnemySpawner : public Object
{
public:
	bool spawnEnemy = false;
	bool& clear;

	std::vector<Enemy*> enemyVecs;
	EnemyType type;

	EnemySpawner(D3DXVECTOR2 pos, EnemyType type, bool clear);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

