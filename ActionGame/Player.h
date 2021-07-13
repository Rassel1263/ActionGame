#pragma once

class Player : public Units
{
public:
	CState<Player>* nowState = NULL;

	int specialIndex = -1;
	float inputTimer = 0;
	int prevInput = -1;
	int nowInput = -1;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	int SpecialIndex();
};

