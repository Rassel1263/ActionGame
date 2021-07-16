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
	BIND,
	HIT,
	DIE,
	CEREMONY,
};

class Units : public Object
{
public:
	struct UnitAbility
	{
		float hp = 0.0f;
		float maxHp = 0.0f;
		float speed = 0.0f;
		float atkPower = 0.0f;
		float atkDamage = 0.0f;
		float atkSpeed = 0.0f;
	} ability;

	bool bHit = false;
	bool bind = false;
	bool bPowerUp = false;

	float aniTimer = 0.0f;
	float shaderTimer = 0.0f;
	float abilityTimer = 0.0f;

	float damage = 0;

	D3DXVECTOR2 offset = { 0, 0 };
	D3DXVECTOR2 attackVec = { 0, 0 };

	std::map<UnitState, Sprite> spr;
	RenderInfo ri;

	UnitState renderer = UnitState::IDLE;
	std::wstring tag;

	SimpleShader* simpleShader;

	Units(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime);

	bool CheckDistance(float distance);
	void SetAbility(float hp, float speed, float atkPower, float atkSpeed);
	void SetCollider(float left, float top, float right, float bottom, D3DXCOLOR color = D3DCOLOR_ARGB(255, 255, 0, 0));
	void SetAttackInfo(D3DXVECTOR2 offset, D3DXVECTOR2 attackVec, float atkPower, float atkDamage, float timer);
	void Attack();


};

