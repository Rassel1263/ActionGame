#pragma once

enum class EnemyType 
{
	Speedy = 0,
	Power,
	Bind,
	Range,
};

class Enemy : public Units
{
public:
	EnemyType type = EnemyType::Speedy;
	CState<Enemy>* nowState = NULL;

	Enemy(D3DXVECTOR2 pos, EnemyType type);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;

	void SetInfo();
	bool CheckPlayer(float distance);
};
