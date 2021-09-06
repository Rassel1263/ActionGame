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

	int renderNum = 0;

	Unit();
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	Sprite& GetNowSprite();

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
