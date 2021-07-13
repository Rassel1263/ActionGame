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

	std::map<UnitState, Sprite> spr;
	RenderInfo ri;

	int renderNum = 0;

	Units(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime);

	void SetAbility(float hp, float speed, float atkPower, float atkSpeed);
};

