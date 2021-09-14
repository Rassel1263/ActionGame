#pragma once
class CBoss : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,

		ATTACK1,
		ATTACK2,
		ATTACK3,

		HIT,
		DIE,

		SHADOW,

		END,
	};

	CBoss();

	CState<CBoss>* nowState = NULL;

	Range* detectRange = NULL;
	ColorShader* colorShader = NULL;

	int pattern = 0;
	float restTime = 0.0f;

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

