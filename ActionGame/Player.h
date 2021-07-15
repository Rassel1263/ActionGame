#pragma once

class Enemy;
class Player : public Units
{
public:
	CState<Player>* nowState = NULL;

	int specialIndex = -1;
	float inputTimer = 0;
	int prevInput = -1;
	int nowInput = -1;

	float specialGaze = 0.0f;
	float specialMaxGaze = 100.0f;
	float eftTimer = 0.0f;

	float limitLeft = -700;
	float limitRight = 700;

	Player();

	Enemy* target = NULL;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	int SpecialIndex();
	void PlusSpecialGaze(int amount);
};

