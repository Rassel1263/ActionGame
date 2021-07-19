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

	float hpGaze = 0.0f;
	float hpMaxGaze = 100.0f;

	float limitLeft = -700;
	float limitRight = 700;

	int itemIndex = 0;
	int guardCnt = 5;

	float guardTimer = 0.0f;
	bool boom = false;

	bool invincibility = false;

	Player();

	Enemy* target = NULL;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	int SpecialIndex();
	bool CheckSpecialGaze(int amount);
	void PlusSpecialGaze(int amount);
	void SetItemEffect(int index);
};

