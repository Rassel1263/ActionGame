#pragma once

class Player : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,
		JUMP,
		FALL,
		SLIDE,
		GUNKATA,

		SHADOW,
		END,
	};

	CState<Player>* nowState = NULL;

	Player();
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void SetState(CState<Player>* nextState);
	void SetAni(Images nextState);

	bool Move(float deltaTime);
};

