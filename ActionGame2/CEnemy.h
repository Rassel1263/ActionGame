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
	  
	CState<CEnemy>* nowState = NULL;
	ColorShader* colorShader = NULL;

	Range* attackRange = NULL;
	Range* detectRange = NULL;

	EnemyUI* ui = NULL;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() = 0;
	virtual void OnCollision(Collider& coli) override;
	virtual void Hit(float damage, D3DXVECTOR2 addForce) override;

	virtual void Attack(float deltaTime);

	void CreateDetectRange(std::wstring targetName, D3DXVECTOR2 addPos, D3DXVECTOR2 min, D3DXVECTOR2 max);
	void CreateAttackRange(std::wstring targetName, D3DXVECTOR2 addPos, D3DXVECTOR2 min, D3DXVECTOR2 max);

	bool AttackColliderTarget();
	bool DetectColliderTarget();

	bool Move(float deltaTime);
	void Destroy();

	void SetState(CState<CEnemy>* nextState);
};
