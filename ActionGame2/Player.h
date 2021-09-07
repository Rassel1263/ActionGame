#pragma once

class Player : public Unit
{
public:
	enum InputDir
	{
		LEFT,
		UP,
		RIGHT,
		DOWN,
	};

	enum class Images
	{
		IDLE,
		MOVE,
		JUMP,
		FALL,
		LANDING,
		SLIDE,

		WEAKATTACK1,
		WEAKATTACK2,
		WEAKATTACK3,
		WEAKATTACK4,
		WEAKTATCKEND,

		GUNKATA,
		MOVESHOOT,

		SHADOW,
		END,
	};

	Player();

	CState<Player>* nowState = NULL;

	// ÄÞº¸ ½Ã½ºÅÛ
	std::vector<std::string> comboInputs;
	bool specialAttack = false;

	int attackNum = 0;
	float comboTimer = 0.0f;

public:
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() override;
	
	void SetState(CState<Player>* nextState);
	void CreateAfterImage(int scene, float visibleTime, D3DXCOLOR color);

	bool Move(float deltaTime);

	void Combo(float deltaTime);
	void ComboCheck();
	void ComboInputCheck();
	void ComboInput(unsigned char u, std::string name);
	void ComboChecking(int skillNum, int inputAmount, ...);
};

