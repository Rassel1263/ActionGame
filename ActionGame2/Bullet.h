#pragma once
class Bullet : public Object
{
public:
	enum class Type
	{
		BASIC,
		AIRSHOT,
		MACHINEGUN,
		SNIPER,

		ROCK,
	} type;

	Sprite spr;
	RenderInfo ri;

	std::wstring team = L"";

	float damage = 0.0f;
	float speed = 0.0f;
	D3DXVECTOR2 attackVector = { 0, 0 };

	D3DXVECTOR2 dir = { 0, 0 };

	Bullet(std::wstring team, D3DXVECTOR2 pos, D3DXVECTOR2 dir, float speed, float damage, float groundPos, Type type);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
};

