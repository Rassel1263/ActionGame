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
		HIT,
		DIE,

		WEAKATTACK1,
		WEAKATTACK2,
		WEAKATTACK3,
		WEAKATTACK4,
		WEAKTATCKEND,

		STRONGATTACK,
		MACHINEGUN,
		SNIPER,

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

	// specialAttack
	bool afterImage = false;
	float afterImageTime = 0.0f;


public:
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void SetImages() override;
	
	void SetState(CState<Player>* nextState);
	void CreateAfterImage(int scene, float visibleTime, D3DXCOLOR color);

	bool Move(float deltaTime, bool moveShot = false);

	void Combo(float deltaTime);
	void ComboCheck();
	void ComboInputCheck();
	void ComboInput(unsigned char u, std::string name);
	void ComboChecking(int skillNum, int inputAmount, ...);

	void CreateBullet(D3DXVECTOR2 offset, float speed, float damage, bool airShoot);
	void CreateAttackCollider(int scene, D3DXVECTOR2 offset, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, float atkPower, float yVec, float time);
	void SetSpecialAttack(Images image,int attackScene, float afterImageTime);
};

