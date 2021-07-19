#pragma once

class Boss : public Units
{
public:
	int bossIndex = 1;
	int fireBall = 0;
	
	CState<Boss>* nowState = NULL;
	EnemyRange* enemyRange = NULL;

	Boss(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual bool Move(float deltaTime) override;
};

