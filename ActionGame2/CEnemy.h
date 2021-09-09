#pragma once

class EnemyUI;
class CEnemy : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,

		ATTACKREADY,
		ATTACK,
		ATTACKEND,

		HIT,
		DIE,

		END,
	};

	CEnemy(D3DXVECTOR2 pos);
	int enemyType = 0;
	  
	float detectionRange = 0.0f;
	float stopRange = 0.0f;

	CState<CEnemy>* nowState = NULL;
	ColorShader* colorShader = NULL;

	EnemyUI* ui = NULL;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() = 0;
	virtual void OnCollision(Collider& coli) override;

	virtual void Attack(float deltaTime);

	bool Move(float deltaTime);
	void Destroy();
	void SetRange(float detectRange, float stopRange);
	bool CheckRange(float range, D3DXVECTOR2 distance);

	void SetState(CState<CEnemy>* nextState);
};

