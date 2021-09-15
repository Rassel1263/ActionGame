#pragma once
class CBoss : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,

		ATTACK1,

		ATTACKREADY,
		ATTACK2,
		ATTACKEND,

		ATTACK3,

		HIT,
		STUN,
		DIE,

		SHADOW,

		END,
	};

	CBoss();

	CState<CBoss>* nowState = NULL;

	Range* detectRange = NULL;

	int pattern = 0;
	float restTime = 0.0f;

	int rushIndex = 0;

	float spAmount = 100;
	float spMaxAmout = 100;
	float spHealTimer = 0.0f;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void SetImages() = 0;
	virtual void Hit(float damage, D3DXVECTOR2 addForce) override;

	bool Move(float deltaTime);
	virtual int ChoosePattern();
	virtual void UpdatePattern(float deltaTime);
	virtual bool Pattern1(float deltaTime) = 0;
	virtual bool Pattern2(float deltaTime) = 0;
	virtual bool Pattern3(float deltaTime) = 0;

	bool DetectColliderTarget();

	void SetState(CState<CBoss>* nextState);
	void ResetPattern();
};

