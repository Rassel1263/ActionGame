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

	bool hit = false;
	float hitDamage = 0.0f;
	int renderNum = 0;

	Unit();
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void SetImages() = 0;
	virtual void Hit(float damage);

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
