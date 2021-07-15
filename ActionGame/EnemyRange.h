#pragma once

class Enemy;
class EnemyRange : public Object
{
public:
	bool findTarget = false;
	bool intro = false;
	Enemy* enemy;
	EnemyRange(Enemy* obj, D3DXVECTOR2 min, D3DXVECTOR2 max);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coll) override;
};

