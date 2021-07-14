#pragma once

enum class UnitState
{
	IDLE = 0,
	DOWN,
	WALK,
	JUMP,
	FALL,
	LATTACK,
	HATTACK,
	LSATTACK1,
	LSATTACK2,
	HSATTACK1,
	HSATTACK2,
	HIT,
	DIE,
};

class Units : public Object
{
public:
	struct UnitAbility
	{
		float hp = 0.0f;
		float speed = 0.0f;
		float atkPower = 0.0f;
		float atkSpeed = 0.0f;
	} ability;

	bool bHit = false;

	float aniTimer = 0.0f;

	std::map<UnitState, Sprite> spr;
	RenderInfo ri;

	UnitState renderer = UnitState::IDLE;
	std::wstring tag;

	Units(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime);

	void SetAbility(float hp, float speed, float atkPower, float atkSpeed);
	void SetCollider(float left, float top, float right, float bottom, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));
	void Attack(D3DXVECTOR2 offset, D3DXVECTOR2 attackVec);

};

