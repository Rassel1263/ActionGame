#pragma once

class Player : public Units
{
public:
	CState<Player>* nowState = NULL;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
};

