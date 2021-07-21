#pragma once

class EnemyRange : public Object
{
public:
	bool findTarget = false;
	Units* enemy;
	EnemyRange(Units* obj, D3DXVECTOR2 min, D3DXVECTOR2 max);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coll) override;
};

