#pragma once
class CEnemy : public Unit
{
public:
	enum class Images
	{
		IDLE,
		MOVE,
		HIT,

		END,
	};

	CEnemy(D3DXVECTOR2 pos);

	CState<CEnemy>* nowState = NULL;

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() = 0;
	virtual void OnCollision(Collider& coli) override;

	void SetState(CState<CEnemy>* nextState);
};

