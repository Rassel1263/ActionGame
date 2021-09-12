#pragma once
class Boss1 : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,

		ATTACK1,
		ATTACK2,

		HIT,
		DIE,

		SHADOW,

		END,
	};

	Boss1();

	CState<Boss1>* nowState = NULL;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void SetImages() override;
	virtual void Hit(float damage, D3DXVECTOR2 addForce) override;

	Range* detectRange = NULL;
	ColorShader* colorShader = NULL;

	int pattern = 0;
	float restTime = 0.0f;
	float patternTime = 0.0f;

	virtual void UpdatePattern(float deltaTime);

	bool Move(float deltaTime);
	virtual bool Pattern1(float deltaTime);
	virtual bool Pattern2(float deltaTime);
	virtual bool Pattern3(float deltaTime);

	virtual int ChoosePattern();

	bool DetectColliderTarget();
	

	void SetState(CState<Boss1>* nextState);
	void ResetPattern();
};

