#pragma once

class Unit : public Object
{
public:
	struct Ability
	{
		float hp;
		float maxHp;
		float speed;

		void SetAbility(float hp, float speed)
		{
			this->hp = hp;
			this->maxHp = hp;
			this->speed = speed;
		}
	};

	std::vector<Sprite> sprites;
	RenderInfo ri;

	Ability ability;

	std::wstring team = L"";

	bool hit = false;
	float hitTimer = 0.0f;
	float hitTime = 0.0f;

	float hitDamage = 0.0f;
	int renderNum = 0;

	bool onAttack = false;
	bool superArmor = false;
	float attackTimer = 0.0f;

	D3DXVECTOR2 GetDistanceFromTarget(D3DXVECTOR2 targetPos);

	Unit();
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() = 0;
	virtual void Hit(float damage, D3DXVECTOR2 addForce);

	void SetCollider(float left, float bottom, float right, float top, std::wstring tag);

	Sprite& GetNowSprite();

	template <typename T>
	void SetAni(T n)
	{
		renderNum = IntEnum(n);
		GetNowSprite().Reset();
	}

	template <typename T>
	void Resize(T n)
	{
		sprites.resize(IntEnum(n));
	}

	template <typename T>
	Sprite& GetSprite(T n)
	{
		return sprites.at(IntEnum(n));
	}
};
